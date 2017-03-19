#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1024*1024
#define nTHREAD 512

__global__ void min(float *input, float *out) {
	__shared__ float sData[nTHREAD];
	int tid = threadIdx.x;
	int iter = tid + blockIdx.x*blockDim.x;
	sData[tid] = input[iter];
	__syncthreads();
	for(int s = blockDim.x/2; s > 0; s /= 2) {
		if(iter < (s+blockIdx.x*blockDim.x)) {
			sData[tid] = (sData[tid] < sData[tid+s]) ? sData[tid] : sData[tid+s];  
		}
		__syncthreads();
	}
	if(tid == 0) {		
		out[blockIdx.x] = sData[0]; 
	}
}

__global__ void max(float *input, float *out) {
	__shared__ float sData[nTHREAD];
	int tid = threadIdx.x;
	int iter = tid + blockIdx.x*blockDim.x;
	sData[tid] = input[iter];
	__syncthreads();
	for(int s = blockDim.x/2; s > 0; s /= 2) {
		if(iter < (s+blockIdx.x*blockDim.x)) {
			sData[tid] = (sData[tid] > sData[tid+s]) ? sData[tid] : sData[tid+s];  
		}
		__syncthreads();
	}
	if(tid == 0) {		
		out[blockIdx.x] = sData[0]; 
	}
}

__global__ void sumTotal(float *input, float *out) {
	__shared__ float sData[nTHREAD];
	int tid = threadIdx.x;
	int iter = tid + blockIdx.x*blockDim.x;
	sData[tid] = input[iter];
	__syncthreads();
	for(int s = blockDim.x/2; s > 0; s /= 2) {
		if(iter < (s+blockIdx.x*blockDim.x)) {
			sData[tid] = sData[tid] + sData[tid+s];  
		}
		__syncthreads();
	}
	if(tid == 0) {		
		out[blockIdx.x] = sData[0]; 
	}
}

__global__ void subNsquare(float *input, float *out, float *mean) {
	__shared__ float sData[nTHREAD];
	int tid = threadIdx.x;
	int iter = tid + blockIdx.x*blockDim.x;
	sData[tid] = input[iter];
	out[iter] = pow(sData[tid] - *mean, 2);
}

__global__ void subNpowr4(float *input, float *out, float *mean) {
	__shared__ float sData[nTHREAD];
	int tid = threadIdx.x;
	int iter = tid + blockIdx.x*blockDim.x;
	sData[tid] = input[iter];
	out[iter] = pow(sData[tid] -* mean, 4); 
}

