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
		long double soln,solnPos = 0,solnNeg = 0,temp;
		for(i = 0; i <= 19; i++){
			temp = (pow(value[iter],i)) / ((long double)fact(i));
			if(temp > 0){
				solnPos += temp;
			}
			else{
				solnNeg += temp;
			}
		}
		soln = solnPos + solnNeg;
		printf("%d\n",value[iter]);
		printf("\tCalculated e^%d  \t= %.20Lf\n",value[iter],soln);
		printf("\texp(%d)  \t\t= %.20lf\n",value[iter],exp(value[iter]));
	}
	return 0;
}
