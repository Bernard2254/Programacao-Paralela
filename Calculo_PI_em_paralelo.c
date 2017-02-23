#include <stdio.h>
#include <omp.h>
#include <time.h>

static long num_steps = 100000; 
double step;
clock_t inicio, fim, decorrido;
int main ()
{ 
 inicio = clock();
 int i, nthreads; double pi, sum[2];
 step = 1.0/(double) num_steps;
 
 #pragma omp parallel num_threads(2)
 {
	int i, id,nthrds;
 	double x;
 	id = omp_get_thread_num();
 	nthrds = omp_get_num_threads();
 	if (id == 0) nthreads = nthrds;
	 for (i=id, sum[id]=0.0;i< num_steps; i=i+nthrds) {
	 	x = (i+0.5)*step;
	 	sum[id] += 4.0/(1.0+x*x);
	 }
 }
 for(i=0, pi=0.0;i<nthreads;i++)pi += sum[i] * step;
 printf("%f\n", pi);
 fim = clock();
 decorrido = ((fim - inicio) / (CLOCKS_PER_SEC / 1000));
 printf("%f", (double)decorrido);
}