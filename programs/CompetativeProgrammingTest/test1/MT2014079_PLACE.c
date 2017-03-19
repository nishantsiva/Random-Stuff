#include<stdio.h>
#include<stdlib.h>

struct Node {
	int empNo;
	struct Node *next;
};

struct Emps {
	int salary;
	struct Node *subs;
};

struct Emps *empArr;

struct Node* createNode(int val){
	struct Node *ptr = (struct Node*)malloc(sizeof(struct Node));
	ptr->empNo = val;
	ptr->next = NULL;
	return ptr;
}

void changeSalary(int boss, int val){
	struct Node *ptr;
	if(empArr[boss].subs == NULL){
		return;
	}
	ptr = empArr[boss].subs;
	while(ptr){
		empArr[ptr->empNo].salary += val;
		changeSalary(ptr->empNo,val);
		ptr = ptr->next;
	}
}

int main (int argc, char *argv[]) {
	int N,M,A,X,boss;
	int i;
	char ch;
	struct Node *ptr;
	scanf("%d %d",&N,&M);
	empArr = (struct Emps*)malloc(sizeof(struct Emps) * (N + 1));
	for(i = 1; i <= N; i++){
		empArr[i].subs = NULL;
	}
	for(i = 1; i <= N; i++){
		if(i == 1){
			scanf("%d",&empArr[i].salary);
		}
		else{
			scanf("%d %d",&empArr[i].salary,&boss);
			if(empArr[boss].subs == NULL){
				empArr[boss].subs = createNode(i);
			}
			else{
				ptr = empArr[boss].subs;
				while (ptr->next != NULL) {
					ptr = ptr->next;
				}
				ptr->next = createNode(i);
			}
		}
	}
	for(i = 0; i < M; i++){
		ch = '\0';
		while(ch != 'p' && ch != 'u'){
			scanf("%c",&ch);
		}
		if(ch == 'p'){
			scanf("%d %d",&A,&X);
			changeSalary(A,X);
		}
		else if (ch == 'u') {
			scanf("%d",&A);
			printf("%d\n",empArr[A].salary);
		}
	}
	return 0;
}
