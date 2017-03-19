#include<stdio.h>
#define MAXN    257

main(){
	int p[MAXN][MAXN];
	int n,teams,i,j;
	scanf("%d",&n);
	teams = 1 << n;printf("n %d\n",teams);
    for(i=0;i<teams;i++){
        for(j=0;j<teams;j++){
            scanf("%d",&p[i][j]);
        }
    }
}
