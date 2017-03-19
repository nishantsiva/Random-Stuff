#include<stdio.h>
#include<stdlib.h>

int main(){
	int K,N,T,P;
	int **Arr;
	int i,j;
	scanf("%d",&K);
	while(K--){
		scanf("%d %d %d",&N,&T,&P);
		if(T - N*P < 0){
			printf("0\n");
			continue;
		}
		Arr = (int**)malloc(sizeof(int*)* N);
		for(i = 0; i < N; i++){
			Arr[i] = (int*)malloc(sizeof(int) * (T- N*P + 1));
			Arr[i][0] = 1;
		}
		for(i = 0; i <= T- N*P; i++){
			Arr[0][i] = 1;
		}
		for(i = 1; i < N; i++){
			for(j = 0; j <= T-N*P; j++){
				Arr[i][j] = Arr[i][j-1] + Arr[i-1][j];
			}
		}
		printf("%d\n",Arr[N-1][T-N*P]);
	}
}
