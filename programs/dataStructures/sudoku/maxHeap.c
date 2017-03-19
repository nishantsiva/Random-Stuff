#include<stdio.h>
#include<stdlib.h>

struct HeapNode{
	int val;
};

struct Heap{  
	struct HeapNode *arr;
	int count;
	int capacity;
};

void heapInsert(struct Heap *list,int value)
{
	int now;
	list->count++;
	list->arr[list->count].val = value;
	/*Adjust its position*/
	now = list->count;
	while(list->arr[now/2].val < value && now/2 > 0) 
	{
		list->arr[now] = list->arr[now/2];
		now /= 2;
	}
	list->arr[now].val = value;
}

int heapExtractMin(struct Heap *list)
{
	struct HeapNode minElement,lastElement;
	int child,now;
	if(list->count == 0){
		return -1;
	}
	minElement = list->arr[1];
	lastElement = list->arr[list->count--];
	/* now refers to the index at which we are now */
	for(now = 1; now*2 <= list->count; now = child)
	{
		/* child is the index of the element which is minimum among both the children */ 
		/* Indexes of children are i*2 and i*2 + 1*/
		child = now*2;
		/*child!=heapSize beacuse heap[heapSize+1] does not exist, which means it has only one 
		child */
		if(child != list->count && list->arr[child].val < list->arr[child+1].val) 
		{
			child++;
		}
		/* To check if the last element fits ot not it suffices to check if the last element
		is less than the minimum element among both the children*/
		if(lastElement.val < list->arr[child].val)
		{
			list->arr[now] = list->arr[child];
		}
		else /* It fits there */
		{
			break;
		}
	}
	list->arr[now] = lastElement;
	return minElement.val;
}

main(){
	int i,ret,minCount = 5;
	int array[] = {5,3,6,23,1};
	struct Heap *heapList;
	heapList = (struct Heap*)malloc(sizeof(struct Heap));
	heapList->count = 0;
	heapList->capacity = minCount;
	heapList->arr = (struct HeapNode*)malloc((minCount+1)*sizeof(struct HeapNode));
	for(i=0;i<minCount;i++){
		heapInsert(heapList,array[i]);
	}
	heapList->arr[0].val = -1;
	while(1){
		//printf("%d ",heapList->arr[i].val);
		ret = heapExtractMin(heapList);
		if(ret == -1)
			break;
		printf("%d ",ret);
	}
	printf("\n");
}
