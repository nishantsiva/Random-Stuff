#include<stdio.h>
#include<stdlib.h>

#define MAX_ORDER 100
#define MIN(A,B) ((A)<(B))?(A):(B)

float costArr[MAX_ORDER + 1];

int main(){
	int M,K,offset,item,count;
	int i,j;
	float cost;
	char buf[500];
	char *bufptr;
	item = 1;
	while(scanf("%f %d\n",&cost,&M) == 2) {
		for(i = 0; i <= MAX_ORDER; i++){
			costArr[i] = i * cost;
		}
		for(i = 1; i <= M; i++){
			scanf("%d %f\n",&count,&cost);
			for(j = 1; j <= MAX_ORDER; j++){
				if(j > count){
					costArr[j] = MIN(cost + costArr[j - count], costArr[j]);
				}
				else{
					costArr[j] = MIN(cost, costArr[j]);
				}
			}
		}
		fgets(buf, sizeof(buf), stdin);
		printf("Case %d:\n",item++);
		bufptr = buf;
		while(sscanf(bufptr,"%d%n",&K,&offset) == 1){
			printf("Buy %d for $%.2f\n",K,costArr[K]);
			bufptr += offset;
		}
	}
	return 0;
}
