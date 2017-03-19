#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 20

__global__ void max(int *input)
{
	__shared__ int s_data[SIZE];
	int tid = threadIdx.x, flag;
	int i = tid + blockIdx.x*blockDim.x;

	s_data[tid] = input[i];
	__syncthreads();

	for( int s = blockDim.x/2, flag = blockDim.x%2; s > 0; s = s >> 1)
	{
		if(tid < s) {
			printf("%d\t-\t%d\t%d\t%d\n", s_data[tid], s_data[tid+s], s, tid);
			s_data[tid] = (s_data[tid]>=s_data[tid+s]) ? s_data[tid] : s_data[tid+s];
		}	 
		__syncthreads();
		if(s == 1) break;
		flag = s%2;
	}
	if(tid == 0) input[0] = s_data[0];
}

int main(int argc, char *argv[])
{
	int *input;
	int *d_input;
	cudaEvent_t start,stop;
	float etime;

	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	cudaEventRecord(start,0);
	input = (int*)malloc(sizeof(int) * SIZE);
	
	srand(time(0));
	for(int j=0;j<SIZE;j++)
	{
		input[j] = rand()%SIZE;
		printf(" %d ",input[j]);
	}printf("\n");
	cudaError_t err;
	err = cudaMalloc((void**)&d_input,sizeof(int)*SIZE);
	if(err != cudaSuccess)
		printf("Error allocating\n");

	//cudaMalloc((void**)&d_input,sizeof(int)*SIZE);
	cudaMemcpy(d_input,input,sizeof(int)*SIZE, cudaMemcpyHostToDevice);
	max<<<SIZE/10,10>>>(d_input);
	cudaMemcpy(input,d_input,sizeof(int)*SIZE, cudaMemcpyDeviceToHost);
	cudaEventRecord(stop,0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&etime,start,stop);
	printf(" max:%d ",input[0]);
	printf("\nTime:%f\n",etime);
	return 0;
}
