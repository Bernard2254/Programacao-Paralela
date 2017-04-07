#include <pmmintrin.h> //SSE3
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define VALUE 4242

typedef short int Type; 

void threshold(Type *dst, const Type *src, int len)
{
	/* Your code here... */
}


int main()
{
  int N = 1024;
  Type dst[N], src[N];

  // fill in arrays
  int i;
  for(i = 0; i < N; i++)
    src[i] = rand()%VALUE; 

  printf("Call function threshold()...\n");
  threshold(dst, src, N);

  // check result  
 for(i = 0; i < N; i++)
   assert(dst[i] == ( src[i] > VALUE ? 0xFFFF : 0 ));

 printf("Great! No errors!\n");
  return 0;
}
