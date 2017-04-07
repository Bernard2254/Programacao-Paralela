source=Calculo_PI_em_paralelo_Usando_Reduction
all: compila roda
compila:
	gcc $(source).c -fopenmp -o $(source)

compilapg:
	gcc $(source).c -fopenmp -o $(source) -pg 

roda:
	./$(source)

limpa:
	rm -f $(source).o $(source)

gprof: compilapg roda
	gprof Calculo_PI_em_paralelo_Usando_Reduction gmon.out > output.txt
