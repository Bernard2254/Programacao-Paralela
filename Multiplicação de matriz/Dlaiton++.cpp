#include <iostream>
#include <chrono>
#include <time.h>

using namespace std;
using namespace std::chrono;

int x=3;
int y=3;
int t=3;
int r=3;

long getTime();
int **AlocMat(int linhas, int colunas);
int **FreeMat(int linhas, int colunas, int **mat);
void fillMatriz(int n, int m, int **matriz);
void Implicito(int **A, int **B, int **S0);
void Explicito(int **A, int **BT, int **S1);

int main(){
	long int init, end;
	int **A = AlocMat(x, y); fillMatriz(x, y, A);
	int **B = AlocMat(x, y); fillMatriz(x, y, B);
	/*
	int A[x][t]={{43,24,22},{66,43,22},{22,72,23}};
	int B[r][y]={{43,77,12},{98,65,67},{89,32,22}};
	int S[x][y]={{6159,5575,2608},{9010,8581,4157},{10049,7110,5594}};
	*/
	int **S0 = AlocMat(x, y);
	int **S1 = AlocMat(x, y);
	int S2[x][y][t+1];
	int S3[x][y][t];
	int **BT = AlocMat(x, y);

	for(int i=0;i<x;i++)
		for(int j=0;j<y;j++){
			S0[i][j]=0;
			S1[i][j]=0;
			BT[i][j]=B[j][i];
			for(int k=0;k<t;t++){
				S2[i][j][k]=0;
				S3[i][j][k]=1;
			}
			//S2[i][j][t]=0;
		}

	//verificar otimizacoes do slide da professora
	//verificar com matriz grande trocando ordem de ijk de todos os metodos
	//verificar quais metodos são mais rapidos para cada tamanho de matriz e matriz quadrada

		//verificar se é mais rapido salvar o elemento da matriz em uma var e depois usar ou ler diretamente da matriz
		//verificar se a+=2 é mais rapido que a=a+2
		//verificar se a*=2 é mais rapido que a=a*2
		//verificar se double é mais rapido que float
		//verificar se gcc é mais rapido q g++
		//verificar se iniciar matriz com c++ é mais rapido q c
		//verificar se é mais rapido a+0 ou a*1
		//verificar se é mais rapido declarar variavel dentro do for ou fora
		//verificar se é mais rapido o for de tras pra frente ou no sentido normal
	
	//percorrendo solucao transposto implicitamente
	Implicito(A, B, S0);
	//percorrendo solucao transposto explicitamente
	Explicito(A, BT, S1);
	//prevendo posicao outra opcao é iniciar S2 com 1 e apenas multiplicar os valores dentro do terceiro for mas depois temoos que achatar a matriz 3d somando a terceira dimensao pra ficar 2d
	init = getTime();
	for(int i=0;i<x;i++)
		for(int j=0;j<y;j++){
			double a=A[i][j],b=B[i][j];
			for(int k=0;k<t;k++){
				if(S2[i][k][j]!=0){//se tiver zero na matriz pode dar problema, para resolver podemos tentar diferenciar +0 de -0 usando bitsignificativo ou definir uma matriz de bool para verificar se foi o primeiro acesso
					S2[i][k][j]*=a;//segunda vez acessado
					S2[i][k][t]+=S2[i][k][j];//soma no valor final
				}else
					S2[i][k][j]=a;//primeira vez acessado


				if(S2[k][i][j]!=0){//se tiver zero na matriz pode dar problema, para resolver podemos tentar diferenciar +0 de -0 usando bitsignificativo ou definir uma matriz de bool para verificar se foi o primeiro acesso
					S2[k][i][j]*=b;//segunda vez acessado
					S2[k][i][t]+=S2[k][i][j];//soma no valor final
				}else
					S2[k][i][j]=b;//primeira vez acesado
			}
		}
	end = getTime();
	cout<<"Prevendo: "<< end-init<<endl;

	//prevendo posicao
	init = getTime();
	for(int i=0;i<x;i++)
		for(int j=0;j<y;j++){
			for(int k=0;k<t;k++){
					S3[i][k][j]*=A[i][j];
					S3[k][i][j]*=B[i][j];
			}
		}
	for(int i=0;i<x;i++)
	for(int j=0;j<y;j++){
		for(int k=1;k<t;k++){
				S3[i][j][0]+=S3[i][j][k];
				S3[i][j][0]+=S3[i][j][k];
		}
	}
	end = getTime();
	cout<<"achatando: "<< end-init<<endl;
}

int **AlocMat(int linhas, int colunas) {
   int x, **v;
   if ((linhas < 1) || (colunas < 1)) 
   		return NULL;

   v = (int **)calloc(linhas, sizeof(int));

   if (v == NULL) {
      printf("\nFatal Error! (function: AlocMat)\n");
      exit(1);
   }
   for (x = 0 ; x < linhas ; x++) {
      v[x] = (int *)calloc(colunas, sizeof(int));
      
      if (v[x] == NULL) {
         printf("\nFatal Error! (function: AlocMat)\n");
         exit(1);
      }
   }
   return v;
}

int **FreeMat(int linhas, int colunas, int **mat) {
   int x;
   if ((linhas < 1) || (colunas < 1)) {
      printf("\nFatal Error! (function: FreeMat)\n");
      exit(1);
   }
   if (mat == NULL) 
   		return NULL;
   for (x = 0 ; x < linhas ; x++) 
   		free(mat[x]);
   free(mat);
   return NULL;   
}

void fillMatriz(int n, int m, int **matriz){
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++){
			matriz[i][j]=rand() % 10000;
		}
}

void Implicito(int **A, int **B, int **S0){
	long int init, end;
	init = getTime();
	for(int i=0;i<x;i++)
			for(int j=0;j<y;j++)
				for(int k=0;k<t;k++){
					S0[i][j]=S0[i][j]+A[i][k]*B[k][j];				
				}
	end = getTime();
	cout<<"Implícito: "<< end-init<<endl;
}

void Explicito(int **A, int **BT, int **S1){
	long int init, end;
	init = getTime();
	for(int i=0;i<x;i++)
		for(int j=0;j<y;j++)
			for(int k=0;k<t;k++){
				S1[i][j]=S1[i][j]+A[i][k]*BT[j][k];				
			}
	end = getTime();
	cout<<"Explicito: "<< end-init<<endl;
}

long getTime(){
	//return clock()/CLOCKS_PER_SEC;
	return high_resolution_clock::now().time_since_epoch().count();
}