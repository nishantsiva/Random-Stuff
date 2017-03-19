// MPI_Scatter and MPI_Gather Example in C

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define root 0

int main(int argc,char *argv[])
{
        int rank, p;
        int *recvbuffer,*sendbuffer,*back_ray;
        int count;
        int i,k,j,localsum;
        int datasize;
        MPI_Init(&argc,&argv);
        MPI_Comm_size( MPI_COMM_WORLD,&p);
        MPI_Comm_rank(MPI_COMM_WORLD,&rank);
/*each processor will get count elements(in recvbuffer) from the root(through MPI_Scatter)*/
        count=4;
        recvbuffer=(int*)malloc(count*sizeof(int));
/*Root Process initializes sendbuffer*/
        if(rank== root){
                datasize=count*p;
                sendbuffer=(int*)malloc(datasize*sizeof(int));
                back_ray=(int*)malloc(p*sizeof(int));
                for(i=0;i<datasize;i++){
                        sendbuffer[i]=i;
                        printf("Sendbuffer[%d] = %d\n",i,sendbuffer[i]);
                }
        }
/*Distribute Data through MPI_Scatter*/
        MPI_Scatter(sendbuffer,count,MPI_INT,recvbuffer,count,MPI_INT,root,MPI_COMM_WORLD);
/*Each process calculates a local sum*/
        localsum=0;
        for(i=0;i<count;i++){
                localsum=localsum+recvbuffer[i];
        }
        printf("Rank= %d total= %d\n ",rank,localsum);
/*Send the local sums back to the root through MPI_Gather*/
        MPI_Gather(&localsum,1,MPI_INT,back_ray,1,MPI_INT,root,MPI_COMM_WORLD);
/*Root Process Calculates the Global Sum*/
        if(rank == root){
                int globalsum=0;
                for(i=0;i<p;i++){
                        printf("b_ray[%d]=%d\t",i,back_ray[i]);
                        globalsum+=back_ray[i];
                }
                printf("results from all processors= %d \n ",globalsum);
        }
        MPI_Finalize();
}

