#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void atxy(int x, int y)
{
#ifdef OLIVETTI
    _pcos_chgcur0(x,y);
#else
    printf("%c[%d;%df",0x1B,y,x);
#endif
}

#define for_x for (x = 0; x < w; x++)
#define for_y for (y = 0; y < h; y++)
#define for_xy for_x for_y
void show(void *u, int w, int h)
{
	int (*univ)[w] = u;
	int x,y;
	atxy(0,0);
	for_y {
		for_x printf(univ[y][x] ? "*" : " ");
		printf("\n");
	}
	fflush(stdout);
}

void evolve(void *u, int w, int h)
{
	unsigned (*univ)[w] = u;
	unsigned new[h][w];
	int x,y,y1,x1;

	for_y for_x {
		int n = 0;
		for (y1 = y - 1; y1 <= y + 1; y1++)
			for (x1 = x - 1; x1 <= x + 1; x1++)
				if (univ[(y1 + h) % h][(x1 + w) % w])
					n++;

		if (univ[y][x]) n--;
		new[y][x] = (n == 3 || (n == 2 && univ[y][x]));
	}
	for_y for_x univ[y][x] = new[y][x];
}

void clearboard(void *u, int w, int h)
{
	unsigned (*univ)[w] = u;
	int x,y;
	for_xy univ[y][x] = 0;
}

void randomboard(void *u, int w, int h)
{
	unsigned (*univ)[w] = u;
	int x,y;
	for_xy univ[y][x] = rand() < RAND_MAX / 10 ? 1 : 0;
}

void pat(void *u, int w, int h, char *s)
{
	int x,y;
	unsigned (*univ)[w] = u;
	
	/* start a few cells in so that the initial
	 * object doesn't wrap.
	 */

	x=2;
	y=2;

	while (*s) {
		if (*s=='*') {
			univ[y][x]=1;
			x+=1;
		} else if (*s=='|') {
			x=2;
			y+=1;
		} else {
			x+=1;
		}
		s+=1;
	}
}

void game(void *u, int w, int h)
{
	unsigned (*univ)[w] = u;

	int x,y;
	
	while (1) {
		show(univ, w, h);
		evolve(univ, w, h);
		usleep(50000);
		//sleep(1);
	}
}

// : glider s"  *|  *|***" pat ;
// : ship s"  ****|*   *|    *|   *" pat ;

int param_to_i(char *s)
{
    unsigned long n;
    char *endptr;
    n = strtoul(s, &endptr, 0);
    if (*endptr) {
		return -1;
    }

    return (int) n;
}


int main(int c, char **v)
{
	int w = 0, h = 0;
	int i, hit;

	for (i=1; i<c; i++) {
		int j = param_to_i(v[i]);

		if (j>0) {
			if (w==0) {
				w=j;
			} else {
				h=j;
			}
		}
	}


	if (w <= 0) w = 30;
	if (h <= 0) h = 16;
    {
		unsigned univ[h][w];
		clearboard(univ, w, h);

        hit=0;
	    for (i=1; i<c; i++) {
			switch (v[i][0]) {
				case 'g':
				case 'G':
				   pat(univ, w, h, " *|  *|***");
				   hit=1;
				   break;

				case 's':
				case 'S':
				   pat(univ, w, h, " ****|*   *|    *|   *");
				   hit=1;
				   break;

				case 'c':
				case 'C':
				   pat(univ, w, h, " *|  **|**|  *");
				   hit=1;
				   break;

				case 'p':
				case 'P':
				   pat(univ, w, h, "*****|*   *");
				   hit=1;
				   break;					   

				case 'i':
				case 'I':
				   pat(univ, w, h, "**| **|**");
				   hit=1;
				   break;				   
			}
		}

		if (!hit) {
			randomboard(univ, w, h);
		}

		
	    game(univ, w, h);		
	}
}
