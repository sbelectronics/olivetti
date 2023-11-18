/*	
 * Copyright 2001-2010 Georges Menie (www.menie.org)
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the University of California, Berkeley nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE REGENTS AND CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * Modified by Scott M Baker to add ymodem support for sending packet zero and
 * multi-file batch transfer.
 */

/* this code needs standard functions memcpy() and memset()
   and input/output functions _inbyte() and _outbyte().

   the prototypes of the input/output functions are:
     int _inbyte(unsigned short timeout); // msec timeout
     void _outbyte(int c);

 */

#include <string.h>
#include <stdio.h>
#include <sys/pcos.h>
#include "crc16.h"

#define SOH  0x01
#define STX  0x02
#define EOT  0x04
#define ACK  0x06
#define NAK  0x15
#define CAN  0x18
#define CTRLZ 0x1A

#define DLY_1S 1000
#define MAXRETRANS 25
#define TRANSMIT_XMODEM_1K

#define FCLOSE(f) \
         if (f!=NULL) { \
		     fclose(f); \
			 f=NULL; \
		 }

char Filename[1024];

int _inbyte(unsigned short timeout) {
	unsigned char b, bstat;
	int r;
	int triesLeft;

	/* I don't know how to do a proper timeout yet. Counting to 2000 ought
	 * to be about a second.
	 */
	triesLeft=2000;
again:
    r = _pcos_lookbyte(DID_COM, &b, &bstat);
	if (r!=PCOS_ERR_OK) {
		fprintf(stderr, "Error in inbyte lookbyte: %d\n", r);
		exit(1);
	}
	if (bstat == 0x00) {
		/* 00 = empty, FF = something present */
		if (triesLeft>0) {
			triesLeft--;
			goto again;
		}
		return -1;
	}


	r = _pcos_getbyte(DID_COM, &b);
	if (r!=PCOS_ERR_OK) {
		fprintf(stderr, "Error in inbyte: %d\n", r);
		exit(1);
	}

	return b;
}

void _outbyte(int c) {
    int r;
again:
	r = _pcos_putbyte(DID_COM, c);
	if (r==110) {
		// timeout
		goto again;
	}	
	if (r!=PCOS_ERR_OK) {
		fprintf(stderr, "Error in outbyte: %d\n", r);
		exit(1);
	}
}

static int check(int crc, const unsigned char *buf, int sz)
{
	if (crc) {
		unsigned short crc = crc16_ccitt(buf, sz);
		unsigned short tcrc = (buf[sz]<<8)+buf[sz+1];
		if (crc == tcrc)
			return 1;
	}
	else {
		int i;
		unsigned char cks = 0;
		for (i = 0; i < sz; ++i) {
			cks += buf[i];
		}
		if (cks == buf[sz])
		return 1;
	}

	return 0;
}

static void flushinput(void)
{
	while (_inbyte(((DLY_1S)*3)>>1) >= 0)
		;
}

long ymodemReceive(void)
{
	unsigned char xbuff[1030]; /* 1024 for XModem 1k + 3 head chars + 2 crc + nul */
	unsigned char *p;
	int bufsz, crc = 0;
	unsigned char trychar = 'C';
	unsigned char packetno;
	int i, c;
	int fileCount = 0;
	long len = 0;
	int retry, retrans = MAXRETRANS;
	int noDataYet;
	int firstEOT;
	FILE *f;

again:
	f = NULL;
	firstEOT = 1;
	noDataYet = 1;
	packetno = 1;

	for(;;) {
		for( retry = 0; retry < 64; ++retry) {
			if (trychar) _outbyte(trychar);
			if ((c = _inbyte((DLY_1S)<<1)) >= 0) {
				switch (c) {
				case SOH:
					bufsz = 128;
					goto start_recv;
				case STX:
					bufsz = 1024;
					goto start_recv;
				case EOT:
				    FCLOSE(f);
					flushinput();        /* XXX smbaker: drop this flush?? */
					if (firstEOT) {
					    _outbyte(NAK);	 /* NAK the first EOT. Why?? */
						firstEOT=0;
						continue;        /* need to receive the second EOT */
					} else {
						_outbyte(ACK);   /* ack the second EOT and ask for next file */
						_outbyte('C');
					}
					goto again;       
				case CAN:
					if ((c = _inbyte(DLY_1S)) == CAN) {
						flushinput();
						_outbyte(ACK);
						FCLOSE(f);
						return -1; /* canceled by remote */
					}
					break;
				default:
					break;
				}
			}
		}
		if (trychar == 'C') { trychar = NAK; continue; }
		FCLOSE(f);
		flushinput();
		_outbyte(CAN);
		_outbyte(CAN);
		_outbyte(CAN);
		return -2; /* sync error */

	start_recv:
		if (trychar == 'C') crc = 1;
		trychar = 0;
		p = xbuff;
		*p++ = c;
		for (i = 0;  i < (bufsz+(crc?1:0)+3); ++i) {
			if ((c = _inbyte(DLY_1S)) < 0) goto reject;
			*p++ = c;
		}

		if ((xbuff[1] == 0x00) && ((unsigned char)(xbuff[2]) == 0xFF) && check(crc, &xbuff[3], bufsz) && noDataYet) {
			if (xbuff[3] == 0x00) {
				_outbyte(ACK);
				flushinput();    /* XXX smbaker: drop the flush and kick the CANs?? */
				_outbyte(CAN);
				_outbyte(CAN);
				_outbyte(CAN);
				fprintf(stderr, "Empty block zero - No more Batch Files\n");
				fprintf(stderr, "%ld bytes transferred in %d files\n", len, fileCount);
				exit(0);
			}
			strcpy(Filename, &xbuff[3]);
			f = fopen(Filename,"wb");
			if (f==NULL) {
				flushinput();
				_outbyte(CAN);
				_outbyte(CAN);
				_outbyte(CAN);
				fprintf(stderr, "Failed to open %s\n", Filename);
				exit(1);
			}
			/* TODO: Get File Size from packet zero */
			_outbyte(ACK);  /* acknowledge the packet zero */
			_outbyte('C');  /* ask for file transfer */
			fileCount += 1;
			continue;
		}

		if (xbuff[1] == (unsigned char)(~xbuff[2]) && 
			(xbuff[1] == packetno || xbuff[1] == (unsigned char)packetno-1) &&
			check(crc, &xbuff[3], bufsz)) {
			noDataYet = 0;
			if (xbuff[1] == packetno)	{
				register int count = bufsz;
				if (count > 0) {
					fwrite(&xbuff[3], 1, count, f);
					len += count;
				}
				++packetno;
				retrans = MAXRETRANS+1;
			}
			if (--retrans <= 0) {
				flushinput();
				_outbyte(CAN);
				_outbyte(CAN);
				_outbyte(CAN);
				FCLOSE(f);
				return -3; /* too many retry error */
			}
			_outbyte(ACK);
			continue;
		}
	reject:
		flushinput();
		_outbyte(NAK);
	}
}

int main(int argc, char **argv)
{
	long st;

	fprintf(stdout, "ymodem by Scott Baker, based on xmodem by Georges Menie\n");
	fprintf(stdout, "Modified for Olivetti M20 by Scott Baker, www.smbaker.com.\n");

	if (argc>1) {
		fprintf(stderr, "syntax: ymodemr\n");
		exit(1);
	}

	printf ("Send data using the ymodem protocol from your terminal emulator now...\n");
	st = ymodemReceive();
	if (st < 0) {
		printf ("Ymodem receive error: status: %ld\n", st);
	}
	else  {
		printf ("Ymodem successfully received %ld bytes\n", st);
	}

	return 0;
}

