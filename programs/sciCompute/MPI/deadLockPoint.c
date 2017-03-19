#include <mpi.h>
#include <stdio.h>
#define N 1000
int main(int argc, char* argv[])
{
  
  int a[N], b[N], npes, myrank ;
  MPI_Status status ;
  MPI_Init(&argc,&argv) ;
  MPI_Comm_size(MPI_COMM_WORLD, &npes) ;
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank) ;

  if (myrank == 0) {
    MPI_Send(a, N, MPI_INT, 1, 10, MPI_COMM_WORLD);
    printf("Processor 0 sent to 1 \n") ;
    MPI_Recv(b, N, MPI_INT, 1, 20, MPI_COMM_WORLD, &status);
    printf("Processor 0 received from 1 \n") ;     
   
    
  }
  else if (myrank == 1) {
    MPI_Send(a, N, MPI_INT, 0, 20, MPI_COMM_WORLD) ;   
    printf("Processor 1 sent to 0 \n") ;
    MPI_Recv(b, N, MPI_INT, 0, 10, MPI_COMM_WORLD, &status) ;
    printf("Processor 1 received from 0 \n") ; 
  }
  
  
  MPI_Finalize() ;
  
  return 0 ;
}
