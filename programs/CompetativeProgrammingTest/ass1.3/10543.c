#include<stdio.h>
#include<stdlib.h>

struct node
{
	int wtToLast,noAdj;
	int *adjs;
};

struct node *graphStruct;
int **graph;

int
calculate(int noNodes,int leastCount,int curNode,int length){
	int i,retVal = -1;
	if(length > 20){
		return -1;
	}
	if(curNode == noNodes-1 && length >= leastCount){
		return length;
	}
	for(i = 0; i < graphStruct[curNode].noAdj; i++){
		retVal = calculate(noNodes,leastCount,graphStruct[curNode].adjs[i],length+1);
		if(retVal != -1){
			break;
		}
	}
	return retVal;
}


void
findWtToLast(int curr,int noNodes,int hopes){
	int i;
	if(hopes >= graphStruct[curr].wtToLast){
		return;
	}
	graphStruct[curr].wtToLast = hopes;
	for(i=0;i<noNodes;i++){
		if(graph[i][curr] == 1){
			findWtToLast(i,noNodes,hopes+1);
		}
	}
}

int
compare (const void * p1, const void * p2)
{
	return ( graphStruct[*(int*)p1].wtToLast - graphStruct[*(int*)p2].wtToLast );
}

int
main (int argc, char *argv[])
{
	int n,m,k,i,retVal,node1,node2;
	scanf("%d %d %d",&n,&m,&k);
	while(n!=0 || m!=0 || k!=0){
		graph = (int**)malloc(sizeof(int*)*n);
		graphStruct = (struct node *)malloc(sizeof(struct node)*n);
		for(i=0;i<n;i++){
			graph[i] = (int*)calloc(n,sizeof(int));
			graphStruct[i].wtToLast = n+1;
			graphStruct[i].noAdj = 0;
			graphStruct[i].adjs = (int*)malloc(sizeof(int)*n);
		}
		for(i=0;i<m;i++){
			scanf("%d %d",&node1,&node2);
			graph[node1][node2] = 1;
			graphStruct[node1].adjs[graphStruct[node1].noAdj++] = node2;
		}
		findWtToLast(n-1,n,0);
		for(i=0;i<n;i++){
			printf("%d ",graphStruct[i].wtToLast);
		}
		printf("\n");
		for(i=0;i<n;i++){
			qsort (graphStruct[i].adjs, graphStruct[i].noAdj, sizeof(int), compare);
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
