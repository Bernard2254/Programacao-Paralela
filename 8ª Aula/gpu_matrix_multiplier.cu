#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 10

int **AlocMat(int linhas, int colunas) {
   int **v;
   if ((linhas < 1) || (colunas < 1)) 
      return NULL;
   v = (int **)calloc(linhas, sizeof(int*));
   for (int i = 0 ; i < linhas ; i++) {
      v[i] = (int *)calloc(colunas, sizeof(int));
   }
   return v;
}

void fillMatriz(int n, int m, int **matriz){
   for(int i=0;i<n;i++)
      for(int j=0;j<m;j++){
         matriz[i][j]=rand() % 10000;
      }
}

int main(int argc, char *argv[])
{
    int **h_a, **h_out;
    int *d_a;

    int i;

    h_a = AlocMat(ARRAY_SIZE, ARRAY_SIZE);
    h_out = (ARRAY_SIZE, ARRAY_SIZE);

    cudaMalloc(&d_a, sz);
}
