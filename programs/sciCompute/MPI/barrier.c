#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, nprocs;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    printf("Part A.  I am task %d of %d\n", rank, nprocs);
    
    MPI_Barrier(MPI_COMM_WORLD);
    
    printf("Part B.  I am task %d\n", rank);

    MPI_Finalize();
    return 0;
}
 

