#include <mpi.h>
#include <stdio.h>
#define N 10000

int main(int argc, char* argv[])
{
  
  int a[N], b[N], npes, myrank ;
  MPI_Status status ;
  MPI_Init(&argc,&argv) ;
  MPI_Comm_size(MPI_COMM_WORLD, &npes) ;
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank) ;
  MPI_Send(a, N, MPI_INT, (myrank+1)%npes, 1, MPI_COMM_WORLD) ;
  printf("Sent from %d to %d \n", myrank, (myrank+1)%npes) ;
  MPI_Recv(b, N, MPI_INT, (myrank-1+npes)%npes, 1, MPI_COMM_WORLD, &status) ;
  printf("Receive from %d to %d \n", (myrank-1+npes)%npes, myrank) ;
  MPI_Finalize() ;
  
  return 0 ;
}
