#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

#define NUMROWS 1024


//a) Write a routine to print out a vector

void printArray(int numRows, float* array, char* fileName) {
  int i ;
  FILE *FP = fopen(fileName,"w") ;
  for(i=0; i < numRows; ++i) {
    fprintf(FP, "%f\n", array[i]) ;
  }
}

//b) Write a routine to print out a matrix

void printSquareMatrix(int numRows, float **matrix, char* fileName) {
  int i,j ;
  FILE *FP = fopen(fileName,"w") ;
  for(i=0; i < numRows; ++i) {
    for(j=0; j < numRows; ++j)
      fprintf(FP, "%f ", matrix[i][j]) ;
    fprintf(FP,"\n") ;
  }
}

//c) Write a routine to initialize an array with a value.

void initializeArray(int numRows, float* array, float value) {
  int i ;
  for(i = 0; i < numRows; ++i)
    array[i] = value ;
  
}

//d) Write a routine to initialize a matrix with a value.
void initializeSquareMatrix(int numRows, float **matrix, float value) {
  int i,j ;
  for(i=0; i < numRows; ++i)
    for(j =0; j < numRows; ++j)
      matrix[i][j] = value ;
}


//e) Write a routine to do square matrix vector multiplication y=A*x (in serial)

void squareMatVecSerial(int numRows, float **A, float* x , float *y) {
  int i,j ;
  for(i=0; i < numRows; ++i) {
    y[i] = 0 ;
    for(j=0; j < numRows; ++j) 
      y[i] += A[i][j]*x[j] ;
  }
}
  
//f) Write a routine to do square matrix multiplication C=A*B (in serial)
void squareMatMultiplySerial(int numRows, float **A, float **B, float **C) {
  int i,j,k ;
  for(i=0; i < numRows; ++i)
    for(j=0; j < numRows; ++j) {
      C[i][j] = 0 ;
      for(k=0; k < numRows; ++k)
	C[i][j] += A[i][k]*B[k][j] ;
    }
}

void alloc2DMatrix(int numRows, float*** buffer) {
  int i ;  
  float *data = (float *)malloc(numRows*numRows*sizeof(float)) ;
  (*buffer)= (float **)malloc(numRows*sizeof(float*));
  for(i=0; i < numRows; ++i)
    (*buffer)[i] = &(data[numRows*i]) ;
}

  

//Compute the matrix vector product result =  A*x in parallel 
//A is assumed to be a distributed matrix, x a distributed aray
//The last processor (numProcs-1) will have the final result
//the final result should be big enough the gather all the small chunks
void squareMatVecParallel2D(int numRows, int numProcs, int myRank, float **A, float* x, float *result) {
  int rootP = (int) sqrt((double)numProcs) ;
  float* tmpResult1 = malloc(numRows*sizeof(float)) ;
  float* tmpResult2 = malloc(numRows*sizeof(float)) ;
  MPI_Comm  rowComm, colComm ;
  MPI_Comm_split(MPI_COMM_WORLD, myRank/rootP, 0, &rowComm) ; 
  squareMatVecSerial(numRows, A, x, tmpResult1) ;
  
  char str[100] ;
  sprintf(str,"test-proc%d.txt",myRank) ;
  MPI_Reduce(tmpResult1, tmpResult2, numRows, MPI_FLOAT,MPI_SUM,rootP-1,rowComm) ;
  MPI_Comm_split(MPI_COMM_WORLD, myRank%rootP,0, &colComm) ;
  MPI_Gather(tmpResult2, numRows,MPI_FLOAT,result,numRows, MPI_FLOAT, rootP-1, colComm);
  free(tmpResult1) ;
  free(tmpResult2) ;
  
}

//set A = B
void copyMatrix(int numRows, float** A, float** B) {
  int i,j ;
  for(i = 0; i < numRows; ++i)
    for(j = 0; j < numRows; ++j)
      A[i][j] = B[i][j] ;
}

