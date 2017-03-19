#include<stdio.h>
#include<stdlib.h>

int main(){
	int T,N,maxSum,maxi,maxj,curr,temp,tempj;
	int i,j;
	scanf("%d",&T);
	for(i=0;i<T;i++){
		scanf("%d",&N);
		maxSum = 0;
		maxi = maxj = -1;
		temp = 0;
		tempj = 0;
		for(j=1;j<N;j++){
			scanf("%d",&curr);
			temp += curr;
			if(temp < 0){
				tempj = j;
				temp = 0;
				continue;
			}
			if(temp > maxSum){
				maxSum = temp;
				maxj = tempj+1;
				maxi = j+1;
				continue;
			}
			if(temp == maxSum){
				if(maxi-maxj < j-tempj){
					maxj = tempj+1;
					maxi = j+1;
				}
						 
			}
		}
		if(maxSum > 0){
			printf("The nicest part of route %d is between stops %d and %d\n",i+1,maxj,maxi);
		}
		else{
			printf("Route %d has no nice parts\n",i+1);
		}
	}
}		
