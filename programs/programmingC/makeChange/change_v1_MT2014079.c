#include<stdio.h>

typedef struct{
	int value;
	int count;
}denoms;

void changeMaker(char *denomsStr, int amount, int no_of_denoms){
	char temp[10];
	denoms denArray[no_of_denoms];
	int i = 0,j = 0,k = 0,flag = 0;
	do{
		if(denomsStr[i] >= '0' && denomsStr[i] <= '9'){
			temp[j++] = denomsStr[i];
			temp[j] = '\0';
		}
		else{
			denArray[k].value = atoi(temp);
			denArray[k].count = amount/denArray[k].value;
			amount = amount % denArray[k].value;
			k++; j = 0;
			temp[j] = '\0';
		}
	}while(denomsStr[i++] != '\0');
	for(i = 0; i< no_of_denoms; i++){
		if(denArray[i].count != 0){
			if(flag)
				printf(",");
			printf("%d:%d",denArray[i].value,denArray[i].count);
			flag = 1;
		}
	}
	printf("\n");	
}

int getDenominations(char *denomArr){
	int i,count = 1;
	for(i = 0; denomArr[i] != '\0'; i++){
		if(denomArr[i] == ',')
			count++;
	}
	return count;
}

main()
{
	char denominations[25];
	int value,iCount,count,j;
	int input[50];
	scanf("%[^\n]s",denominations);
	for(iCount = 0; !feof(stdin); iCount++)
		scanf(" %d",&input[iCount]);
	iCount--;
	printf("%s\n",denominations);
	count = getDenominations(denominations);
	for(j=0; j < iCount; j++)
		changeMaker(denominations,input[j],count);
}
