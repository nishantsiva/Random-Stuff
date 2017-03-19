//C Language - Environment Management Routines Example
#include "mpi.h"
#include <stdio.h>
main(int argc, char *argv[])
{
    int myrank;
    int value = 123;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_Rank(MPI_COMM_WORLD, &myrank);
    if (myrank == 0)
        MPI_Send(&value, 1, MPI_INT, 1, MPI_ANY_TAG, MPI_COMM_WORLD);
    else if (myrank == 1)
        MPI_Recv(&value, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    MPI_Finalize();
}


