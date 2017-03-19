#include<stdio.h>
#include<stdlib.h>

/*
 * Reccursively finds balance using all combinations.
 * Doesn't proceed through a path if it finds current balance not possible
 */

int findMaxBal(int *A,int index,int maxIndex,int curr,int limit){
	int max = -1;
	int temp;
	if(index == maxIndex){
		return curr;
	}
	if(curr + A[index] <= limit){
		max = findMaxBal(A,index+1,maxIndex,curr+A[index],limit);
	}
	if(curr-A[index] >= 0){
		temp = findMaxBal(A,index+1,maxIndex,curr-A[index],limit);
		if(temp > max){
			max = temp;
		}
	}
	return max;
}

int main (int argc, char *argv[]) {
	int T,N,M,q;
	int i,j;
	int arr[50];
	scanf("%d",&T);
	for(i=0;i<T;i++){
		scanf("%d %d %d",&N,&q,&M);
		for(j=0;j<N;j++){
			scanf("%d",&arr[j]);
		}
		printf("%d\n",findMaxBal(arr,0,N,q,M));
	}
	return 0;
}
