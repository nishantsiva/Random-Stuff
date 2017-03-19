#include <stdio.h>
#include <math.h>

#define EPSILON 0.000001

int isEqual (double x, double y) {
	if (fabs(x-y) < EPSILON) {
		return 1;
	}
	return 0;
}

double slope (double x1, double y1, double x2, double y2) {
	
}

double findAngleBtwLines (double x1, double y1, 
							double x2, double y2, 
							double x3, double y3, 
							double x4, double y4) {
	return 0;
}

int main (int argc, char *argv[]) {
	int x1, y1, x2, y2, x3, y3, x4, y4;
	double x,y;
/*	scanf("%d %d", &x1, &y1);*/
/*	scanf("%d %d", &x2, &y2);*/
/*	scanf("%d %d", &x3, &y3);*/
/*	scanf("%d %d", &x4, &y4);*/
/*	printf("%f\n", findAngleBtwLines((double)x1, (double)y1, */
/*									(double)x2, (double)y2, */
/*									(double)x3, (double)y3, */
/*									(double)x4, (double)y4));*/
/*	*/
/*	return 0;*/
	x = 0.00000049;
	y = -0.0000005;
	printf("%d\n",isEqual(x,y));
}
