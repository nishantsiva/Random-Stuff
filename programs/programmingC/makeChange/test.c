#include<stdio.h>
#include<stdlib.h>

#define MIN(a,b) (((a)<(b))?(a):(b))

int insertDenominations(int *denomArray, int value){
	int i = 0,temp;
	while(1){
		if(denomArray[i] == 0){
			denomArray[i++] = value; 
			return i;
		}
		if(denomArray[i]<value){
			do{
				temp = denomArray[i];
				denomArray[i++] = value;
				value = temp;
			}while(value);
			return i;
		}
		i++;
	}
}

int getDenominations(char *inputStr,int *denomArray){
	int i=0,j=0,value,count;
	char temp[10];
	if(inputStr[0] == '\0')
		return;
	do{
		if(inputStr[i] >= '0' && inputStr[i] <= '9'){
			temp[j++] = inputStr[i];
			temp[j] = '\0';
		}
		else if(inputStr[i] == ',' || inputStr[i] == '\0'){
			value = atoi(temp);
			count = insertDenominations(denomArray,value);
			j = 0;
			temp[j] = '\0';
		}
	}while(inputStr[i++] != '\0');
	return count;
}

int changeMaker(int *denoms, int *opt,int amount,int count){
	int i,j,curr,got,no_change = -1,temp[count];
	if(amount == 0){
		return 0;}
	for(i = 0;i<count;i++)
		temp[i] = 0;
	for(i = 0;i<count;i++){
		curr = denoms[i];
		got = amount/curr;
		temp[i] = got;
		got += changeMaker(denoms+i+1,temp+i+1,amount%curr,count-(i+1));
		if(got<no_change || no_change == -1){
			no_change = got;
			for(j = 0;j<count;j++)
				opt[j] = temp[j];
		}
		temp[i] = 0;
	}
	return no_change;
}

void printList(int *denoms,int *opt,int count){
	int i,flag = 0;
	for(i=0;i<count;i++){
		if(opt[i]!=0){
			if(flag)
				printf(",");
			printf("%d:%d",denoms[i],opt[i]);
			flag = 1;
		}
	}
	printf("\n");
}

main()
{
	char denominations[25];
	int shift,iCount,count,i,j;
	int input[50],denoms[50],output[50];
	scanf("%[^\n]s",denominations);
	for(iCount = 0; !feof(stdin); iCount++)
		scanf(" %d",&input[iCount]);
	iCount--;
	for(i=0;i<50;i++)
		denoms[i] = 0;
	count = getDenominations(denominations,denoms);
	printf("%s\n",denominations);
	for(j=0; j < iCount; j++){
		changeMaker(denoms,output,input[j],count);
		printList(denoms,output,count);
	}
}
