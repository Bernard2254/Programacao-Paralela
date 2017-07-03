#include "utils.h"

#define THREADS 16

__constant__ float cfilter[81];

__global__
void gaussian_blur(uchar4* const input, uchar4* const output,
                   int numRows, int numCols, const int filterWidth)
{
  int x= threadIdx.x + (blockIdx.x*blockDim.x);
  int y = threadIdx.y + (blockIdx.y*blockDim.y);
  int l, m;

  if (x< numCols && y < numRows)
  {
    float s = 0, s2 = 0, s3 = 0;
    x-= filterWidth/2;   y -= filterWidth/2;
    #pragma unroll
    for (int i = 0; i < filterWidth; i++)
    { 
      m = min(max(y +i, 0), numRows-1);
      for (int j = 0; j < filterWidth; j++)
      {
        l = min(max(x+j, 0), numCols-1);
        register int k = i*filterWidth + j;
        register int c = m*numCols + l;
        s+= cfilter[k] * input[c].x;
        s2 += cfilter[k] * input[c].y;
        s3 += cfilter[k] * input[c].z;
      }
    }

    x+= filterWidth/2;   y += filterWidth/2;
    output[x+(y*numCols)].x = s;
    output[x+ (y*numCols)].y = s2;
    output[x+ (y*numCols)].z = s3;
  }
}

//unsigned char *d_red, *d_green, *d_blue;
float         *d_filter;

void allocateMemoryAndCopyToGPU(const size_t numRowsImage, const size_t numColsImage,
                                 const float* const h_filter, const size_t filterWidth)
{
  int num = filterWidth * filterWidth;
  //cudaMalloc(&d_filter, sizeof(float) * num);
  //cudaMemcpy(d_filter, h_filter, sizeof(float) * num, cudaMemcpyHostToDevice);
  cudaMemcpyToSymbol(cfilter, h_filter, sizeof(float) * num);

}

void your_gaussian_blur(const uchar4 * const h_inputImageRGBA, uchar4 * const d_inputImageRGBA,
                        uchar4* const d_outputImageRGBA, const size_t numRows, const size_t numCols,
                        unsigned char *d_redBlurred, 
                        unsigned char *d_greenBlurred, 
                        unsigned char *d_blueBlurred,
                        const int filterWidth)
{
  
  const dim3 blockSize(THREADS, THREADS);
  const dim3 gridSize((numCols+THREADS-1)/THREADS, (numRows+THREADS-1)/THREADS);
 
  gaussian_blur<<<gridSize, blockSize>>>(d_inputImageRGBA, d_outputImageRGBA, numRows, numCols, filterWidth);
  
}

void cleanup() {
}
