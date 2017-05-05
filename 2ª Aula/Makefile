SOURCE = Calculo_PI_em_paralelo_Resolvendo_False_Sharing_Usando_Sincronizacao
all: compile link run destroy
compile:
	gcc $(SOURCE).c -fopenmp -c 

compilepg:
	gcc $(SOURCE).c -fopenmp -o $(SOURCE) -pg 

link:
	gcc $(SOURCE).o -fopenmp -o $(SOURCE)

run:
	./$(SOURCE)

destroy:
	rm -f $(SOURCE).o $(SOURCE)

gprof: compilapg roda
	gprof Calculo_PI_em_paralelo_Usando_Reduction gmon.out > output.txt
