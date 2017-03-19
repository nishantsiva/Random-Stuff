#include<stdio.h>
#include<mpi.h>

int main(int argc , char **argv)
{
        int size, rank,i;
        int sendbuffer[10];
        int recvbuffer[10];
        MPI_Init(&argc,&argv);
        MPI_Comm_size(MPI_COMM_WORLD,&size);
        MPI_Comm_rank(MPI_COMM_WORLD,&rank);
        for(i=0;i<=10;i++){
                sendbuffer[i] = rank+i;
        }

        MPI_Reduce(&sendbuffer,recvbuffer,10,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
        if(rank==0){
                for(i=0;i<10;i++)
                printf("recvbuffer[%d] =%d\n",i,recvbuffer[i]);
        }
        MPI_Finalize();
}

