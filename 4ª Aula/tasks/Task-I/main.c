
#include <pmmintrin.h> // SSE3
#include <immintrin.h> // AVX
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>


struct timespec start, finish;
double elapsedSSE3;
double elapsedAVX;

void copy_vectSSE3int ( int * dst, const int* src, size_t len)
{


  int VECT_LEN=4;


  clock_gettime(CLOCK_MONOTONIC, &start);		
  int i;
  // length of the array must be a multiple of the vector size VECT_LEN
  for(i = 0; i < len; i += VECT_LEN )
    {
      __m128i v = _mm_loadu_si128((__m128i *) (src+i));
      _mm_storeu_si128((__m128i *)(dst+i), v);
    }
   clock_gettime(CLOCK_MONOTONIC, &finish);
   elapsedSSE3 = (finish.tv_sec - start.tv_sec);
   elapsedSSE3 += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
   printf("Time of SSE3 int: %lf\n",elapsedSSE3);
}

void copy_vectSSE3char ( char * dst, const char* src, size_t len)
{


  int VECT_LEN=16;


  clock_gettime(CLOCK_MONOTONIC, &start);		
  int i;
  // length of the array must be a multiple of the vector size VECT_LEN
  for(i = 0; i < len; i += VECT_LEN )
    {
      __m128i v = _mm_loadu_si128((__m128i *) (src+i));
      _mm_storeu_si128((__m128i *)(dst+i), v);
    }
   clock_gettime(CLOCK_MONOTONIC, &finish);
   elapsedSSE3 = (finish.tv_sec - start.tv_sec);
   elapsedSSE3 += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
   printf("Time of SSE3 char: %lf\n",elapsedSSE3);
}

void copy_vectAVXchar ( char * dst, const char* src, size_t len)
{


  int VECT_LEN=32;


  clock_gettime(CLOCK_MONOTONIC, &start);		
  int i;
  // length of the array must be a multiple of the vector size VECT_LEN
  for(i = 0; i < len; i += VECT_LEN )
    {
      __m256i v = _mm256_loadu_si256((__m256i *) (src+i));
      _mm256_storeu_si256((__m256i *)(dst+i), v);
    }
   clock_gettime(CLOCK_MONOTONIC, &finish);
   elapsedAVX = (finish.tv_sec - start.tv_sec);
   elapsedAVX += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
   printf("Time of AVX char: %lf\n",elapsedAVX);
}

void copy_vectAVXint ( int * dst, const int* src, size_t len)
{


  int VECT_LEN=8;


  clock_gettime(CLOCK_MONOTONIC, &start);		
  int i;
  // length of the array must be a multiple of the vector size VECT_LEN
  for(i = 0; i < len; i += VECT_LEN )
    {
      __m256i v = _mm256_loadu_si256((__m256i *) (src+i));
      _mm256_storeu_si256((__m256i *)(dst+i), v);
    }
   clock_gettime(CLOCK_MONOTONIC, &finish);
   elapsedAVX = (finish.tv_sec - start.tv_sec);
   elapsedAVX += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
   printf("Time of AVX int: %lf\n",elapsedAVX);
}

int main()
{
  int N = 160000;
  char csrc[N], cdst[N];
  int isrc[N], idst[N];

  printf("Call function copy_vect()...\n");

  copy_vectSSE3int(isrc, idst, N);
  copy_vectSSE3char(csrc, cdst, N);
  copy_vectAVXchar(csrc, cdst, N);
  copy_vectAVXint(isrc, idst, N);

  return 0;
}

