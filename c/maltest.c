/* Test malloc
 *
 * I wanted to prove to myself that z8kgcc will malloc from segments other than
 * BSS, DATA, and TEXT. It surely does.
 * 
 */

#include <stdlib.h>
#include <stdio.h>

char str_bss[1000];
char str_data[1000] = "data";

int main(int argc, char **argv)
{
    char *blocks[32];
    char str_stack[10];
    int i;
    int j;

    printf("str_stack: %p\n", str_stack);
    printf("str_bss: %p\n", str_bss);
    printf("str_data: %p\n", str_data);
    printf("code: %p\n", main);

    printf("allocating 32 blocks of 8K each...\n");
    for(i=0; i<32; i++) {
        blocks[i] = (char*) malloc(8192);
        printf("%d: addr %p\n", i, blocks[i]);

        for(j=0; j<8192; j++) {
            *(blocks[i]+j) = ((i+j)&0xFF);
        }
    }

    printf("testing 32 blocks of 8K each...\n");
    for(i=0; i<32; i++) {
        for(j=0; j<8192; j++) {
            if (*(blocks[i]+j) != ((i+j)&0xFF))  {
                printf("mismatch block %d addr %d\n", i, j);
                exit(-1);
            }
        }
    }    
}
