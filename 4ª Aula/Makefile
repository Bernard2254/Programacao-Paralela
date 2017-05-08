source=Calculo_PI_em_paralelo_Usando_Reduction
all: compile link run destroy
compile:
	gcc $(source).c -fopenmp -c 

compilepg:
	gcc $(source).c -fopenmp -o $(source) -pg 

link:
	gcc $(source).o -fopenmp -o $(source)

run:
	./$(source)

destroy:
	rm -f $(source).o $(source)

gprof: compilapg roda
	gprof Calculo_PI_em_paralelo_Usando_Reduction gmon.out > output.txt
