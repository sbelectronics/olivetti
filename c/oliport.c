#include "oliport.h"

void outp(unsigned int portAddr, unsigned char value)
{
    volatile unsigned int portAddr1;
    volatile unsigned char value1;

    /* compensate for compiliter optimization bug?? */
    portAddr1 = portAddr;
    value1 = value;

    __asm__ volatile (
        "push @sp,r7   \n\t"
        "ld r7,%H1     \n\t"
        "outb @%H0,rl7 \n\t"
        "pop r7,@sp    \n\t": : "r" ((unsigned int)portAddr1),
                                "r" ((unsigned int)value1));
}

unsigned char inp(unsigned int portAddr)
{
    unsigned char value;
    __asm__ volatile (
        "inb %Q0,@%H1 \n\t" : "=r" (value)
                            : "r" ((unsigned int)portAddr));

    return value;
}
