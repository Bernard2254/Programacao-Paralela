#include <stdio.h>
#include <omp.h>
#include <time.h>

#define NUM_THREADS 2

static long num_steps = 1000000; 
double step;
clock_t inicio, fim, decorrido;
int main ()
{ 
 inicio = clock();
 int i, nthreads; double pi, sum=0;
 step = 1.0/(double) num_steps;
 omp_lock_t writelock; //Declara cadeado
 omp_init_lock(&writelock); //Inicia cadeado
 #pragma omp parallel num_threads(NUM_THREADS) 
 {
	int i, id,nthrds;
 	double x;
 	id = omp_get_thread_num(); //Pega ID da Thread que está executando
 	nthrds = omp_get_num_threads(); //Pega número de Threads que serão executadas
 	if (id == 0) nthreads = nthrds; //por padrão id=0 é a Thread master -> Ela atualiza a variável global
 									//se todas as threads atualizassem poderia dar problema de acesso a memória compartilhada
	 for (i=id ;i< num_steps; i=i+nthrds) {
	 	x = (i+0.5)*step;
	 	omp_set_lock(&writelock); //Abre cadeado
	 		sum += 4.0/(1.0+x*x);
    	omp_unset_lock(&writelock); //Fecha cadeado
	 }
 }
 omp_destroy_lock(&writelock);
 pi += sum * step;
 printf("%f\n", pi);
 fim = clock();
 decorrido = ((fim - inicio) / (CLOCKS_PER_SEC / 1000));
 printf("%f\n", (double)decorrido);
}
/*variables: A = 1,B = 1, C = 1, X = 1;
#pragma omp parallel private(B) firstprivate(C) lastprivate(X) firstprivate(X)
A é compartilhada
B é privada mas não é considerada inicializada
C é privada e inicializada com 1
X é privada (devido o firstprivate será inicializado com 1) pode ser usada depois da região paralela
*/