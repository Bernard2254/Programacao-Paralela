#ifndef DLAITONMULTIPLIER_H
#define DLAITONMULTIPLIER_H

long Implicito(int **A, int **B, int **S, int x, int y, int t){
	long int init, end;
	init = getTime();
	for(int i=0;i<x;i++)
			for(int j=0;j<y;j++)
				for(int k=0;k<t;k++){
					S[i][j]=S[i][j]+A[i][k]*B[k][j];				
				}
	end = getTime();
	return end-init;
}

long Explicito(int **A, int **BT, int **S, int x, int y, int t){
	long int init, end;
	init = getTime();
	for(int i=0;i<x;i++)
		for(int j=0;j<y;j++)
			for(int k=0;k<t;k++){
				S[i][j]=S[i][j]+A[i][k]*BT[j][k];				
			}
	end = getTime();
	return end-init;
}

long Prevendo(int **A, int **B, int ***S, int x, int y, int t){
	long int init, end;
	init = getTime();
	for(int i=0;i<x;i++)
		for(int j=0;j<y;j++){
			double a=A[i][j],b=B[i][j];
			for(int k=0;k<t;k++){
				if(S[i][k][j]!=0){//se tiver zero na matriz pode dar problema, para resolver podemos tentar diferenciar +0 de -0 usando bitsignificativo ou definir uma matriz de bool para verificar se foi o primeiro acesso
					S[i][k][j]*=a;//segunda vez acessado
					S[i][k][t]+=S[i][k][j];//soma no valor final
				}else
					S[i][k][j]=a;//primeira vez acessado

				if(S[k][i][j]!=0){//se tiver zero na matriz pode dar problema, para resolver podemos tentar diferenciar +0 de -0 usando bitsignificativo ou definir uma matriz de bool para verificar se foi o primeiro acesso
					S[k][i][j]*=b;//segunda vez acessado
					S[k][i][t]+=S[k][i][j];//soma no valor final
				}else
					S[k][i][j]=b;//primeira vez acesado
			}
		}
	end = getTime();
	return end-init;
}

long Achatando(int **A, int **B, int ***S,int x, int y, int t){
	long int init, end;
	init = getTime();
	for(int i=0;i<x;i++)
		for(int j=0;j<y;j++){
			for(int k=0;k<t;k++){
					S[i][k][j]*=A[i][j];
					S[k][i][j]*=B[i][j];
			}
		}
	for(int i=0;i<x;i++)
	for(int j=0;j<y;j++){
		for(int k=1;k<t;k++){
				S[i][j][0]+=S[i][j][k];
				S[i][j][0]+=S[i][j][k];
		}
	}
	end = getTime();
	return end-init;
}	
#endif /* DLAITONMULTIPLIER_H */