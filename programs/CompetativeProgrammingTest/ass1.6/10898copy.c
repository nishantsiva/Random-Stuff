#include<stdio.h>
#include<stdlib.h>

#define MAX_ORDER 999999

int cmbCost[15];
int cmbNos[15][6];
int Arr[MAX_ORDER + 1];

void calculateMin(int curr, int final, int nItems, int nCombos){
	int i,j,k;
	int tempCurr,tempMin,flag,tempCmb,pos;
	for(; curr <= final; curr++)
	{
		if(curr == 0) Arr[curr] = 0;
		else Arr[curr] = -1;
		for(i = 0; i < nCombos+nItems; i++){
			tempCurr = curr;
			tempCmb = 0;
			flag = 1;
			for(j = 0, pos = 1; j < nItems; j++, pos *= 10){
				if(((tempCurr % 10) - (cmbNos[i][j]))  < 0){
					flag = 0;
					break;
				}
				tempCurr /= 10;
				tempCmb += cmbNos[i][j] * pos;
			}
			if(flag == 0) continue;
			tempMin = Arr[curr - tempCmb] + cmbCost[i];
			if(Arr[curr] == -1 || tempMin < Arr[curr]){
				Arr[curr] = tempMin;
			}
		}
	}
}

int main(){
	int I,C,cases,orders,temp,pos;
	int i,j,iter;
	while(scanf("%d",&I) == 1) {
		iter = 0;
		for(i = 0; i < I; i++){
			for(j = 0; j < I; j++){
				cmbNos[iter][j] = 0;
			}
			scanf("%d",&cmbCost[iter]);
			cmbNos[iter++][i] = 1;
		}
		scanf("%d",&C);
		for(i = 0; i < C; i++){
			for(j = 0; j < I; j++){
				scanf("%d",&cmbNos[iter][j]);
			}
			scanf("%d",&cmbCost[iter]);
			iter++;
		}
		calculateMin(0,MAX_ORDER,I,C);
		scanf("%d",&cases);
		while(cases--){
			orders = 0;
			for(i = 0, pos = 1; i < I; i++, pos *= 10){
				scanf("%d",&temp);
				orders += temp * pos;
			}
			printf("%d\n",Arr[orders]);
		}
	}
	return 0;
}
