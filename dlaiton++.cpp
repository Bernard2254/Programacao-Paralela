#include <iostream>
#include <time.h>

using namespace std;

int x=3;
int y=3;
int t=3;
int r=3;

long getTime(){
	//return time(0);
	return clock();//high_resolution_clock::now().time_since_epoch().count();
}

int main(){
	int A[x][t]={(423,234,22),(666,423,22),(28472,7462,23)};
	int B[r][y]={(4234,7567,12),(98,6665,667),(89,32,22)};
	int S[x][y]={(1815872,4761155,161638),(2863256,7859621,290617),(121283771,265182590,5319324)};
	int S0[x][y];
	int S1[x][y];
	int S2[x][y][t+1];
	int S3[x][y][t];
	int BT[x][y];
	for(int i=0;i<x;i++)
		for(int j=0;j<y;j++){
			S0[i][j]=0;
			S1[i][j]=0;
			BT[i][j]=B[j][i];
			for(int k=0;k<t;t++){
				S2[i][j][k]=0;
				S3[i][j][k]=1;
			}
			S2[i][j][t]=0;
		}

	//verificar se a+=2 é mais rapido que a=a+2
	//verificar se a*=2 é mais rapido que a=a*2
	//verificar se é mais rapido salvar o elemento da matriz em uma var e depois usar ou ler diretamente da matriz
	//verificar se double é mais rapido que float
	//verificar se gcc é mais rapido q g++
	//verificar se iniciar matriz com c++ é mais rapido q c
	//verificar otimizacoes do slide da professora
	//verificar com matriz grande trocando ordem de ijk de todos os metodos
	//verificar quais metodos são mais rapidos para cada tamanho de matriz e matriz quadrada
	//verificar se é mais rapido a+0 ou a*1
	//verificar se é mais rapido declarar variavel dentro do for ou fora
	//verificar se é mais rapido o for de tras pra frente ou no sentido normal
	
	//percorrendo solucao transposto implicitamente
	long int init, end;
	init = getTime();
	for(int i=0;i<x;i++)
		for(int j=0;j<y;j++)
			for(int k=0;k<t;t++){
				S0[i][j]=S0[i][j]+A[i][k]*B[k][j];				
			}
	end = getTime();
	cout<<"Implícito: "<< end-init<<endl;
	//percorrendo solucao transposto explicitamente
	init = getTime();
	for(int i=0;i<x;i++)
		for(int j=0;j<y;j++)
			for(int k=0;k<t;t++){
				S1[i][j]=S1[i][j]+A[i][k]*BT[j][k];				
			}
	end = getTime();
	cout<<"Explícito: "<< end-init<<endl;
	//prevendo posicao outra opcao é iniciar S2 com 1 e apenas multiplicar os valores dentro do terceiro for mas depois temoos que achatar a matriz 3d somando a terceira dimensao pra ficar 2d
	init = getTime();
	for(int i=0;i<x;i++)
		for(int j=0;j<y;j++){
			double a=A[i][j],b=B[i][j];
			for(int k=0;k<t;t++){
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
			for(int k=0;k<t;t++){
					S3[i][k][j]*=A[i][j];
					S3[k][i][j]*=B[i][j];
			}
		}
	for(int i=0;i<x;i++)
	for(int j=0;j<y;j++){
		for(int k=1;k<t;t++){
				S3[i][j][0]+=S3[i][j][k];
				S3[i][j][0]+=S3[i][j][k];
		}
	}
	end = getTime();
	cout<<"achatando: "<< end-init<<endl;
}