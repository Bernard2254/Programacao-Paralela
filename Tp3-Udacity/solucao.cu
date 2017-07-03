#include <limits.h>

#include <float.h>

#include <math.h>

#include <stdio.h>



#include "utils.h"



#define THREADS 1024



__global__

void histograma(unsigned int* d_bins, const float* d_in, const int bins, const float min, const float max, const int size) {  

    int main_id = threadIdx.x+blockDim.x * blockIdx.x;

    float range = max-min;

    int bin_id = ((d_in[main_id]-min)/range)*bins;

    

    atomicAdd(&d_bins[bin_id], 1);

}



__global__ 

void scan(unsigned int* d_bins, int size) {

    int main_id = threadIdx.x + blockDim.x * blockIdx.x;

    

    for(int s = 1; s <= size; s *= 2) {

          int ind = main_id - s; 

         

          unsigned int val = 0;

          if(ind >= 0)

              val = d_bins[ind];

          __syncthreads();

              d_bins[main_id] += val;

          __syncthreads();

    }

}



__global__

void reduction_kernel(const float* const d_kernel_in, float* d_kernel_out, const size_t size, int minmax) {

    extern __shared__ float shared[];

    

    int main_id = threadIdx.x + blockDim.x * blockIdx.x;

    int thread_id = threadIdx.x; 

    

    if(main_id < size) 

        shared[thread_id] = d_kernel_in[main_id];

    __syncthreads();

       

    for(int s = blockDim.x/2; s > 0; s /= 2) {

        if(thread_id < s) {

            if(minmax == 0)

                shared[thread_id] = min(shared[thread_id], shared[thread_id+s]);

            else

                shared[thread_id] = max(shared[thread_id], shared[thread_id+s]);

        }

        __syncthreads();

    }

    

    if(thread_id == 0)

        d_kernel_out[blockIdx.x] = shared[0];

}



float reduction(const float* const d_in, const size_t size, int minmax) {

    float* d_kernel_in;

    

    cudaMalloc(&d_kernel_in, sizeof(float) * size);    

    cudaMemcpy(d_kernel_in, d_in, sizeof(float) * size, cudaMemcpyDeviceToDevice);





    float* d_kernel_out;



    const int mem_size = sizeof(float)*THREADS;

    dim3 block_reduction = (size+THREADS-1)/THREADS;



    for(size_t kernel_size = THREADS*size - (THREADS-1);  kernel_size >= THREADS; ){

        kernel_size = (kernel_size+THREADS-1)/THREADS;

        cudaMalloc(&d_kernel_out, sizeof(float) * (kernel_size+THREADS-1)/THREADS);

        reduction_kernel<<<block_reduction, THREADS, mem_size>>>(d_kernel_in, d_kernel_out, kernel_size, minmax);

        d_kernel_in = d_kernel_out;

    }

    

    float out;

    cudaMemcpy(&out, d_kernel_out, sizeof(float), cudaMemcpyDeviceToHost);

    return out;

}



void your_histogram_and_prefixsum(const float* const d_logLuminance,

                                  unsigned int* const d_cdf,

                                  float &min_logLum,

                                  float &max_logLum,

                                  const size_t numRows,

                                  const size_t numCols,

                                  const size_t numBins)

{

    const size_t size = numRows*numCols;

    

    max_logLum = reduction(d_logLuminance, size, 1);

    min_logLum = reduction(d_logLuminance, size, 0);

    

    size_t histograma_size = sizeof(unsigned int)*numBins;



    cudaMemset(d_cdf, 0, histograma_size);  

    histograma<<<(numCols*numRows + THREADS - 1)/THREADS, THREADS>>>(d_cdf, d_logLuminance, numBins, min_logLum, max_logLum, size);

    scan<<<(numBins + THREADS -1)/THREADS, THREADS>>>(d_cdf, numBins);

    

    

  //TODO

  /*Here are the steps you need to implement

    1) find the minimum and maximum value in the input logLuminance channel

       store in min_logLum and max_logLum

    2) subtract them to find the range

    3) generate a histogram of all the values in the logLuminance channel using

       the formula: bin = (lum[i] - lumMin) / lumRange * numBins

    4) Perform an exclusive scan (prefix sum) on the histogram to get

       the cumulative distribution of luminance values (this should go in the

       incoming d_cdf pointer which already has been allocated for you)       */

}
