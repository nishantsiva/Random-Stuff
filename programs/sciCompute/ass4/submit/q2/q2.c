#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 0.0000001

double fun_a(double x) {
	return sqrt(x*x*x);
}

double fun_b(double x) {
	return 1/(double)(1 + 10*x*x);
}

double fun_c(double x) {
	return (exp(-9*x*x) + exp(-1024*(x - 1/4.0)*(x - 1/4.0)))/sqrt(M_PI);
}

double fun_d(double x) {
	return 50 / (M_PI*(2500*x*x + 1));
}

double fun_e(double x) {
	return 1/sqrt(fabs(x));
}

double fun_f(double x) {
	return 25*exp(-25*x);
}

double fun_g(double x) {
	if(x==0) x = EPSILON;
	return log(x);
}

double simpsons(int a, int b, int n, double (*fun)(double)) {
	double x = (b - a) / (double)n;
	double ans = 0;
	int i;
	ans += (*fun)((double)a);
	for (i = 1; i < n; ++i)
	{
		ans += (*fun)((double)a + i*x)*((i%2 == 0) ? 2 : 4);
	}
	ans += (*fun)((double)b);
	return x / (double)3 * ans;
}

int main(int argc, char const *argv[])
{
	int iter = 100000;
	printf("a) %f\n", simpsons(0, 	1, 	iter, &fun_a));
	printf("b) %f\n", simpsons(0, 	1, 	iter, &fun_b));
	printf("c) %f\n", simpsons(0, 	1, 	iter, &fun_c));
	printf("d) %f\n", simpsons(0, 	10, iter, &fun_d));
	printf("e) %f\n", simpsons(-9, 	100,iter, &fun_e));
	printf("f) %f\n", simpsons(0, 	10, iter, &fun_f));
	printf("g) %f\n", simpsons(0, 	1, 	iter, &fun_g));
	return 0;
}