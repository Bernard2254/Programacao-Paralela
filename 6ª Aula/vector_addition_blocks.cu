#include <stdio.h>

__global__ void vecAdd(float *d_A,float *d_B, float *d_C, int N){
	int id = threadIdx.x + (blockDim.x * blockIdx.x);
	if(id<N)	
		d_C[id] = d_A[id] + d_B[id];
}

int main(){
	int N=32;
	int Nthreads = 256;
	int size = N*sizeof(float); float *d_A, *d_B, *d_C; 
	float *A, *B, *C;

	A = (float*)malloc(size);
	B = (float*)malloc(size);
	C = (float*)malloc(size);
	int i=0;
	for(i=0; i<N; i++){
		A[i] = i;
		B[i] = i;
	}
	cudaMalloc((void **) &d_A, size);
	cudaMemcpy(d_A, A, size, cudaMemcpyHostToDevice);
	cudaMalloc((void **) &d_B, size);
	cudaMemcpy(d_B,	B, size, cudaMemcpyHostToDevice);
	cudaMalloc((void **) &d_C, size);

	vecAdd<<<(N+(Nthreads -1))/Nthreads, Nthreads>>>(d_A, d_B, d_C, N);

	cudaMemcpy(C, d_C, size, cudaMemcpyDeviceToHost); //É uma função síncrona nativamente
	for(i=0; i<N; i++)
		printf("%f ", C[i]);
	cudaFree(d_A);cudaFree(d_B);cudaFree(d_C);
}
