#include<stdio.h>
#include<stdlib.h>

#define MAX_ORDER 999999

int cmbCost[15];
int cmbNos[15];
int Arr[MAX_ORDER + 1];

void calculateMin(int curr, int final, int nItems, int nCombos){
	int i,j;
	int tempCurr,tempMin,flag,tempCmb;
	for(; curr <= final; curr++)
	{
		if(curr == 0) Arr[curr] = 0;
		else Arr[curr] = -1;
		for(i = 0; i < nCombos+nItems; i++){
			tempCurr = curr;
			tempCmb = cmbNos[i];
			flag = 1;
			for(j = 0; j < nItems; j++){
				if(((tempCurr % 10) - (tempCmb % 10))  < 0){
					flag = 0;
					break;
				}
				tempCurr /= 10;
				tempCmb /=10;
			}
			if(flag == 0) continue;
			tempMin = Arr[curr - cmbNos[i]] + cmbCost[i];
			if(Arr[curr] == -1 || tempMin < Arr[curr]){
				Arr[curr] = tempMin;
			}
		}
	}
}

int main(){
	int I,C,cases,orders,temp,pos,start;
	int i,j,iter;
	while(scanf("%d",&I) == 1) {
		iter = 0;
		for(i = 0, pos = 1; i < I; i++, pos *= 10){
			scanf("%d",&cmbCost[iter]);
			cmbNos[iter++] = pos;
		}
		scanf("%d",&C);
		for(i = 0; i < C; i++){
			cmbNos[iter] = 0;
			for(j = 0, pos = 1; j < I; j++, pos *= 10){
				scanf("%d",&temp);
				cmbNos[iter] += temp * pos;
			}
			scanf("%d",&cmbCost[iter]);
			iter++;
		}
		start = 0;
		scanf("%d",&cases);
		while(cases--){
			orders = 0;
			for(i = 0, pos = 1; i < I; i++, pos *= 10){
				scanf("%d",&temp);
				orders += temp * pos;
			}
			calculateMin(start,orders,I,C);
			printf("%d\n",Arr[orders]);
		}
	}
	return 0;
}
