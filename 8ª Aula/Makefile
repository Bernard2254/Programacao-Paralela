SOURCE = gpu_matrix_multiplier

all: compile link run destroy

compile: 
	nvcc $(SOURCE).cu -c
link:
	nvcc$(SOURCE).cu -o $(SOURCE)
run:
	./$(SOURCE)
destroy:
	rm -rf ./$(SOURCE) $(SOURCE).o