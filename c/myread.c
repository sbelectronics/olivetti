/* $Id: read.c,v 1.19 2004/05/22 22:07:46 chris Exp $ */

/* fixes a bug when the input buffer is full */

#include <sys/types.h>
#include <sys/param.h>
#include <sys/pcos.h>
#include <errno.h>
#include "myread.h"

#define LB_LEN 82
static unsigned char mylinebuffer[LB_LEN];
static int mylblen = 0, mylbix = 0;

static int _mygetbyte_linebuffered(int did, unsigned char *byte)
{
    unsigned char c;

    if (! mylblen || mylbix >= mylblen) {  /* line buffer empty, get data */
        int retval;
        for (mylbix = 0; mylbix < LB_LEN; mylbix++) {
          again:
            retval = _pcos_getbyte(did, &c);
            if (retval) {
                return(retval);
            }
            if (c == 8) {            /* ^H */
                if (mylbix) {
                    mylbix--;
                    _pcos_putbyte(did, c);
                    _pcos_putbyte(did, ' ');
                    _pcos_putbyte(did, c);
                }
                goto again;
            }

            if (c == 3) {            /* ^C */
                mylbix = 0;
                *byte = 3;
                return(PCOS_ERR_OK);
            }

            mylinebuffer[mylbix] = c;
            if (c == 4 || c == 26) { /* ^D or ^Z (EOF) */
                break;
            }
            _pcos_putbyte(did, c);   /* echo typed char */
            if (c == '\r') {
                mylinebuffer[mylbix] = '\n';
                _pcos_putbyte(did, '\n');
                break;
            }
        }

        /* There's a buf here in z8kgcc. If the input buffer is maxxed out,
         * then we'll end up including one garbage character in the returned
         * result.
         */

        if (mylbix>=LB_LEN) {
            mylblen = mylbix;  /* fix is here */
        } else {
            mylblen = mylbix + 1;
        }
        mylbix = 0;
    }

    *byte = mylinebuffer[mylbix];
    mylbix++;

    return(PCOS_ERR_OK);
}

int _myread(void *buf, size_t nbytes)
{
    int retval;
    unsigned int i, nbytesi = nbytes;   /* nbytes: nbytes as int */
    unsigned char *cbuf = buf;

    if (! nbytes) return(nbytes);

    _pcos_selectcur(2);  /* turn on cursor */
    for (i=0; i<nbytes; i++) {
        unsigned char c;

        retval = _mygetbyte_linebuffered(DID_CONSOLE, &c);
        if (retval) {
            _pcos_selectcur(0);   /* turn off cursor */
            errno = errno_from_pcos_err(retval);
            return(-1);
        }

        if (c == 3) {    /* ^C */
            _pcos_putbyte(DID_CONSOLE, '^');
            _pcos_putbyte(DID_CONSOLE, 'C');
            _pcos_putbyte(DID_CONSOLE, '\r');
            _pcos_putbyte(DID_CONSOLE, '\n');
            _pcos_selectcur(0);
            exit(130);
        }

        *(cbuf + i) = c;
        if (c == '\n') {
            i++;
            goto lineend;
        }
        if (c == 4 || c == 26) {  /* ^D or ^Z (EOF) */
            lineend:
            _pcos_selectcur(0);   /* turn off cursor */
            return(i);
        }
    }
    _pcos_selectcur(0);   /* turn off cursor */

    retval = nbytesi;
    return(retval);
}
