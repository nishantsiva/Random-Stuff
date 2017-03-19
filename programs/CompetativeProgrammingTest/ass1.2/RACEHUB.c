#include<stdio.h>
#include<stdlib.h>

int compare (const void * p1, const void * p2)
{
	int *a = (int*)p1;
	int *b = (int*)p2;
	return ( *a > *b ) - (*a < *b);
}

int
main (int argc, char *argv[])
{
	int *x,*dist;
	int r,l,i,sum,hub,max;
	long long b,temp;
	scanf("%d %d %lld",&r,&l,&b);
	x = (int*)malloc(sizeof(int)*r);
	for(i=0;i<r;i++){
		scanf("%d",&x[i]);
	}
	dist = (int*)malloc(sizeof(int)*r);
	max = 0;
	for(hub = x[0]; hub <= x[r-1]; hub++){
		for(i=0;i<r;i++){
			dist[i] = abs(hub - x[i]);
		}
		qsort (dist, r, sizeof(int), compare);
		temp = b;
		for(i=0;i<r;i++){
			if((temp - dist[i]) >= 0)
				temp -= dist[i];
			else
				break;
		}
		if(i>max)
			max = i;
	}
	printf("%d\n",max);
	return 0;
}
