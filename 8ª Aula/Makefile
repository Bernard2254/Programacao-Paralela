SOURCE = gpu_matrix_multiplier

all: compile run destroy

compile: 
	nvcc $(SOURCE).cu -o $(SOURCE)
run:
	./$(SOURCE)
destroy:
	rm -rf ./$(SOURCE)

