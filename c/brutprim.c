/*
 * brutprim.c: The world's worst prime number generator.
 */

#include <stdio.h>

int main() 
{
    int l,n,d,p;

    printf("LIMIT ? ");
    scanf("%d", &l);

    for (n=3; n<=l; n++) {
        p=1;
        for (d=2; d<=(n-1); d++) {
            if ((n % d)==0) {
                putchar('.');
                p=0;
                break;
            }
        }
        if (p) {
            printf("%d ", n);
        }
    }
    printf("\n");
} 
