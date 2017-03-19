#include <stdio.h>
#include <math.h>

int check(double x, double y, double a, double b) {
	double theta;
	if (x > a && y > b) {
		return 1;
	}
	if (x <= a && y <= b) {
		return 0;
	}
	theta = asin(y/sqrt(a*a + b*b)) - atan2(b,a);
	if (theta < 0) {
		return 0;
	}
	if ((2*(b*sin(theta)) + sqrt(a*a + b*b - y*y)) <= x) {
		return 1;
	}
	return 0;
}

int main (int argc, char *argv[]) {
	int cases;
	double x, y, a, b, temp;
	scanf("%d",&cases);
	while (cases--) {
		scanf("%lf %lf %lf %lf", &x, &y, &a, &b);
		if (x < y) {
			temp = x; x = y; y = temp;
		}
		if (a < b) {
			temp = a; a = b; b = temp;
		}
		if (check(x, y, a, b)) {
			printf("Escape is possible.\n");
		}
		else {
			printf("Box cannot be dropped.\n");
		}
	}
	return 0;
}
