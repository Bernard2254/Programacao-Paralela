/**
 * SSE matrix multiplication
 *
 * Course: High Performance Computing and Programming, Uppsala University
 * Course Part: Lab 4
 *
 * Author: Andreas Sandberg <andreas.sandberg@it.uu.se>
 * Modified by: Marcus Holm <marcus.holm@it.uu.se>
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <pmmintrin.h>

#ifndef __SSE3__
#error This example requires SSE3
#endif

#include "util.h"

/* Size of the matrices to multiply */
#define SIZE 2048

#define SSE_BLOCK_SIZE 4

#ifndef L1_BLOCK_SIZE
#define L1_BLOCK_SIZE 64
#endif

#ifndef L2_BLOCK_SIZE
#define L2_BLOCK_SIZE 1024
#endif

#define XMM_ALIGNMENT_BYTES 16 // for SSE3

static float mat_a[SIZE][SIZE]   __attribute__((aligned (XMM_ALIGNMENT_BYTES)));
static float mat_b[SIZE][SIZE]   __attribute__((aligned (XMM_ALIGNMENT_BYTES)));
static float mat_c[SIZE][SIZE]   __attribute__((aligned (XMM_ALIGNMENT_BYTES)));
static float mat_ref[SIZE][SIZE] __attribute__((aligned (XMM_ALIGNMENT_BYTES)));




/* TASK: Ensure that this matrix multiplication is autovectorized */
void matmul_autovec()
{
  int i, j, k;

  for (i = 0; i < SIZE; i++) {
    for (k = 0; k < SIZE; k++) {
      for (j = 0; j < SIZE; j++) {
	mat_c[i][j] += mat_a[i][k] * mat_b[k][j];
      }
    }
  }
}


/**
 * Reference implementation of the matrix multiply algorithm. Used to
 * verify the answer from matmul_opt. Do NOT change this function.
 */
__attribute__((optimize("no-tree-vectorize"))) 
void matmul_ref()
{
  int i, j, k;

  for (i = 0; i < SIZE; i++) {
    for (k = 0; k < SIZE; k++) {
      for (j = 0; j < SIZE; j++) {
	mat_ref[i][j] += mat_a[i][k] * mat_b[k][j];
      }
    }
  }

}




/**
 * Function used to verify the result. No need to change this one.
 */
static int
verify_result()
{
  float e_sum;
  int i, j;

  e_sum = 0;
  for (i = 0; i < SIZE; i++) {
    for (j = 0; j < SIZE; j++) {
      e_sum += mat_c[i][j] < mat_ref[i][j] ?
	mat_ref[i][j] - mat_c[i][j] :
	mat_c[i][j] - mat_ref[i][j];
    }
  }

  printf("e_sum: %f\n", e_sum);

  return e_sum < 1E-6;
}

/**
 * Initialize mat_a and mat_b with "random" data. Write to every
 * element in mat_c to make sure that the kernel allocates physical
 * memory to every page in the matrix before we start doing
 * benchmarking.
 */
__attribute__((optimize("no-tree-vectorize")))  
void init_matrices()
{
  int i, j;

  for (i = 0; i < SIZE; i++) {
    for (j = 0; j < SIZE; j++) {
      mat_a[i][j] = ((i + j) & 0x0F) * 0x1P-4F;
      mat_b[i][j] = (((i << 1) + (j >> 1)) & 0x0F) * 0x1P-4F;
    }
  }

  memset(mat_ref, 0, sizeof(*mat_ref));
  memset(mat_c, 0, sizeof(*mat_c));

}

static void
run_multiply()
{
  struct timeval ts_start, ts_stop;
  double runtime_ref, runtime_autovec;

  printf("Starting autovec run...\n");
  util_monotonic_time(&ts_start);
  matmul_autovec();
  util_monotonic_time(&ts_stop);
  runtime_autovec = util_time_diff(&ts_start, &ts_stop);
  printf("Autovec run completed in %.2f s\n",
	 runtime_autovec);

  printf("Starting reference run...\n");
  util_monotonic_time(&ts_start);
  matmul_ref();
  util_monotonic_time(&ts_stop);
  runtime_ref = util_time_diff(&ts_start, &ts_stop);
  printf("Reference run completed in %.2f s\n",
	 runtime_ref);

  printf("Speedup: %.2f\n",
	 runtime_ref / runtime_autovec);


  if (verify_result())
    printf("OK\n");
  else
    printf("MISMATCH\n");
}

int
main(int argc, char *argv[])
{
  /* Initialize the matrices with some "random" data. */
  init_matrices();

  run_multiply();

  return 0;
}

