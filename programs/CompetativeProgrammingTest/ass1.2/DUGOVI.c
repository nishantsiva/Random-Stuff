#include<stdio.h>
#include<stdlib.h>

struct node
{
	int to,debt,fromCount,balance,visited;
	int next,prev;
};

struct node **person;
int start = 1;

int
visit(int curr){
	int balance,j;
	if(person[curr]->fromCount != 0){
		return 0;
	}
	person[curr]->visited = 1;
	person[person[curr]->to]->fromCount--;
	person[person[curr]->to]->balance += person[curr]->debt;
	
	if(start == curr){
		start = person[curr]->next;
		if(start != -1)
			person[person[curr]->next]->prev = -1;
	}
	else if(person[curr]->next == -1){
		person[person[curr]->prev]->next = -1;
	}
	else{
		person[person[curr]->prev]->next = person[curr]->next;
		person[person[curr]->next]->prev = person[curr]->prev;
	}
	
	if(person[curr]->debt - person[curr]->balance >= 0 ){
		balance = person[curr]->debt - person[curr]->balance;
		person[curr]->balance = 0;
	}
	else{
		balance = 0;
		person[curr]->balance -= person[curr]->debt;
	}
	//printf("3 %d\n",balance);for(j=1;person[j] != NULL;j++){printf("\t%d : %d %d %d %d\n",j,person[j]->to,person[j]->debt,person[j]->fromCount,person[j]->balance);};
	return balance + visit(person[curr]->to);
}

int
main (int argc, char *argv[])
{
	int i,n,totalMoney = 0,j;
	int candidate,candidateDebt;
	scanf("%d",&n);
	person = (struct node**)malloc(sizeof(struct node*)*(n+1));
	for(i=1;i<=n;i++){
		person[i] = (struct node*)malloc(sizeof(struct node));
		person[i]->fromCount = 0;
		person[i]->balance = 0;
		person[i]->visited = 0;
		if(i != 1){
			person[i-1]->next = i;
		}
		person[i]->prev = i-1;
		person[i]->next = -1;
	}
	for(i=1;i<=n;i++){
		scanf("%d %d",&person[i]->to,&person[i]->debt);
		person[person[i]->to]->fromCount++;
	}
	
	for(i=1;i<=n;i++){
		if(person[i]->visited == 0){
			totalMoney += visit(i);
		}
	}//printf("1\n");for(j=1;j<=n;j++){printf("\t%d : %d %d %d %d\n",j,person[j]->to,person[j]->debt,person[j]->fromCount,person[j]->balance);};
	while(start != -1){
		candidateDebt = -1;
		candidate = -1;
		i = start;
		do{
			if(person[i]->fromCount == 1){
				if(candidateDebt == -1 || person[i]->debt - person[i]->balance < candidateDebt){
					candidate = i;
					candidateDebt = person[i]->debt - person[i]->balance;
				}
			}
			i = person[i]->to;
		}while(i != start);
		person[candidate]->fromCount = 0;
		totalMoney += visit(candidate);
		//printf("2\n");for(j=1;j<=n;j++){printf("\t%d : %d %d %d %d\n",j,person[j]->to,person[j]->debt,person[j]->fromCount,person[j]->balance);};
	}
	printf("%d\n",totalMoney);
	return 0;
}
