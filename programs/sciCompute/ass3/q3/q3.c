#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 0.0000000001

void copy (double *s, double *d, int r, int c) {
	int i;
	for (i = 0; i < r*c; i += 1) {
		d[i] = s[i];
	}
}

void printMatrix (double *M, int r, int c) {
	int i, j;
	for (i = 0; i < r; i += 1) {
		printf("\t");
		for (j = 0; j < c; j += 1) {
			printf("%lf\t", *(M + i*c + j));
		}
		printf("\n");
	}
}

int isMatEqual (double *A, double *B, int r, int c) {
	int i;
	for (i = 0; i < r*c; i += 1) {
		if (fabs(A[i] - B[i]) > EPSILON) {
			return 0;
		}
	}
	return 1;
}

void MatMult (double *A, double *B, double *C, int r1, int c1, int c2) {
	int i, j, k;
	for (i = 0; i < r1; i += 1) {
		for (j = 0; j < c2; j += 1) {
			*(C + i*c2 + j) = 0;
			for (k = 0; k < c1; k += 1) {
				*(C + i*c2 + j) += *(A + i*c1 + k) * *(B + k*c2 + j);
			}
		}
	}
}

int main (int argc, char *argv[]) {
	double A[][3] = {{ 0.8, 0.2, 0.1},
				     { 0.1, 0.7, 0.3},
				     { 0.1, 0.1, 0.6}};
	double xStart[][1] = {{1.0}, {0.0}, {0.0}};
	double ax[3][1];
	double APrev[3][3], nA[3][3], temp[3][3];
	double tempx[3][1];
	int i = 0;
	copy((double*)A, (double*)nA,3,3);
	do {
		copy((double*)nA, (double*)APrev,3,3);
		MatMult((double*)nA, (double*)A, (double*)temp, 3, 3, 3);
		copy((double*)temp, (double*)nA, 3, 3);
		if (++i == 3)
		{
			MatMult((double*)nA, (double*)xStart, (double*)ax, 3, 3, 1);
			printf("Probability distribution vector after 3 steps : \n");
			printMatrix((double*)ax,3,1);
		}
	} while (isMatEqual((double*)nA, (double*)APrev, 3, 3) == 0);
	printf("\nStationary matrix :\n");
	printMatrix((double*)nA,3,3);
	printf("\nLong term probability distribution vector :\n");
	MatMult((double*)nA, (double*)xStart, (double*)ax, 3, 3, 1);
	printMatrix((double*)ax,3,1);
	printf("\nEigen vector for stationary matrix\n");
	MatMult((double*)nA, (double*)ax, (double*)tempx, 3, 3, 1);
	printMatrix((double*)tempx,3,1);
	return 0;
}
