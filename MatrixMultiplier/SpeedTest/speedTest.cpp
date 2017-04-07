#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../DlaitonMatrix.h"

#define NOFTESTS 10000
#define ITERATIONS 10000
#define GCC 1

#if GCC==1
	#include "../DlaitonPerf.h"
#else
	#include "../DlaitonChronoPerf.h"
	long getTime(){
		return getNanoSec();
	}
#endif

long sum(int iterations);
long multi(int iterations);
void fillMatriz(int n, int m, int **matriz);
long floatVsDouble(int iterations);
long zeroVsOne(int iterations);
long forVar(int iterations);
long forReverse(int iterations);
long saveElement();

#define ARQUIVO1 "soma.txt"
#define ARQUIVO2 "multiplicacao.txt"
#define ARQUIVO3 "ponto_flutuante.txt"
#define ARQUIVO4 "multiplica_por1.txt"
#define ARQUIVO5 "outside.txt"
#define ARQUIVO6 "reverse.txt"
#define ARQUIVO7 "salvar.txt"





int main(){
	srand(time(NULL));
	FILE *arquivo = fopen(ARQUIVO1, "a");
	long s=getTime();

	double sumTest=0;
	for(int i=0;i<NOFTESTS;i++)
		sumTest+=sum(ITERATIONS);
	sumTest/=NOFTESTS;
	if(sumTest>0){
		//printf("A=A+B mais rapido que A+=B, diff=%lf\n",sumTest);
		fputs("a\n", arquivo);
	}else{
		//printf("A+=B mais rapido que A=A+B, diff=%lf\n",sumTest); MUITO MAIS RAPIDO
		fputs("b\n", arquivo);
	}
	fclose(arquivo);

	double multiTest=0;
	arquivo = fopen(ARQUIVO2, "a");
	for(int i=0;i<NOFTESTS;i++)
		multiTest+=multi(ITERATIONS);
	multiTest/=NOFTESTS;
	if(multiTest>0){
		//printf("A=A*B mais rapido que A*=B, diff=%lf\n",multiTest);
		fputs("a\n", arquivo);
	}else{
		//printf("A*=B mais rapido que A=A*B, diff=%lf\n",multiTest); MAIS RAPIDO
		fputs("b\n", arquivo);
	}
	fclose(arquivo);

	double floatTest=0;
	arquivo = fopen(ARQUIVO3, "a");
	for(int i=0;i<NOFTESTS;i++)
		floatTest+=floatVsDouble(ITERATIONS);
	floatTest/=NOFTESTS;
	if(floatTest>0){
		//printf("Double mais rapido que float, diff=%lf\n",floatTest);
		fputs("a\n", arquivo);
	}else{
		//printf("Float mais rapido que double, diff=%lf\n",floatTest); MAIS RAPIDO
		fputs("b\n", arquivo);
	}
	fclose(arquivo);

	double zoTest=0;
	arquivo = fopen(ARQUIVO4, "a");
	for(int i=0;i<NOFTESTS;i++)
		zoTest+=zeroVsOne(ITERATIONS);
	zoTest/=NOFTESTS;
	if(zoTest>0){
		//printf("1*=a mais rapido que 0+=a, diff=%lf\n",zoTest); MUITO MAIS RAPIDO
		fputs("a\n", arquivo);
	}else{
		//printf("0+=a mais rapido que 1*=a, diff=%lf\n",zoTest);
		fputs("b\n", arquivo);
	}
	fclose(arquivo);

	double forVTest=0;
	arquivo = fopen(ARQUIVO5, "a");
	for(int i=0;i<NOFTESTS;i++)
		forVTest+=forVar(ITERATIONS);
	forVTest/=NOFTESTS;
	if(forVTest>0){
		//printf("Outside mais rapido que inside, diff=%lf\n",forVTest); MUITO MAIS RAPIDO
		fputs("a\n", arquivo);
	}else{
		//printf("Inside mais rapido que outside, diff=%lf\n",forVTest);
		fputs("b\n", arquivo);
	}
	fclose(arquivo);

	double forRTest=0;
	arquivo = fopen(ARQUIVO6, "a");
	for(int i=0;i<NOFTESTS;i++)
		forRTest+=forReverse(ITERATIONS);
	forRTest/=NOFTESTS;
	if(forRTest>0){
		//printf("Reverse mais rapido que normal, diff=%lf\n",forRTest); MUITO MAIS RAPIDO
		fputs("a\n", arquivo);
	}else{
		//printf("Normal mais rapido que reverse, diff=%lf\n",forRTest);
		fputs("b\n", arquivo);
	}
	fclose(arquivo);

	double saveElementTest=0;
	arquivo = fopen(ARQUIVO7, "a");
	for(int i=0;i<NOFTESTS;i++)
		saveElementTest+=saveElement();
	saveElementTest/=NOFTESTS;
	if(saveElementTest>0){
		//printf("Acessar diretamente mais rapido que salvar, diff=%lf\n",saveElementTest);
		fputs("a\n", arquivo);
	}else{
		//printf("salvar mais rapido que acessar diretamente, diff=%lf\n",saveElementTest); MUITO MAIS RAPIDO
		fputs("b\n", arquivo);
	}
	fclose(arquivo);

	long e=getTime();
	int id =0;
	char aux;
	arquivo = fopen(ARQUIVO1, "r");
	while(fscanf(arquivo,"%c\n",&aux)!=EOF){
		printf("Id: %i\n",++id);
	}
	printf("\nTotal Time: %ld\n ",e-s);

	return 0;
}

