#include <stdio.h>

__global__ void mykernel(void){
}

int main(void){
	mykernel<<<1,1>>>();
	printf("Olá mundo\n");
	return 0;
}
