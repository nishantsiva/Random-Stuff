#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#define  MASTER		0

int main (int argc, char *argv[])
{
int  numtasks, taskid, len;

int  partner, message;
MPI_Status status;

MPI_Init(&argc, &argv);
MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
MPI_Comm_rank(MPI_COMM_WORLD,&taskid);


if (taskid == MASTER)
   

/* determine partner and then send/receive with partner */
if (taskid < numtasks/2) {
  partner = numtasks/2 + taskid;
  MPI_Send(&taskid, 1, MPI_INT, partner, 1, MPI_COMM_WORLD);
  MPI_Recv(&message, 1, MPI_INT, partner, 1, MPI_COMM_WORLD, &status);
  }
else if (taskid >= numtasks/2) {
  partner = taskid - numtasks/2;
  MPI_Recv(&message, 1, MPI_INT, partner, 1, MPI_COMM_WORLD, &status);
  MPI_Send(&taskid, 1, MPI_INT, partner, 1, MPI_COMM_WORLD);
  }

/* print partner info and exit*/
printf("Task %d is partner with %d\n",taskid,message);

MPI_Finalize();

}

