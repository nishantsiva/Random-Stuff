#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#define  ARRAYSIZE	16
#define  MASTER		0

float  data[ARRAYSIZE];

int main (int argc, char *argv[])
{
int   numprocs, rank, dest, offset, i, j, source, chunksize;
float mysum, sum;

MPI_Status status;

/***** Initializations *****/
MPI_Init(&argc, &argv);
MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);

chunksize = (ARRAYSIZE / numprocs);
/***** Master process only ******/

    if (rank == MASTER){

  /* Initialize the array */
  sum = 0;
  for(i=0; i<ARRAYSIZE; i++) {
    data[i] =  i +1;
    sum = sum + data[i];
    }
  printf("Initialized array sum = %f\n",sum);

  /* Send each process its portion of the array - master keeps 1st part */
  offset = chunksize;
  for (dest=1; dest<numprocs; dest++) {
    MPI_Send(&offset, 1, MPI_INT, dest, 2, MPI_COMM_WORLD);
    MPI_Send(&data[offset], chunksize, MPI_FLOAT, dest, 1, MPI_COMM_WORLD);
    printf("Sent %d elements to task %d offset= %d\n",chunksize,dest,offset);
    offset = offset + chunksize;
    }

  /* Master does its part of the work */
        offset = 0;
        mysum = 0;
        for(i=offset; i < offset + chunksize; i++) {
            mysum = mysum + data[i];
        }

  
  /* Get final sum and print sample results */  
 
  
  printf("*** Final sum= %f ***\n",sum);

  }  /* end of master section */



/***** Non-master tasks only *****/

if (rank > MASTER) {

  /* Receive my portion of array from the master task */
  source = MASTER;
  MPI_Recv(&offset, 1, MPI_INT, source, 2, MPI_COMM_WORLD, &status);
  MPI_Recv(&data[offset], chunksize, MPI_FLOAT, source, 1, MPI_COMM_WORLD, &status);

    mysum = 0;
    
    for(i=offset; i < offset + chunksize; i++) {
        mysum = mysum + data[i];
    }

  /* Send my results back to the master task */
  

  MPI_Reduce(&mysum, &sum, 1, MPI_FLOAT, MPI_SUM, MASTER, MPI_COMM_WORLD);

  } /* end of non-master */


MPI_Finalize();

}   /* end of main */