int main() {
	float *input, *out, *_input, *_out;
	cudaEvent_t start, stop;
	float _time = 0.0;
	time_t seconds;	
	
	cudaEventCreate(&start);	
	cudaEventCreate(&stop);
	input = (float*)malloc(sizeof(float)*SIZE);
	out = (float*)malloc(sizeof(float)*SIZE);
	time(&seconds);
	srand((unsigned int)seconds);

	for(int i = 0; i < SIZE; i++) {
		input[i] = (float)rand()/(float)(RAND_MAX) * SIZE;
	}
	
	cudaError_t err1, err2;
	err1 = cudaMalloc((void**)&_input, sizeof(float)*SIZE);
	err2 = cudaMalloc((void**)&_out, sizeof(float)*SIZE);
	if(err1 != cudaSuccess || err2 != cudaSuccess) {
		printf("Error in allocation %d %d\n", err1, err2);
		exit(0);
	}
	
	// Minimum Calculation
	cudaMemcpy(_input, input, sizeof(float)*SIZE, cudaMemcpyHostToDevice);
	
	cudaEventRecord(start, 0);
	int flag = 0;
	int block = SIZE/nTHREAD, remainder;
	while(block > 1) {
		if(flag == 0) {
			min<<<block,nTHREAD >>>(_input, _out);
			flag = 1;
		}
		else {
			min<<<block,nTHREAD >>>(_out, _input);
			flag = 0;
		}
		remainder = block;
		block /= nTHREAD;
	}
	if(flag == 0) {
		min<<<1, remainder>>>(_input, _out);
		cudaMemcpy(out, _out, sizeof(float)*SIZE, cudaMemcpyDeviceToHost);
	}
	else {
		min<<<1, remainder>>>(_out, _input);	
		cudaMemcpy(out, _input, sizeof(float)*SIZE, cudaMemcpyDeviceToHost);
	}
	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&_time, start, stop);
	printf("Elapsed Time(MIN) = %f\n", _time);
	
	cudaMemcpy(out, _out, sizeof(float)*SIZE, cudaMemcpyDeviceToHost);
	printf("MIN = %f\n",out[0]);
	
	// Maximum Calculation
	cudaMemcpy(_input, input, sizeof(float)*SIZE, cudaMemcpyHostToDevice);
	
	cudaEventRecord(start, 0);
	flag = 0;
	block = SIZE/nTHREAD;
	while(block > 1) {
		if(flag == 0) {
			max<<<block,nTHREAD >>>(_input, _out);
			flag = 1;
		}
		else {
			max<<<block,nTHREAD >>>(_out, _input);
			flag = 0;
		}
		remainder = block;
		block /= nTHREAD;
	}
	if(flag == 0) {
		max<<<1, remainder>>>(_input, _out);
		cudaMemcpy(out, _out, sizeof(float)*SIZE, cudaMemcpyDeviceToHost);
	}
	else {
		max<<<1, remainder>>>(_out, _input);	
		cudaMemcpy(out, _input, sizeof(float)*SIZE, cudaMemcpyDeviceToHost);
	}
	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&_time, start, stop);
	printf("Elapsed Time(MAX) = %.5f\n", _time);
	
	cudaMemcpy(out, _out, sizeof(float)*SIZE, cudaMemcpyDeviceToHost);
	printf("MAX = %f\n",out[0]);
	
	// STD calculation
	cudaMemcpy(_input, input, sizeof(float)*SIZE, cudaMemcpyHostToDevice);
	
	cudaEventRecord(start, 0);
	flag = 0;
	block = SIZE/nTHREAD;
	while(block > 1) {
		if(flag == 0) {
			sumTotal<<<block, nTHREAD>>>(_input, _out);
			flag = 1;
		}
		else {
			sumTotal<<<block,nTHREAD >>>(_out, _input);
			flag = 0;
		}
		remainder = block;
		block /= nTHREAD;
	}
	if(flag == 0) {
		sumTotal<<<1, remainder>>>(_input, _out);
		cudaMemcpy(out, _out, sizeof(float)*SIZE, cudaMemcpyDeviceToHost);
	}
	else {
		sumTotal<<<1, remainder>>>(_out, _input);	
		cudaMemcpy(out, _input, sizeof(float)*SIZE, cudaMemcpyDeviceToHost);
	}
	
	float mean = out[0], *_mean = NULL;
	mean /= SIZE;
	cudaMemcpy(_mean, &mean, sizeof(float), cudaMemcpyHostToDevice);
	
	block = SIZE/nTHREAD;
	cudaMemcpy(_input, input, sizeof(float)*SIZE, cudaMemcpyHostToDevice);
	subNsquare<<<block, nTHREAD>>>(_input, _out, _mean);
	cudaMemcpy(out, _out, sizeof(float)*SIZE, cudaMemcpyDeviceToHost);	
	cudaMemcpy(_input, out, sizeof(float)*SIZE, cudaMemcpyHostToDevice);	
	flag = 0;
	block = SIZE/nTHREAD;
	while(block > 1) {
		if(flag == 0) {
			sumTotal<<<block, nTHREAD>>>(_input, _out);
			flag = 1;
		}
		else {
			sumTotal<<<block,nTHREAD >>>(_out, _input);
			flag = 0;
		}
		remainder = block;
		block /= nTHREAD;
	}
	if(flag == 0) {
		sumTotal<<<1, remainder>>>(_input, _out);
		cudaMemcpy(out, _out, sizeof(float)*SIZE, cudaMemcpyDeviceToHost);
	}
	else {
		sumTotal<<<1, remainder>>>(_out, _input);	
		cudaMemcpy(out, _input, sizeof(float)*SIZE, cudaMemcpyDeviceToHost);
	}
	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&_time, start, stop);
	printf("Elapsed Time(STD) = %.5f\n", _time);
	
	float std = out[0];
	std /= SIZE;
	std = sqrt(std);
	printf("STD = %f\n", std);
	
	// Kurtosis calculation

	cudaMemcpy(_input, input, sizeof(float)*SIZE, cudaMemcpyHostToDevice);
	
	cudaEventRecord(start, 0);
	block = SIZE/nTHREAD;
	subNpowr4<<<block, nTHREAD>>>(_input, _out, _mean);

	cudaMemcpy(out, _out, sizeof(float)*SIZE, cudaMemcpyDeviceToHost);	
	cudaMemcpy(_input, out, sizeof(float)*SIZE, cudaMemcpyHostToDevice);	
	flag = 0;
	block = SIZE/nTHREAD;
	while(block > 1) {
		if(flag == 0) {
			sumTotal<<<block, nTHREAD>>>(_input, _out);
			flag = 1;
		}
		else {
			sumTotal<<<block,nTHREAD >>>(_out, _input);
			flag = 0;
		}
		remainder = block;
		block /= nTHREAD;
	}
	if(flag == 0) {
		sumTotal<<<1, remainder>>>(_input, _out);
		cudaMemcpy(out, _out, sizeof(float)*SIZE, cudaMemcpyDeviceToHost);
	}
	else {
		sumTotal<<<1, remainder>>>(_out, _input);	
		cudaMemcpy(out, _input, sizeof(float)*SIZE, cudaMemcpyDeviceToHost);
	}
	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&_time, start, stop);
	printf("Elapsed Time(kurtosis) = %.5f\n", _time);
	
	float kurtosis = out[0];
	kurtosis /= SIZE;
	kurtosis /= pow(std, 4);
	printf("Kurtosis = %f\n", kurtosis);

	cudaFree(_input);
	cudaFree(_out);
	cudaFree(_mean);
}
