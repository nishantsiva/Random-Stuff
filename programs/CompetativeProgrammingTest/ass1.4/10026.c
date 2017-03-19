#include<stdio.h>
#include<stdlib.h>

struct Tasks
{
	int num;
	float ratio;
};

int compare (const void * p1, const void * p2)
{
	struct Tasks *ptr1 = (struct Tasks*)p1;
	struct Tasks *ptr2 = (struct Tasks*)p2;
	float diff;
	diff = ptr2->ratio - ptr1->ratio;
	if(diff > 0) return 1;
	if(diff < 0) return -1;
	return 0;
}

int
main (int argc, char *argv[])
{
	struct Tasks *tasks;
	int noTasks,T,i,j;
	int fine,time;
	scanf("%d",&T);
	for(i=0;i<T;i++){
		scanf("%d",&noTasks);
		tasks = (struct Tasks*)malloc(sizeof(struct Tasks) * (noTasks));
		for(j=0;j<noTasks;j++){
			scanf("%d %d",&time,&fine);
			tasks[j].ratio = (float)fine / (float)time;
			tasks[j].num = j + 1;
		}
		qsort (tasks, noTasks, sizeof(struct Tasks), compare);
		for(j=0;j<noTasks;j++){
			if(j > 0) printf(" ");
			printf("%d",tasks[j].num);
		}
		printf("\n");
		if(i < T-1) printf("\n");
		free(tasks);
	}
	return 0;
}
