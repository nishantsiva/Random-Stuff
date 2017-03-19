#include<stdio.h>
#include<math.h>

long long
fact(long long n){
	if(n == 1 || n == 0){
		return 1;
	}
	return n*fact(n-1);
}

int
main (int argc, char *argv[])
{
	int value[] = {1,-1,5,-5,10,-10,15,-15,20,-20};
	int i,iter;
	for(iter = 0; iter < 10; iter++){
		long double soln = 0;
		for(i = 0; i <= 19; i++){
			soln += (pow(abs(value[iter]),i)) / ((long double)fact(i));
		}
		if(value[iter] < 0){
			soln = 1 / soln;
		}
		printf("%d\n",value[iter]);
		printf("\tCalculated e^%d  \t= %.20Lf\n",value[iter],soln);
		printf("\texp(%d)  \t\t= %.20lf\n",value[iter],exp(value[iter]));
	}
	return 0;
}
