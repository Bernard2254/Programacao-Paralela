#include <stdio.h>
#include <omp.h>
#include <time.h>

#define NUM_THREADS 80

static long num_steps = 1000000; 
//clock_t inicio, fim, decorrido;
int main ()
{ 
 //inicio = clock();
 double pi = 0;
 double step = 1.0/(double) num_steps;
 
 #pragma omp parallel num_threads(NUM_THREADS)
 {
 	double x, soma=0;
 	int i;
 	#pragma omp for
		for(i=0; i<num_steps; i++){
			x = (i+0.5)*step;
	 		soma += 4.0/(1.0+x*x);
		}

	#pragma omp critical
		pi += soma*step;
 }
 printf("%f\n", pi);
 //fim = clock();
 //decorrido = ((fim - inicio) / (CLOCKS_PER_SEC / 1000));
 //printf("%f\n", (double)decorrido);
 return 0;
}