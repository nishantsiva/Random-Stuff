#include<stdio.h>
#include<stdlib.h>

struct Models {
	int cost;
	struct Models *next;
};

struct Garments {
	int count;
	struct Models *models;
};

struct Garments *garments;

struct Models* createModel(int price){
	struct Models *ptr;
	ptr = (struct Models*)malloc(sizeof(struct Models));
	ptr->cost = price;
	ptr->next = NULL;
	return ptr;
}

int tryGarments(int M, int C,int maxAmt,int noGarments,int **Arr){
	int retVal = -1,temp;
	struct Models *ptr;
	if(M > maxAmt)
		return -1;
	if(C == noGarments)
		return 0;
	if(Arr[C][M] == 1)
		return -1;
	Arr[C][M] = 1;
	for(ptr = garments[C].models; ptr != NULL; ptr = ptr->next){
		temp = tryGarments(M + ptr->cost, C + 1, maxAmt, noGarments,Arr);
		if(temp != -1){
			if(temp + ptr->cost > retVal){
				retVal = temp + ptr->cost;
			}
		}
	}
	return retVal;
}

int main(){
    int T,M,C,K,price,retVal;
    int i,j,t;
    int **checkArr;
	struct Models *ptr,*ptr1;
    scanf("%d",&T);
    for(t = 1; t <= T; t++){
        scanf("%d %d",&M,&C);
        garments = (struct Garments*)malloc(sizeof(struct Garments) * C);
        checkArr = (int**)malloc(sizeof(int*) * C);
        for(i = 0; i < C; i++){
        	checkArr[i] = (int*)calloc(sizeof(int),(M+1));
        	scanf("%d",&K);
        	garments[i].count = K;
        	for(j = 0; j < K; j++){
        		scanf("%d",&price);
        		if(j == 0){
        			garments[i].models = createModel(price);
        			ptr = garments[i].models;
        		}
        		else{
        			ptr->next = createModel(price);
        			ptr = ptr->next;
        		}
        	}
        }
		retVal = tryGarments(0,0,M,C,checkArr);
		if(retVal == -1){
			printf("no solution\n");
		}
		else{
			printf("%d\n",retVal);
		}
		for(i = 0; i < C; i++){
			free(checkArr[i]);
			ptr = garments[i].models;
			while(ptr != NULL){
				ptr1 = ptr;
				ptr = ptr->next;
				free(ptr1);
			}
		}
		free(garments);
		free(checkArr);
    }
}
