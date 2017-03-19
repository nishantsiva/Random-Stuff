#include<stdio.h>

#define MAX(x,y) (((x)>(y))?(x):(y))

int p[] = {23, 28, 33};
int s[3], d;

int findNext(int max, int maxi) {
	int j, i, flag1, flag2;
	for (j = max; j < 21253; j += p[maxi])
	{
		flag1 = flag2 = 0;
		if (j > 0)
		{
			for (i = 0; i < 3; ++i)
			{
				if(i != maxi){
					if((j - s[i])%p[i] != 0) break;
					if(flag1 == 0) { flag1 = 1; continue;}
					flag2 = 1; break;
				}
			}
			if(flag1 == 1 && flag2 == 1)
				return j;
		}
	}
	return -1;
}

int main(int argc, char const *argv[])
{
	int max, retVal, maxi, i;
	scanf("%d %d %d %d", &s[0], &s[1], &s[2], &d);
	for (i = 0; i < 3; ++i) s[i] -= d;

	max = MAX(MAX(s[0],s[1]),s[2]);
	for (i = 0; i < 3; ++i) {
		if(s[i] == max) {
			maxi = i; 
			break;
		}
	}

	printf("%d\n", findNext(max, maxi));
	return 0;
}