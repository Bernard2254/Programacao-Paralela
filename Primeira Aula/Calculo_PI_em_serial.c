#include <stdio.h>
#include <time.h>
static long num_steps = 1000000;
double step;
clock_t inicio, fim, decorrido;
int main ()
{
	 inicio = clock(); 
	 int i; double x, pi, sum = 0.0;
	 step = 1.0/(double) num_steps;
	 
	 for (i=0;i< num_steps; i++){
	 	x = (i+0.5)*step;
	 	sum = sum + 4.0/(1.0+x*x);
	 }

	 pi = step * sum;
	 printf("%f\n", pi);
	 fim = clock();
	 decorrido = ((fim - inicio) / (CLOCKS_PER_SEC / 1000));
	 printf("%f", (double)decorrido);
}