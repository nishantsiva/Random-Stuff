#include <stdio.h>
#include <stdlib.h>
#define NUM_ROWS 20000


void alloc2DMatrix(int numRows, float*** buffer) {
  int i ;  
  float *data = (float *)malloc(numRows*numRows*sizeof(float)) ;
  (*buffer)= (float **)malloc(numRows*sizeof(float*));
  for(i=0; i < numRows; ++i)
    (*buffer)[i] = &(data[numRows*i]) ;
}


int main() {
  float* column_sum = (float*)malloc(NUM_ROWS*sizeof(float)) ;
  float** b ;
  int n=NUM_ROWS ;
  int i,j ;
  alloc2DMatrix(n,&b) ;
  
  for (i = 0; i < NUM_ROWS; i++) {
    column_sum[i] = 0.0;
    for (j = 0; j < NUM_ROWS; j++) {
	column_sum[i] += b[j][i];
    }
    
  }
}
