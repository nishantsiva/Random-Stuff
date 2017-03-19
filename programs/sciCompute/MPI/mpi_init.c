//C Language - Environment Management Routines Example

   #include "mpi.h"
   #include <stdio.h>

   int main(int argc,char* argv[])
   {
   int  numtasks, rank, len, rc; 
   len = 5 ;
   rc = MPI_Init(&argc,&argv);
   if (rc != MPI_SUCCESS) {
     printf ("Error starting MPI program. Terminating.\n");
     MPI_Abort(MPI_COMM_WORLD, rc);
     }

   MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
   MPI_Comm_rank(MPI_COMM_WORLD,&rank);
   printf ("Number of tasks= %d My rank= %d, len = %d \n", numtasks,rank, len);

   /*******  do some work *******/

   MPI_Finalize();

   return 0;
   }

