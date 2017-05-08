#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>


#define NUM_THREADS 2
#define PAD 16

clock_t inicio, fim;

void main(){
		int linhas, colunas, i, j;
		srand(0);
		printf("\nDigite o numero de linhas da matriz: ");
		scanf("%d", &linhas);
		printf("Digite o numero de colunas da matriz: ");
		scanf("%d", &colunas);

		int matriz1[linhas][colunas], matriz2[colunas][linhas],
		y[linhas][PAD],yaux[linhas][PAD], x[colunas];

		for(i=0; i<linhas; i++){
			x[i] = rand()%10 + 1;
			for(j=0; j<colunas; j++){
				matriz1[i][j] = rand()%10 + 1;
			//	printf("%d ", matriz1[i][j]);
			}
	//		printf("\n");
		}
	//	printf("\n");

		for(i=0; i<colunas; i++){
			for(j=0; j<linhas; j++){
				matriz2[i][j] = rand()%10 + 1;
			//	printf("%d ", matriz2[i][j]);
			}
	//		printf("\n");
		}

		printf("\n");
		inicio = clock();
		for(i=0; i<linhas; i++){
			yaux[i][0] = 0;
			for(j=0; j<colunas; j++){
				yaux[i][0] += matriz1[i][j]*x[j];
			}
		}
		fim = clock();
		printf("SERIAL: %f\n", (double)((fim - inicio) / (CLOCKS_PER_SEC / 1000)));

		inicio = clock();
		#pragma omp parallel num_threads(NUM_THREADS)
		{
			int i, j, id, local[linhas][PAD];
			id = omp_get_thread_num();
			for(i = id; i < linhas; i+=2){
				local[i][0] = 0;
				for(j = 0; j < colunas; j++)
					local[i][0] += matriz1[i][j]*x[j];
				y[i][0] = local[i][0];
			}
		}
		fim = clock();
		printf("PARALELO: %f\n", (double)((fim - inicio) / (CLOCKS_PER_SEC / 1000)));
		printf("\n");
		int igual=1;
		for(i=0; i<linhas; i++){
			if(yaux[i][0] != y[i][0])
				igual = 0;
	//		printf("%d ", y[i][0]);
		}
		if(igual)
			printf("\nFunfou!!!\n");
		else
			printf("\nDesfunfou :(\n");
}