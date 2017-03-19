#include<stdio.h>
#include<stdlib.h>

int
main (int argc, char *argv[])
{
	int n,m,k,i,j,k,node1,node2;
	int **graph,**A;
	scanf("%d %d %d",&n,&m,&k);
	while(n!=0 || m!=0 || k!=0){
		graph = (int**)malloc(sizeof(int*)*n);
		A = (int**)malloc(sizeof(int*)*n);
		for(i=0;i<n;i++){
			graph[i] = (int*)calloc(n,sizeof(int));
			A[i] = (int*)calloc(n,sizeof(int));
		}
		for(i=0;i<m;i++){
			scanf("%d %d",&node1,&node2);
			graph[node1][node2] = 1;
		}
		for(i=0;i<k;i++){
			for(j=0;j<n;j++){
				
			}
		}
		retVal = calculate(n,k,0,1);
		if(retVal == -1){
			printf("LOSER\n");
		}
		else{
			printf("%d\n",retVal);
		}
		for(i=0;i<n;i++){
			free(graph[i]);
		}
		free(graph);
		scanf("%d %d %d",&n,&m,&k);
	}
	return 0;
}
