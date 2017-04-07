#ifndef DLAITONMATRIX_H
#define DLAITONMATRIX_H

#include <stdlib.h>

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

int ***Aloc3DMat(int x, int y, int z) {
    int ***v;
    if ((x < 1) || (y < 1) || (z < 1)) 
   		return NULL;
	v = (int ***)calloc(x, sizeof(int**));
   	for (int i = 0 ; i < x ; i++) {
    	v[i] = (int **)calloc(y, sizeof(int*));
      	for(int j=0;j<y;j++)
      		v[i][j]=(int*)calloc(z, sizeof(int));
   	}
   return v;
}

int **FreeMat(int linhas, int colunas, int **mat) {
   if ((linhas < 1) || (colunas < 1) || (mat == NULL) )
   		return NULL;
   for (int i = 0 ; i < linhas ; i++) 
   		free(mat[i]);
   free(mat);
   return NULL;   
}

int ***Free3DMat(int x, int y, int z, int ***mat) {
   if ((x < 1) || (y < 1) || (z < 1) || (mat == NULL) )
   		return NULL;
   for (int i = 0 ; i < x ; i++) 
   		for (int j = 0 ; j < y ; j++) 
   			free(mat[i][j]);
   free(mat);
   return NULL;   
}

void fillMatriz(int n, int m, int **matriz){
   for(int i=0;i<n;i++)
      for(int j=0;j<m;j++){
         matriz[i][j]=rand() % 10000;
      }
}

void fillMatrizWithValue(int n, int m, int **matriz, int v){
   for(int i=0;i<n;i++)
      for(int j=0;j<m;j++){
         matriz[i][j]=v;
      }
}

void fill3DMatrizWithValue(int n, int m, int o, int ***matriz, int v){
   for(int i=0;i<n;i++)
      for(int j=0;j<m;j++)
         for(int k=0;k<o;k++)
            matriz[i][j][k]=v;
      
}

#endif /* DLAITONMATRIX_H */