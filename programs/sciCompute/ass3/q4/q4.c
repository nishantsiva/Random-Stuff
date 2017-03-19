#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define EPSILON 0.000001

float findConvergence (float x, float x1, float x2, float x3) {
	float c1, c2;
	c1 = log(fabs(x3-x)/fabs(x2-x));
	c2 = log(fabs(x2-x)/fabs(x1-x));
	return c2 / c1;
}

int main (int argc, char *argv[]) {
	float xn = 1e6;
	float x = 1.0;
	float xk, xkn, xknn, r, c;
	int flag = 0, flag2 = 0, iter;
	printf("\nx^2 - 1 = 0,  x0 = 10^6\n\n");
	iter = 0;
	while (fabs(xn - x) > EPSILON) {
		printf("%f\n", xn);
		x = xn;
		xn = x - (x*x-1)/(2*x);
		iter++;
		if (flag == 0) {
			flag = 1;
			xk = x;
			xkn = xn;
			continue;
		}
		if (flag2 == 0) {
			flag2 = 1;
			xknn = xn;
		}
	}
	printf("%f\n", xn);
	printf("Value converges to : %f\n", xn);
	printf("Iterations : %d\n", iter);
	r = findConvergence(xn,xk,xkn,xknn);
	c = fabs(xn - xknn) / pow(fabs(xn - xkn),r);
	printf("r = %f\tc = %f\n\n", r, c);
	
	x = 1;
	xn = 10;
	flag = 0;
	flag2 = 0;
	iter = 0;
	printf("\n(x - 1)^4 = 0,  x0 = 10\n\n");
	while (fabs(xn - x) > EPSILON) {
		printf("%f\n", xn);
		x = xn;
		xn = x - (x-1)/4;
		iter++;
		if (flag == 0) {
			flag = 1;
			xk = x;
			xkn = xn;
			continue;
		}
		if (flag2 == 0) {
			flag2 = 1;
			xknn = xn;
		}
	}
	printf("%f\n", xn);
	printf("Value converges to : %f\n", xn);
	printf("Iterations : %d\n", iter);
	r = findConvergence(xn,xk,xkn,xknn);
	c = fabs(xn - xknn) / pow(fabs(xn - xkn),r);
	printf("r = %f\tc = %f\n\n", r, c);
	return 0;
}