//set A = B
void addMatrix(int numRows, float** A, float** B) {
  int i,j ;
  for(i = 0; i < numRows; ++i)
    for(j = 0; j < numRows; ++j)
      A[i][j] += B[i][j] ;
}
//Compute local matrix multiplication
void squareMatMultiplyParallel2D(int numRows, int numProcs, int myRank, float **A, float **B , float **C) {
  
  int i ;
  
  int rootP = (int) sqrt((double)numProcs) ;
  MPI_Comm  rowComm, colComm ;
  MPI_Status status1, status2 ;
  float** tmpMatrix, **tmpResult ;

  alloc2DMatrix(numRows, &tmpMatrix) ;
  alloc2DMatrix(numRows, &tmpResult) ;
  
  MPI_Comm_split(MPI_COMM_WORLD, myRank/rootP, 0, &rowComm) ; 
  MPI_Comm_split(MPI_COMM_WORLD, myRank%rootP,0, &colComm) ;
  
  int rowIndex = myRank/rootP ;
  int colIndex = myRank%rootP ;
  int localRowRank, localColRank ;
  
  MPI_Comm_rank(rowComm, &localRowRank) ;
  MPI_Comm_rank(colComm, &localColRank) ;
  // printf("localRowRank = %d \n", localRowRank) ;
  // printf("localColRank = %d \n", localColRank) ;
  copyMatrix(numRows, tmpMatrix, A) ;
  if(rowIndex) {
    if(localRowRank < rootP/2) {
      MPI_Send(&tmpMatrix[0][0], numRows*numRows, MPI_FLOAT, (localRowRank-rowIndex+rootP)%rootP, rowIndex, rowComm) ;
      //printf("rowIndex = %d, myRank for A= %d, , sending to %d \n", rowIndex, localRowRank,  (localRowRank-rowIndex+rootP)%rootP) ;
      MPI_Recv(&A[0][0], numRows*numRows, MPI_FLOAT, (localRowRank+rowIndex)%rootP,rowIndex,rowComm,&status1) ;
      //printf("rowIndex = %d, myRank for A= %d, received from %d \n", rowIndex, localRowRank, (localRowRank+rowIndex)%rootP) ;
      
    }  else {
      MPI_Recv(&A[0][0], numRows*numRows, MPI_FLOAT, (localRowRank+rowIndex)%rootP,rowIndex, rowComm, &status1) ;
      //printf("rowIndex = %d, myRank for A= %d, received from %d \n", rowIndex, localRowRank, (localRowRank+rowIndex)%rootP) ;
      MPI_Send(&tmpMatrix[0][0], numRows*numRows, MPI_FLOAT, (localRowRank-rowIndex+rootP)%rootP, rowIndex, rowComm) ;
      //printf("rowIndex = %d, myRank for A= %d  sending to %d \n", rowIndex, localRowRank, (localRowRank-rowIndex+rootP)%rootP) ;
      
    }
  }
  copyMatrix(numRows, tmpMatrix, B) ;  
  if(colIndex) {
    if(localColRank < rootP/2) {
      MPI_Send(&tmpMatrix[0][0], numRows*numRows, MPI_FLOAT, (localColRank-colIndex+rootP)%rootP, colIndex, colComm) ;
      MPI_Recv(&B[0][0], numRows*numRows, MPI_FLOAT, (localColRank+colIndex)%rootP,colIndex,colComm,&status2) ;
    } else {
      MPI_Recv(&B[0][0], numRows*numRows, MPI_FLOAT, (localColRank+colIndex)%rootP,colIndex,colComm,&status2) ;
      MPI_Send(&tmpMatrix[0][0], numRows*numRows, MPI_FLOAT, (localColRank-colIndex+rootP)%rootP, colIndex, colComm) ;
    }
    
  }
  //printf("here \n") ;
  
  //each processor writes out its chunk of results into a file
  char str[80] ;
  for(i=0; i < rootP; ++i) {
    
    squareMatMultiplySerial(numRows, A, B, tmpResult) ;
    addMatrix(numRows,C,tmpResult) ;

    //sprintf(str,"A-proc%d-%d.txt",myRank,i) ;
    // printSquareMatrix(numRows,A,str) ; 
    
    //sprintf(str,"B-proc%d-%d.txt",myRank,i) ;
    // printSquareMatrix(numRows,B,str) ; 
    
    //sprintf(str,"C-proc%d-%d.txt",myRank,i) ;
    //printSquareMatrix(numRows,C,str) ; 
    
    copyMatrix(numRows, tmpMatrix, A) ;
    if(localRowRank < rootP/2) {
      MPI_Send(&tmpMatrix[0][0], numRows*numRows, MPI_FLOAT, (localRowRank-1+rootP)%rootP, rowIndex, rowComm) ;
      MPI_Recv(&A[0][0], numRows*numRows, MPI_FLOAT, (localRowRank+1)%rootP,rowIndex,rowComm,&status1) ;
    }  else {
      MPI_Recv(&A[0][0], numRows*numRows, MPI_FLOAT, (localRowRank+1)%rootP,rowIndex,rowComm,&status1) ;
      MPI_Send(&tmpMatrix[0][0], numRows*numRows, MPI_FLOAT, (localRowRank-1+rootP)%rootP, rowIndex, rowComm) ;
    }
    
    copyMatrix(numRows, tmpMatrix, B ) ;
    if(localColRank < rootP/2) {
      MPI_Send(&tmpMatrix[0][0], numRows*numRows, MPI_FLOAT, (localColRank-1+rootP)%rootP, colIndex, colComm) ;
      MPI_Recv(&B[0][0], numRows*numRows, MPI_FLOAT, (localColRank+1)%rootP,colIndex,colComm,&status2) ;
    } else {
      MPI_Recv(&B[0][0], numRows*numRows, MPI_FLOAT, (localColRank+1)%rootP,colIndex,colComm,&status2) ;
      MPI_Send(&tmpMatrix[0][0], numRows*numRows, MPI_FLOAT, (localColRank-1+rootP)%rootP, colIndex, colComm) ;
    }
  }
  
  
 free(tmpMatrix[0]) ;
 free(tmpMatrix) ;
 free(tmpResult[0]) ;
 free(tmpResult) ;
}


