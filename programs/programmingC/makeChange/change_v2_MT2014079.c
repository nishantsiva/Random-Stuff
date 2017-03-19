#include<stdio.h>
#include<stdlib.h>

#define MIN(a,b) (((a)<(b))?(a):(b))

typedef struct _denoms{
	int value;
	int count;
	struct _denoms *next;
}denoms;

denoms* createNode(int value, int count){
	denoms *ptr = (denoms*)malloc(sizeof(denoms));
	ptr->value = value;
	ptr->count = count;
	ptr->next = NULL;
	return ptr;
}

void insertDenominations(denoms *ptr, int value, int count){
	denoms *temp;
	if(ptr->value == 0){
		ptr->value = value;
		ptr->count = count;
		return;
	}
	while(ptr->next != NULL){
		if(ptr->next->value > value)
			ptr = ptr->next;
		else{
			temp = createNode(value,count);
			temp->next = ptr->next;
			ptr->next = temp;
			return;
		}
	}
	ptr->next = createNode(value,count);
}

denoms* getDenominations(char *inputStr){
	int i=0,j=0,count,value;
	char temp[10];
	denoms *denomStart;
	if(inputStr[0] == '\0')
		return;
	denomStart = createNode(0,0);
	do{
		if(inputStr[i] >= '0' && inputStr[i] <= '9'){
			temp[j++] = inputStr[i];
			temp[j] = '\0';
		}
		else if(inputStr[i] == ':'){
			value = atoi(temp);
			j = 0;
			temp[j] = '\0';
		}
		else if(inputStr[i] == ',' || inputStr[i] == '\0'){
			count = atoi(temp);
			insertDenominations(denomStart,value,count);
			j = 0;
			temp[j] = '\0';
		}
	}while(inputStr[i++] != '\0');
	return denomStart;
}

int changeMaker(denoms *ptr, int amount, char *optStr){
	int need,got,shift = 0,flag = 0;
	while(ptr != NULL && amount!=0){
		need = amount / ptr->value;
		got = MIN(need,ptr->count);
		ptr->count -= got;
		amount -= ptr->value*got;
		if(got != 0){
			if(flag)
				shift += sprintf(optStr+shift,",");
			shift += sprintf(optStr+shift,"%d:%d",ptr->value,got);
			flag = 1;
		}
		ptr = ptr->next;
	}
	return shift + sprintf(optStr+shift,"\n");	
}

void printDenoms(denoms *ptr){
	while(ptr){
		printf("%d:%d",ptr->value,ptr->count);
		if(ptr->next)
			printf(",");
		ptr = ptr->next;
	}
	printf("\n");
}

main()
{
	char denominations[25],output[500];
	int shift,iCount,j;
	int input[50];
	denoms *denomList;
	scanf("%[^\n]s",denominations);
	for(iCount = 0; !feof(stdin); iCount++)
		scanf(" %d",&input[iCount]);
	iCount--;
	denomList = getDenominations(denominations);
	output[0] = '\0';
	shift = 0;
	for(j=0; j < iCount; j++)
		shift += changeMaker(denomList,input[j],output+shift);
	printDenoms(denomList);
	printf("%s",output);
}
