#include <pmmintrin.h> // SSE3
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

__m128 vec_sum(const __m128 v0, const __m128 v1,
	       const __m128 v2, const __m128 v3)
{
 /* Your code here... */
}


int main()
{
  int N=4, i;
  float a[N], b[N], c[N], d[N], res[N];
  for(i = 0; i < N; i++)
	{
		a[i] = 1;
		b[i] = 2;
		c[i] = 3;
		d[i] = 4;
	}

  __m128 va, vb, vc, vd, vres;

  va = _mm_loadu_ps(a);
  vb = _mm_loadu_ps(b);
  vc = _mm_loadu_ps(c);
  vd = _mm_loadu_ps(d);

  printf("Call function copy_vect()...\n");
  vres = vec_sum(va, vb, vc, vd);

  _mm_storeu_ps(res, vres);

  assert(res[0] == 4);
  assert(res[1] == 8);
  assert(res[2] == 12);
  assert(res[3] == 16);

  printf("Great! No errors!\n");

  return 0;
}

