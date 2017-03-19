#include<stdio.h>
#include<stdlib.h>

struct node
{
	int index;
	struct node *next,*prev;
};

struct node*
createNode(struct node *prev,int index){
	struct node *ptr = (struct node*)malloc(sizeof(struct node));
	ptr->index = index;
	ptr->prev = prev;
	ptr->next = NULL;
	return ptr;
}

int
main (int argc, char *argv[])
{
	struct node *start,*last,*ptr;
	int sum,n,*arr,i,j,tempSum,nextIndex,change,isEmpty,usedVal,complete;
	char out1[5],out2[50];
	scanf("%d %d",&sum,&n);
	while(n!=0){
		arr = (int*)malloc(sizeof(int)*n);
		for(i=0;i<n;i++){
			scanf("%d",&arr[i]);
		}
		printf("Sums of %d:\n",sum);
		nextIndex = 0;
		tempSum = sum;
		isEmpty = 1;
		start = NULL;
		while(1){
			change = 0;
			if(nextIndex >= n){
				change = 1;
			}
			else{
				while(tempSum - arr[nextIndex] < 0){
			
					if(++nextIndex >= n){
						change = 1;
						break;
					}
				}
			}
			if(change == 0){
				if(start == NULL){
					last = start  = createNode(NULL,nextIndex);
				}
				else{
					last->next = createNode(last,nextIndex);
					last = last->next;
				}
				tempSum -= arr[nextIndex];
				nextIndex++;
			
				if(tempSum == 0){
					printf("%d",arr[start->index]);
					ptr = start->next;
					while(ptr){
						printf("+%d",arr[ptr->index]);
						ptr = ptr->next;
					}
					printf("\n");
					isEmpty = 0;
				}
			}
			if(change == 1){
				complete = 0;
				while(1){
					if(start == NULL){
						complete = 1;
						break;
					}
					usedVal = arr[last->index];
					nextIndex = last->index;
					tempSum += usedVal;
					if(last->prev == NULL){
						last = start = NULL;
					}
					else{
						last = last->prev;
						last->next = NULL;
					}
					while(nextIndex < n){
						if(arr[++nextIndex] != usedVal){
							break;
						}
					}
					if(nextIndex < n){
						break;
					}
				}
				if(complete){
					break;
				}
			}
		}
		if(isEmpty){
			printf("NONE\n");
		}
		scanf("%d %d",&sum,&n);
	}
	return 0;
}
