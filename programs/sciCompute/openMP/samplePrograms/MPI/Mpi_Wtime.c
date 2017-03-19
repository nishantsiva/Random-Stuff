#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include<math.h>
int main(int argc,char *argv[])
{
        int rank, p;
        long start,end;
        long limit =0;
        long localsum=0,globalsum =0;
        long share = 0;
        int i =0;
        double start_time = 0;
        MPI_Status status;
        MPI_Init(&argc,&argv);
        MPI_Comm_size( MPI_COMM_WORLD,&p);
        MPI_Comm_rank(MPI_COMM_WORLD,&rank);
        start_time = MPI_Wtime();
        limit = 1000000000;
        start = floor(rank*limit/p);
        end  =  floor((rank+1)*limit/p)-1;
        share = end-start+1;
        int *local_numbers = (int *)malloc(share*sizeof(int));
        for(i=0;i<share;i++)
                local_numbers[i] =1 ;
        for(i=0;i<share;i++)
                localsum += local_numbers[i];
        MPI_Barrier(MPI_COMM_WORLD);
        MPI_Reduce(&localsum,&globalsum,1,MPI_LONG,MPI_SUM,0,MPI_COMM_WORLD);
        free(local_numbers);
        if(rank==0){
                printf("Sum is %ld\n", globalsum);
                double end_time = MPI_Wtime();
                double diff = end_time - start_time;
                printf("Total Execution Time = %f\n", diff);
        }
        MPI_Finalize();
        return 0;
}
