#include <stdio.h>
#include <stdlib.h>

#define MAXN 1001

int main (int argc, char *argv[]) {
	int Arr[MAXN][MAXN];
	int cases, i, j, N;
	char s[MAXN];
	scanf("%d",&cases);
	while (cases--) {
		scanf("%d",&N);
		for (i = 0; i < N; i += 1) {
			scanf("\n%s", s);
			for (j = 0; j < N; j += 1) {
				switch (s[j]) {
					case '.' : Arr[i][j] = 0; break;
					case '#' : Arr[i][j] = 1; break;
					default  : printf("Input Error");
				}
			}
		}
/*		UP		: -1	*/
/*		DOWN	: 1		*/
/*		LEFT	: -2	*/
/*		RIGHT	: 2		*/
	
	}
	return 0;
}
