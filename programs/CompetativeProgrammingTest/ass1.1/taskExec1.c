#include<stdio.h>
#include<stdlib.h>

struct Task{
	int taskNo,visited;
	int *adjNodes,adjCount;
	int flag;
	struct Task *next;
};

int
main (int argc, char *argv[])
{
	struct Task *start,*taskPtr,*taskPtr1,*taskPtr2,**taskArr;
	int i,t,m,p,c,time,minc,temp,flag;
	scanf("%d %d",&t,&m);
	start = NULL;
	taskArr = (struct Task**)malloc(sizeof(struct Task*) * (t+1));
	for(i=1;i<=t;i++){
		if(start == NULL){
			start = (struct Task*)malloc(sizeof(struct Task));
			taskPtr = start;
		}
		else{
			taskPtr->next = (struct Task*)malloc(sizeof(struct Task));
			taskPtr = taskPtr->next;
		}
		taskArr[i] = taskPtr;
		taskPtr->adjNodes = (int*)calloc(t+1,sizeof(int));
		taskPtr->adjCount = 0;
		taskPtr->flag = 0;
		taskPtr->taskNo = i;
		taskPtr->visited = 0;
		taskPtr->next = NULL;
	}
	for(i=0;i<m;i++){
		scanf("%d %d",&p,&c);
		taskArr[p]->adjNodes[c] = 1;
		taskArr[p]->adjCount++;
	}
	time = 0;
	minc = 0;
	flag = 0;
	while(start != NULL){
		temp = 0;
		taskPtr = taskPtr1 = start;
		while(taskPtr){
			if(taskPtr->adjCount == 0 && taskPtr->flag == flag){
				if(taskPtr == start){
					start = taskPtr->next;
				}
				else{
					taskPtr1->next = taskPtr->next;
				}
				temp++;
				taskPtr->visited = 1;
				taskPtr2 = start;
				while(taskPtr2){
					if(taskPtr2->adjNodes[taskPtr->taskNo] == 1){
						taskPtr2->adjNodes[taskPtr->taskNo] = 0;
						taskPtr2->adjCount--;
						taskPtr2->flag = !flag;
					}
					taskPtr2 = taskPtr2->next;
				}
			}
			else
				taskPtr1 = taskPtr;
			taskPtr = taskPtr->next;
		}
		time++;
		if(temp>minc) minc = temp;
		flag = flag?0:1;
	}
	printf("%d %d\n",time,minc);
	return 0;
}
