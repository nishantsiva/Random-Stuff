#include<stdio.h>
#include<math.h>
#include<float.h>

int
main (int argc, char *argv[])
{
	long double a,b,c,disc,x1,x2,largest;
	scanf("%Le %Le %Le",&a,&b,&c);
	largest = (a > b)?a:b;
	largest = (largest > c)?largest:c;
	a = a/largest;
	b = b/largest;	
	c = c/largest;
	if(a ==0 && c == 0){
		printf("%Lf\n",(long double)0.0);
	}
	else if(a == 0){
		printf("%Lf\n",-(c/b));
	}
	else if(c == 0){
		printf("%Lf %Lf\n",(long double)0.0,-(b/a));
	}
	else{
		disc = b*b - 4*a*c;
		if(disc >= 0){
			x1 = -(b+sqrt(disc)) / (2*a);
			x2 = -(2*c) / (b+sqrt(disc));
			printf("%Lf %Lf\n",x1,x2);
		}
		else{
			x1 = -b / (2*a);
			x2 = sqrt(-disc) / (2*a);
			printf("%Lf+%Lfi %Lf-%Lfi\n",x1,x2,x1,x2);
		}
	}
	return 0;
}
