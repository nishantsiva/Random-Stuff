#include<stdio.h>
#include<math.h>

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

int evaluateExprUtil(char *expr,char variable,int value,int *len);

int getOpernd(char *exprArr,int *len,char variable,int value){
	int i = 0,sign = 1,retVal;
	if(exprArr[i] == '-' || exprArr[i] == '+'){
		if(exprArr[i] == '-')
			sign = -1;
		i++;
	}
	if(exprArr[i] == '('){
		retVal = evaluateExprUtil(exprArr+i+1,variable,value,len);
		*len = *len + i + 2;
		return retVal * sign; 
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
		
int evaluateExprUtil(char *expr,char variable,int value,int *len)
{
	int i = 0,shift;
	int result;
	result = getOpernd(expr+i,&shift,variable,value);
	i += shift;
	while(expr[i]!='\0' && expr[i]!=')')
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
	*len = i;
	return result;
}

int evaluateExpr(char *expr,int value)
{
	char variable;
	int length;
	variable = expr[2];
	return evaluateExprUtil(expr+5,variable,value,&length);
}

char* toPostExpr(char *expr){
	
}

main()
{
	char expr[25],*post_exp;
	int value,i = 0,j;
	int input[10];
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
	printf("\n%s\n",expr);
	removeBlanks(expr);
	post_exp = toPostExpr(expr+5);
	for(j=0;j<i;j++){
		printf("P(%d)=%d\n",input[j],evaluateExpr(expr,input[j]));
	}
}	
