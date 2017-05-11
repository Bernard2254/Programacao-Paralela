#include <stdio.h>

__global__ void matMult(float *d_A,float *d_B, float *d_C, int n){
        int col = threadIdx.x + (blockDim.x * blockIdx.x);
        int row = threadIdx.y + (blockDim.y*blockIdx.y);
        if(col>=n||row>=n) return;
        float seguraPraMimBernard=0;
        for(int a=0;a<n;a++){
                seguraPraMimBernard+=d_A[row+a*n]*d_B[a+col*n];
        }
        d_C[row+col*n]=seguraPraMimBernard;
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
                A[i]=i;
                B[i]=i;
        }
        cudaMalloc((void **) &d_A, size);
        cudaMemcpy(d_A, A, size, cudaMemcpyHostToDevice);
        cudaMalloc((void **) &d_B, size);
        cudaMemcpy(d_B, B, size, cudaMemcpyHostToDevice);
        cudaMalloc((void **) &d_C, size);

        dim3 blockSize((N+(Nthreads -1))/Nthreads,(N+(Nthreads -1))/Nthreads,1);
        dim3 thrdPBlock(Nthreads,Nthreads,1);

        matMult<<<blockSize,thrdPBlock>>>(d_A, d_B, d_C, N);

        cudaMemcpy(C, d_C, size, cudaMemcpyDeviceToHost); //É uma função síncrona nativamente
        for(i=0; i<N; i++)
                printf("%f ", C[i]);
        cudaFree(d_A);cudaFree(d_B);cudaFree(d_C);
}