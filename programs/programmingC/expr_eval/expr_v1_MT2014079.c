#include<stdio.h>
#include<math.h>

int getNum(char *exprArr,int *len)
{
	int i = 0,num = 0;
	while(exprArr[i] <= '9' && exprArr[i] >= '0') 
	{
		num = num*10 + (exprArr[i] - '0');
		i++;
	}
	*len = i;
	return num;
}

int getOpernd(char *exprArr,int *len,char variable,int value){
	int i = 0,sign = 1,retVal;
	if(exprArr[i] == '-' || exprArr[i] == '+'){
		if(exprArr[i] == '-')
			sign = -1;
		i++;
	}
	if(exprArr[i] <= '9' && exprArr[i] >= '0'){
		retVal = getNum(exprArr + i,len);
		*len = *len + i;
		return retVal * sign;
	}	
	else if(exprArr[i]==variable){
		*len = 1 + i;
		return value * sign;
	}
}

void removeBlanks(char *expr){
	int i = 0,j;
	while(expr[i] != '\0'){
		if(expr[i] == ' '){
			j = i+1;
			while(expr[j-1] != '\0'){
				expr[j-1] = expr[j];
				j++;
			}
			continue;
		}
		i++;
	}
}
			
int evaluateExprUtil(char *expr,char variable,int value)
{
	int i = 0,shift;
	int result;
	result = getOpernd(expr+i,&shift,variable,value);
	i += shift;
	while(expr[i]!='\0')
	{
		if(expr[i]=='=' || expr[i]==' '){
			i++;
			continue;
		}
		switch(expr[i]){
			case '+':	result += getOpernd(expr+i+1,&shift,variable,value);
						i += shift + 1;
						break;
			case '-':	result -= getOpernd(expr+i+1,&shift,variable,value);
						i += shift + 1;
						break;
			case '*':	result *= getOpernd(expr+i+1,&shift,variable,value);
						i += shift + 1;
						break;
			case '/':	result /= getOpernd(expr+i+1,&shift,variable,value);
						i += shift + 1;
						break;
			case '^':	result = pow(result,getOpernd(expr+i+1,&shift,variable,value));
						i += shift + 1;
						break;
		}
	}
	return result;
}

int evaluateExpr(char *expr,int value)
{
	char variable;
	variable = expr[2];
	return evaluateExprUtil(expr+5,variable,value);
}

main()
{
	char expr[25];
	int value,i = 0,j;
	int input[10];
	//while((expr[i] = getchar()) != '\n') i++;
	//expr[i] = '\0';
	scanf("%[^\n]s",expr);
	i = 0;
	while(1)
	{
		scanf(" %d",&input[i]);
		if(input[i] == 1000){
			break;
		}
		i++;
	}		
	printf("%s\n",expr);
	removeBlanks(expr);
	for(j=0;j<i;j++){
		printf("P(%d)=%d\n",input[j],evaluateExpr(expr,input[j]));
	}
}	