long sum(int iterations){
	int a=rand() % 10000;
	int bkp=a;
	long plusEqual,equalVarPlus,s,e;
	s=getTime();
	for(int i=0;i<iterations;i++){
		a+=666;
	}
	e=getTime();
	plusEqual=e-s;
	a=bkp;
	s=getTime();
	for(int i=0;i<iterations;i++){
		a=a+666;
	}
	e=getTime();
	equalVarPlus=e-s;
	return equalVarPlus-plusEqual;
}

long multi(int iterations){
	int a=rand() % 10000;
	int bkp=a;
	long multiEqual,equalVarMulti,s,e;
	s=getTime();
	for(int i=0;i<iterations;i++){
		a*=666;
	}
	e=getTime();
	multiEqual=e-s;
	a=bkp;
	s=getTime();
	for(int i=0;i<iterations;i++){
		a=a*666;
	}
	e=getTime();
	equalVarMulti=e-s;
	return equalVarMulti-multiEqual;
}

long floatVsDouble(int iterations){
	double d=(rand() % 10000)/1000;
	float f=(float)d;
	long floaT,doublE,s,e;
	s=getTime();
	for(int i=0;i<iterations;i++){
		f+=666;
		f/=2;
	}
	e=getTime();
	floaT=e-s;
	s=getTime();
	for(int i=0;i<iterations;i++){
		d+=666;
		d/=2;
	}
	e=getTime();
	doublE=e-s;
	return doublE-floaT;
}

long zeroVsOne(int iterations){
	int a=rand()%666;
	int z,o;
	long zero,one,s,e;
	s=getTime();
	for(int i=0;i<iterations;i++){
		z=0;
		z+=a;
	}
	e=getTime();
	zero=e-s;
	s=getTime();
	for(int i=0;i<iterations;i++){
		o=0;
		o*=a;
	}
	e=getTime();
	one=e-s;
	return one-zero;
}

long forVar(int iterations){
	iterations/=100;
	if(iterations<100)iterations=100;
	int a=24,b=66,c;
	int j,k;
	long inside,outside,s,e;
	s=getTime();
	for(int h=0;h<iterations;h++){
		for(int i=0;i<iterations;i++)
			c=a+b;
	}
	e=getTime();
	inside=e-s;
	s=getTime();
	for(j=0;j<iterations;j++){
		for(k=0;k<iterations;k++)
			c=a+b;
	}
	e=getTime();
	outside=e-s;
	return outside-inside;
}

long forReverse(int iterations){
	iterations/=100;
	if(iterations<100)iterations=100;
	int a=24,b=66,c;
	long normal,reverse,s,e;
	s=getTime();
	for(int h=0;h<iterations;h++){
		for(int i=0;i<iterations;i++)
			c=a+b;
	}
	e=getTime();
	normal=e-s;
	s=getTime();
	for(int h=iterations-1;h>=0;h--){
		for(int i=iterations-1;i>=0;i--)
			c=a+b;
	}
	e=getTime();
	reverse=e-s;
	return reverse-normal;
}


long saveElement(){
	int n=10,m=10;
	int** A = AlocMat(n,m); //int A[n][m];
	int** B = AlocMat(m,n);//int B[m][n];
	int** S = AlocMat(n,n);//int S[n][n];
	fillMatriz(n,m,A);
	fillMatriz(m,n,B);
	long save,dontSave,s,e;
	s=getTime();
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			for(int k=0;k<n;k++){
				int a=A[i][k];
				int b=B[k][j];
				S[i][j]=S[i][j]+a*b;				
		}	
	e=getTime();
	save=e-s;
	s=getTime();
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			for(int k=0;k<n;k++)
				S[i][j]=S[i][j]+A[i][k]*B[k][j];					
	e=getTime();
	dontSave=e-s;
	FreeMat(n, m, A);
	FreeMat(m, n, B);
	FreeMat(n, n, S);
	return dontSave-save;
}