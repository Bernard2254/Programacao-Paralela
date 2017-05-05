SOURCE = intro
all: compile link run destroy
compile:
	nvcc $(SOURCE).c -c 

compilepg:
	nvcc $(SOURCE).c -o $(SOURCE) -pg 

link:
	nvcc $(SOURCE).o -o $(SOURCE)

run:
	./$(SOURCE)

destroy:
	rm -f $(SOURCE).o $(SOURCE)

gprof: compilapg roda
	gprof Calculo_PI_em_paralelo_Usando_Reduction gmon.out > output.txt
