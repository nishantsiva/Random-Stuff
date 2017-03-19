#include<stdio.h>
#include<stdlib.h>

struct Emps {
	int salary,incriment,boss;
};

struct Emps *empArr;

int main (int argc, char *argv[]) {
	int N,M,A,X,sum;
	int i,j;
	char ch;
	struct Node *ptr;
	scanf("%d %d",&N,&M);
	empArr = (struct Emps*)malloc(sizeof(struct Emps) * (N + 1));
	for(i = 1; i <= N; i++){
		empArr[i].incriment = 0;
		if(i == 1){
			scanf("%d",&empArr[i].salary);
			empArr[i].boss = -1;
		}
		else{
			scanf("%d %d",&empArr[i].salary,&empArr[i].boss);
		}
	}
	for(i = 0; i < M; i++){
		ch = '\0';
		while(ch != 'p' && ch != 'u'){
			scanf("%c",&ch);
		}
		if(ch == 'p'){
			scanf("%d %d",&A,&X);
			empArr[A].incriment += X;
		}
		else if (ch == 'u') {
			scanf("%d",&A);
			sum = empArr[A].salary;
			for(j = empArr[A].boss; j != -1; j = empArr[j].boss){
				sum += empArr[j].incriment;
			}
			printf("%d\n",sum);
		}
	}
	return 0;
}
