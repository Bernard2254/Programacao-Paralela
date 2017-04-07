#include <iostream>
#include "DlaitonMatrix.h"

#define GCC 0

#if GCC==1
	#include "DlaitonPerf.h"
#else
	#include "DlaitonChronoPerf.h"
	long getTime(){
		return getNanoSec();
	}
#endif

#include "DlaitonMultiplier.h"

using namespace std;


int x=100;int t=100;//A
int r=t;int y=100;//B

//verificar otimizacoes do slide da professora
//verificar com matriz grande trocando ordem de ijk de todos os metodos
//verificar quais metodos são mais rapidos para cada tamanho de matriz e matriz quadrada
//aplicar fundamentos dos speedtest

int main(){
	long int init, end;
	int **A = AlocMat(x, t); fillMatriz(x, t, A);
	int **B = AlocMat(r, y); fillMatriz(r, y, B);
	int **BT = AlocMat(y, r);
	for(int i=0;i<r;i++)
		for(int j=0;j<y;j++)
			BT[j][i]=B[i][j];
	int **S0 = AlocMat(x, y);//calloc ja deixa 0
	int **S1 = AlocMat(x, y);//calloc ja deixa 0
	int ***S2 = Aloc3DMat(x,y,t+1);
	int ***S3 = Aloc3DMat(x,y,t);

	fill3DMatrizWithValue(x,y,t,S3,1);
	char *name;
	long bestOfAll;
	long implicito, explicito, prevendo, achatando;

	implicito=Implicito(A, B, S0,x,y,t);
	explicito=Explicito(A, BT, S1,x,y,t);
	prevendo=Prevendo(A,B,S2,x,y,t);
	achatando=Achatando(A,B,S3,x,y,t);

	cout<<"Implicito ";cout.width(9);cout<<right<<implicito<<endl;
	cout<<"Explicito ";cout.width(9);cout<<right<<explicito<<endl;
	cout<<"Prevendo  ";cout.width(9);cout<<right<<prevendo<<endl;
	cout<<"Achatando ";cout.width(9);cout<<right<<achatando<<endl;

	bestOfAll=implicito;
	if(explicito<bestOfAll)bestOfAll=explicito;
	if(prevendo<bestOfAll)bestOfAll=prevendo;
	if(achatando<bestOfAll)bestOfAll=achatando;

	if(bestOfAll==implicito)name="implicito";
	else if(bestOfAll==explicito)name="explicito";
	else if(bestOfAll==prevendo)name="prevendo";
	else if(bestOfAll==achatando)name="achatando";
	else name="err";

	cout<<endl<<"Melhor algoritmo "<<name<<" \n\n";
	
}