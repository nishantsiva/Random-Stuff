#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define RANDOM_INPUT 1

void
interchangeRow(float **Arr, int size, int row1, int row2){
	int i;
	float temp;
	for(i = 0; i < size + 1; i++){
		temp = Arr[row1][i];
		Arr[row1][i] = Arr[row2][i];
		Arr[row2][i] = temp;
	}
}

void
interchangeCol(float **Arr, int size, int col1, int col2){
	int i;
	float temp;
	for(i = 0; i < size; i++){
		temp = Arr[i][col1];
		Arr[i][col1] = Arr[i][col2];
		Arr[i][col2] = temp;
	}
}

void main()
{
	float **mat,*X,temp,temp1,x,y,z;
	int i,n,j,pvt,newRow,newCol,tempPos;
	int *pos;
	float feed = 100.0;
	srand((unsigned int)time(NULL));
	if(RANDOM_INPUT)
		n = rand() % 99 + 1;
	else
		scanf("%d",&n);
	mat = (float**)malloc(sizeof(float*)*n);
	X = (float*)malloc(sizeof(float)*n);
	pos = (int*)malloc(sizeof(int)*n);
	for(i=0; i<n; i++)
	{
		mat[i] = (float*)malloc(sizeof(float)*(n+1));
		pos[i] = i;
		for(j=0; j<n; j++)
		{
			if(RANDOM_INPUT)
				mat[i][j] = ((float)rand()/(float)(RAND_MAX)) * feed;
			else
				scanf("%f",&mat[i][j]);
		}
	}
	for(i=0;i<n;i++){
		if(RANDOM_INPUT)
			mat[i][n] = ((float)rand()/(float)(RAND_MAX)) * feed;
		else
			scanf("%f",&mat[i][n]);
	}
	printf("\n Your Matrix \n\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n+1;j++)
		{
			printf(" %g ",mat[i][j]);
		}
		printf("\n\n");
	}
	for(pvt = 0; pvt < n; pvt++){
		newRow = newCol = pvt;
		temp = 0.0;
		for(i= pvt; i < n; i++){
			for(j = pvt; j < n; j++){
				if(fabs(mat[i][j]) > temp){
					newRow = i;
					newCol = j;
					temp = fabs(mat[i][j]);
				}
			}
		}
		if(temp == 0) continue;
		interchangeCol(mat,n,pvt,newCol);
		tempPos = pos[pvt];
		pos[pvt] = pos[newCol];
		pos[newCol] = tempPos;
		interchangeRow(mat,n,pvt,newRow);
		for(i = pvt+1; i < n; i++){
			temp = mat[i][pvt] / mat[pvt][pvt];
			for(j = pvt; j < n+1; j++){
				mat[i][j] = mat[i][j] - mat[pvt][j]*temp;
			}
		}
	}
	
	printf("\nAfter Pivoting \n\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n+1;j++)
		{
			printf(" %.3f ",mat[i][j]);
		}
		printf("\n\n");
	}
	for(pvt = n-1; pvt >=0; pvt--){
		X[pvt] = mat[pvt][n];
		for(j = n-1; j > pvt; j--){
			X[pvt] -= mat[pvt][j] * X[j];
		}
		X[pvt] /= mat[pvt][pvt];
	}
	for(i = 0; i < n; i++){
		printf("\n\nx%d = %.6f",pos[i],X[i]);
	}
	printf("\n");
}
