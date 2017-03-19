#include<stdio.h>
#include<stdlib.h>

struct Emps {
	int salary;
	int incriment;	//Increment for subordinates
	int boss;		//employee number of boss
};

struct Emps *empArr;

/*
 * Reccursively call supervisors and find the increments to get updated salary
 */
int getIncrement(int emp){
	if(empArr[emp].boss == -1){
		return 0;
	}
	return empArr[empArr[emp].boss].incriment + getIncrement(empArr[emp].boss);
}

int main (int argc, char *argv[]) {
	int N,M,A,X;
	int i;
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
			empArr[A].incriment += X; //Updates the increment in supervisor
		}
		else if (ch == 'u') {
			scanf("%d",&A);
			printf("%d\n",empArr[A].salary + getIncrement(A));
		}
	}
	return 0;
}