int main(int argc, char* argv[]) {
  
  int numProcs, myRank, rootP ;
  float **A, **B, **C ;
  float x[NUMROWS], y[NUMROWS] ;
  MPI_Status status ;
  MPI_Comm rowComm, colComm ;
  MPI_Init(&argc,&argv) ;
  MPI_Comm_size(MPI_COMM_WORLD, &numProcs) ;
  MPI_Comm_rank(MPI_COMM_WORLD, &myRank) ;
  
  rootP = (int) sqrt((double)numProcs) ;
  int chunkSize = NUMROWS/rootP ;
  
  alloc2DMatrix(chunkSize,&A) ;
  alloc2DMatrix(chunkSize,&B) ;
  alloc2DMatrix(chunkSize,&C) ;

  initializeSquareMatrix(chunkSize, A, 1) ;
  initializeArray(chunkSize,x,1) ;
  squareMatVecParallel2D(chunkSize, numProcs, myRank, A, x, y) ;
  
  if(myRank == numProcs-1)
    printArray(NUMROWS,y,"test.txt") ;
 
    
  initializeSquareMatrix(chunkSize, B, 1) ;
  initializeSquareMatrix(chunkSize, C, 0) ;
  
  double startTime, endTime, timeTaken, maxTime ;
  startTime = MPI_Wtime() ;
  squareMatMultiplyParallel2D(chunkSize, numProcs, myRank, A, B, C) ;
  endTime = MPI_Wtime() ;
  timeTaken = endTime - startTime ;
  
  MPI_Reduce(&timeTaken, &maxTime, 1, MPI_DOUBLE,MPI_MAX,0,MPI_COMM_WORLD) ;
  if(myRank ==0)
    printf("Time taken = %lf \n", maxTime) ;

  //each processor writes out its chunk of results into a file
  char str[100] ;
  sprintf(str,"C-proc%d.txt",myRank) ;
  printSquareMatrix(chunkSize,C,str) ; 
  
  
  
  free(A[0]) ;
  free(A) ;

  free(B[0]) ;
  free(B) ;

  
  free(C[0]) ;
  free(C) ;
 
  
  MPI_Finalize() ;
  
}
