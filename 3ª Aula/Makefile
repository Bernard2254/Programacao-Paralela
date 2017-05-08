source=Multiplicacao_matriz_padding_variavel_local
all: compila link roda destroy
compila:
	gcc $(source).c -fopenmp -c 

link:
	gcc $(source).o -fopenmp -o $(source)

roda:
	./$(source)

destroy:
	rm -rf $(source) $(source).o