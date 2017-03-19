#include<stdio.h>
#include<stdlib.h>

struct node{
	struct Task *adjNode;
	struct node *next;
};

struct Task{
	int taskNo,visited;
	struct node *children;
	struct Task *next;
};

int
main (int argc, char *argv[])
{
	struct Task *start,*taskPtr,*taskPtr1,**taskArr;
	struct node *ptr;
	int i,t,m,p,c,time,minc,temp;
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
		taskPtr->taskNo = i;
		taskPtr->visited = 0;
		taskPtr->next = NULL;
		taskPtr->children = NULL;
	}
	for(i=0;i<m;i++){
		scanf("%d %d",&p,&c);
		if(taskArr[p]->children == NULL){
			taskArr[p]->children = (struct node*)malloc(sizeof(struct node));
			taskArr[p]->children->adjNode = taskArr[c];
			taskArr[p]->children->next = NULL;
		}
		else{
			ptr = taskArr[p]->children;
			while(ptr->next != NULL){
				ptr = ptr->next;
			}
			ptr->next = (struct node*)malloc(sizeof(struct node));
			ptr->next->adjNode = taskArr[c];
			ptr->next->next = NULL;
		}
	}
	time = 0;
	minc = 0;
	while(start != NULL){
		temp = 0;
		taskPtr = taskPtr1 = start;
		while(taskPtr){
			if(taskPtr->children == NULL){
				if(taskPtr == start){
					start = taskPtr->next;
				}
				else{
					taskPtr1->next = taskPtr->next;
				}
				temp++;
				taskPtr->visited = 1;
			}
			taskPtr1 = taskPtr;
			taskPtr = taskPtr->next;
		}
		time++;
		if(temp>minc) minc = temp;
		taskPtr = start;
		while(taskPtr){
			while(taskPtr->children != NULL && taskPtr->children->adjNode->visited == 1){
				taskPtr->children = taskPtr->children->next;
			}
			ptr = taskPtr->children;
			taskPtr = taskPtr->next;
			if(ptr == NULL)
				continue;
			while(ptr->next != NULL){
				if(ptr->next->adjNode->visited == 0){
					ptr = ptr->next;
				}
				else{
					ptr->next = ptr->next->next;
				}
			}
		}
	}
	printf("%d %d\n",time,minc);
	return 0;
}
