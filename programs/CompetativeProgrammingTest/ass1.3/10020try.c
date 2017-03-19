#include<stdio.h>
#include<stdlib.h>

struct Line
{
	int left,right,selected;
	struct Line *next;
};

int compare (const void * p1, const void * p2)
{
	struct Line *a = *(struct Line**)p1;
	struct Line *b = *(struct Line**)p2;
	int retVal;
	retVal = (b->right) - (a->right);
	return retVal;
}

int
main (int argc, char *argv[])
{
	struct Line *start,*linePtr,**lineArr;
	int i,j,T,M,L,R,lineCount,lowerBound,selectedCount;
	scanf("%d",&T);
	for(i=0;i<T;i++){
		scanf("%d",&M);
		scanf("%d %d",&L,&R);
		start = NULL;
		lineCount = 0;
		while(L!=0 || R!=0){
			if(R > 0){
				if(start == NULL){
					start = (struct Line*)malloc(sizeof(struct Line));
					linePtr = start;
				}
				else{
					linePtr->next = (struct Line*)malloc(sizeof(struct Line));
					linePtr = linePtr->next;
				}
				linePtr->left = L;
				linePtr->right = R;
				linePtr->next = NULL;
				linePtr->selected = 0;
				lineCount++;
			}
			scanf("%d %d",&L,&R);
		}
		lineArr = (struct Line**)malloc(sizeof(struct Line*)*lineCount);
		for(j = 0, linePtr = start; linePtr != NULL; j++, linePtr = linePtr->next){
			lineArr[j] = linePtr;
		}
		qsort (lineArr, lineCount, sizeof(struct Line*), compare);
		/*for(j=0;j<lineCount;j++){printf("%d %d\n",lineArr[j]->left,lineArr[j]->right);}*/
		lowerBound = 0;
		selectedCount = 0;
		while(lowerBound < M){
			for(j = 0; j < lineCount; j++){
				if(lineArr[j]->left <= lowerBound){
					lineArr[j]->selected = 1;
					selectedCount++;
					lowerBound = lineArr[j]->right;
					break;
				}
			}
			if(j == lineCount)
				break;
		}
		if(lowerBound < M){
			printf("0\n");
		}
		else{
			printf("%d\n",selectedCount);
			for(j=lineCount-1;j>=0;j--){
				if(lineArr[j]->selected == 1)
					printf("%d %d\n",lineArr[j]->left,lineArr[j]->right);
			}
		}
		printf("\n");
		free(lineArr);
		linePtr = start->next;
		while(start){
			free(start);
			start = linePtr;
			if(linePtr){
				linePtr = linePtr->next;
			}
		}
	}
	return 0;
}
