#include<stdio.h>
#include<stdlib.h>

int main (int argc, char *argv[]) {
	int N,i,sum,moves,give,final;
	int arr[100];
	scanf("%d",&N);
	sum = 0;
	for(i=0;i<N;i++){
		scanf("%d",&arr[i]);
		sum += arr[i];
	}
	moves = 0;
	give = 0;
	final = sum / N;
	for(i=0;i<N;i++){
		give += arr[i] - final;
		moves += abs(give);
	}
	printf("%d\n",moves);
	return 0;
}
