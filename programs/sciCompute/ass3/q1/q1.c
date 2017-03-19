#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 0.0000001

void copy (double *s, double *d) {
	int i;
	for (i = 0; i < 3; i += 1) {
		d[i] = s[i];
	}
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

double findNorm (double *X) {
	int i;
	double temp = 0.0;
	for (i = 0; i < 3; i += 1) {
		if (temp*temp < X[i]*X[i]) {
			temp = X[i];
		}
	}
	return temp;
}

int isEqual (double X1, double X2) {
	double dif = X1 - X2;
	if (dif >= 0 && dif < EPSILON) {
		return 1;
	}
	else if (dif < 0 && -dif < EPSILON) {
		return 1;
	}
	return 0;
}

void divideNorm (double *X, double n) {
	int i;
	for (i = 0; i < 3; i += 1) {
		X[i] /= n;
	}
}

void transpose (double A[][3], double At[][3]) {
	int i, j;
	for (i = 0; i < 3; i += 1) {
		for (j = 0; j < 3; j += 1) {
			At[i][j] = A[j][i];
		}
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

void findEigen (double A[][3], double *nX, double *l) {
	double nNorm = 1, norm;
	double X[3], temp[3];
	double num, denom;
	int i, j;
	do {
		norm = nNorm;
		MatMult((double*)A, (double*)nX, (double*)temp, 3, 3, 1);
		copy(temp, nX);
		nNorm = findNorm(nX);
		divideNorm(nX, nNorm);
	} while (isEqual(nNorm, norm) == 0);
	num = denom = 0.0;
	for (i = 0; i < 3; i += 1) {
		X[i] = 0;
		for (j = 0; j < 3; j += 1) {
			X[i] += nX[j]*A[i][j]; 
		}
		num += X[i]*nX[i];
		denom += nX[i]*nX[i];
	}
	*l =  num / denom;
}

void deflate (double A[][3], double *X, double l) {
	int i, j;
	double At[3][3], U[] = {0.0, 0.0, 0.0}, temp[3];
	for (i = 0; i < 3; i += 1) {
		if (X[i] == 1) {
			U[i] = 1.0;
		}
	}
	transpose(A,At);
	MatMult((double*)At, (double*)U, (double*)temp, 3, 3, 1);
	copy(temp, U);
	for (i = 0; i < 3; i += 1) {
		for (j = 0; j < 3; j += 1) {
			A[i][j] -= X[i]*U[j];
		}
	}
}

int main (int argc, char *argv[]) {
	double A[][3] = {{ 2, 3, 2},
				     {10, 3, 4},
				     { 3, 6, 1}};
	double start[] = {0.0, 0.0, 1.0}, X[3];
	double lambda;
	copy(start, X);
	findEigen(A, X, &lambda);
	printf("\nDominent eigen value : %f\n", lambda);
	printf("Eigen Vector :\n"); printMatrix((double*)X,3,1);
	deflate(A, X, lambda);copy(start, X);
	findEigen(A, X, &lambda);
	printf("\nNext Dominent eigen value : %f\n", lambda);
	return 0;
}
