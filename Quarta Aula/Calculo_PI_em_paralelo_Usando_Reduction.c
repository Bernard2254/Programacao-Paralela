#include <stdio.h>
#include <omp.h>
#include <time.h>

#define NUM_THREADS 2

static long num_steps = 1000000; 
clock_t inicio, fim, decorrido;
int main ()
{ 
 inicio = clock();
 double pi = 0;
 double step = 1.0/(double) num_steps;
 omp_set_num_threads(NUM_THREADS);
 
 #pragma omp parallel 
 {
 	double x;
 	int i;
 	#pragma omp for reduction(+:pi) //reduction operacao e variavel
		for(i=0; i<num_steps; i++){
			x = (i+0.5)*step;
	 		pi += 4.0/(1.0+x*x);
		}
 }
 printf("%f\n", pi*step);
 fim = clock();
 decorrido = ((fim - inicio) / (CLOCKS_PER_SEC / 1000));
 printf("%f\n", (double)decorrido);
 return 0;
}