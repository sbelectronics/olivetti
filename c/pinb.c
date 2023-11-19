/*
 * From http://www.z80ne.com/m20/sections/download/z8kgcc/z8kgcc.html#Examples
 * Christian Groessler
 * 
 * GNU Free Documentation License
 * 
 * read a byte from a port and display it
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

int main(int argc, char **argv)
{
    unsigned long portaddr;
    char *endptr;
    unsigned char value;

    if (argc != 2) {
        fprintf(stderr, "usage: pinb <port address>\n");
        return 1;
    }

    /* get port address */
    portaddr = strtoul(*(argv + 1), &endptr, 0);
    if (portaddr > 0xffff || *endptr) {
        fprintf(stderr, "invalid port address!\n");
        return 1;
    }

    printf("reading from port 0x%04lx (%lu)", portaddr, portaddr);
    if (! (portaddr & 1))
        printf("\t\tWARNING: even address!");
    printf("\n");

    __asm__ volatile (
        "inb %Q0,@%H1 \n\t" : "=r" (value)
                            : "r" ((unsigned int)portaddr));

    printf("Port value: 0x%02x  (%u)\n", value, value);

    return 0;
}
