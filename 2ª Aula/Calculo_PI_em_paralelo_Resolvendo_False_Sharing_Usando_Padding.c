#include <stdio.h>
#include <omp.h>
#include <time.h>

#define NUM_THREADS 2
#define PAD 8 //assume 64 byte L1 cache line size; double = 8 bytes cabe 8 na linha 
			  //depende muito da arquitetura
static long num_steps = 1000000; 
double step;
clock_t inicio, fim, decorrido;
int main ()
{ 
 inicio = clock();
 int i, nthreads; double pi, sum[NUM_THREADS][PAD];
 step = 1.0/(double) num_steps;
 
 #pragma omp parallel num_threads(NUM_THREADS)
 {
	int i, id,nthrds;
 	double x;
 	id = omp_get_thread_num(); //Pega ID da Thread que está executando
 	nthrds = omp_get_num_threads(); //Pega número de Threads que serão executadas
 	if (id == 0) nthreads = nthrds; //por padrão id=0 é a Thread master -> Ela atualiza a variável global
 									//se todas as threads atualizassem poderia dar problema de acesso a memória compartilhada
	 for (i=id, sum[id]=0.0;i< num_steps; i=i+nthrds) {
	 	x = (i+0.5)*step;
	 	sum[id][0] += 4.0/(1.0+x*x); //Coloca as variáveis em coluna uma mesma coluna do cache, mas em linhas diferentes
	 }
 }
 for(i=0, pi=0.0;i<nthreads;i++)pi += sum[i][0] * step;
 printf("%f\n", pi);
 fim = clock();
 decorrido = ((fim - inicio) / (CLOCKS_PER_SEC / 1000));
 printf("%f\n", (double)decorrido);
}

/*
ANTES: Cache tem que trocar linha toda hora que atualiza um sum[i] mesmo sem a thread usar a variável que foi modificada
cache: sum[0] sum[1] sum[2] sum[3]
		0     0      0     0

AGORA: Não vai precisar trocar a linha toda hora
cache: sum[0]  0     0      0
	   sum[1]  0     0      0
	   sum[2]  0     0      0
	   sum[3]  0     0      0
*/