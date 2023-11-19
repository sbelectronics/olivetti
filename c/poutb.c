/*
 * From http://www.z80ne.com/m20/sections/download/z8kgcc/z8kgcc.html#Examples
 * Christian Groessler
 * 
 * GNU Free Documentation License
 * 
 * write a byte to a port
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
    unsigned long value;

    if (argc != 3) {
        fprintf(stderr, "usage: poutb <port address> <value>\n");
        return 1;
    }

    /* get port address */
    portaddr = strtoul(*(argv + 1), &endptr, 0);
    if (portaddr > 0xffff || *endptr) {
        fprintf(stderr, "invalid port address!\n");
        return 1;
    }

    /* get value */
    value = strtoul(*(argv + 2), &endptr, 0);
    if (value > 0xff || *endptr) {
        fprintf(stderr, "invalid value!\n");
        return 1;
    }

    printf("writing 0x%02lx (%lu) to port 0x%04lx (%lu)",
            value, value, portaddr, portaddr);
    if (! (portaddr & 1))
        printf("\t\tWARNING: even port address!");
    printf("\n");

    __asm__ volatile (
        "push @sp,r7   \n\t"
        "ld r7,%H1     \n\t"
        "outb @%H0,rl7 \n\t"
        "pop r7,@sp    \n\t": : "r" ((unsigned int)portaddr),
                                "r" ((unsigned int)value));

    return 0;
}

