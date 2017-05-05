SOURCE = Calculo_PI_em_serial
all: compile link run destroy
compile:
	gcc $(SOURCE).c -fopenmp -c 

compilepg:
	gcc $(SOURCE).c -fopenmp -o $(SOURCE) -pg 

link:
	gcc $(SOURCE).o -o $(SOURCE)

run:
	./$(SOURCE)

destroy:
	rm -f $(SOURCE).o $(SOURCE)

gprof: compilapg roda
	gprof Calculo_PI_em_paralelo_Usando_Reduction gmon.out > output.txt
