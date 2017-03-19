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
	float xn = 10;
	float x = 2.0;
	float xk, xkn, xknn;
	int flag = 0, flag2 = 0;
	printf("Solution by fixed point iteration method:\n");
	while (fabs(xn - x) > EPSILON) {
		printf("%f\n", xn);
		x = xn;
		xn = 1+0.5*sin(x);
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
	printf("Convergence rate = %f\n\n", findConvergence(xn,xk,xkn,xknn));
	
	x = 1;
	xn = 10;
	flag = 0;
	flag2 = 0;
	printf("Solution by newton's method:\n");
	while (fabs(xn - x) > EPSILON) {
		printf("%f\n", xn);
		x = xn;
		xn = x - (x-0.5*sin(x)-1)/(1-0.5*cos(x));
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
	printf("Convergence rate = %f\n\n", findConvergence(xn,xk,xkn,xknn));
	
	return 0;
}
