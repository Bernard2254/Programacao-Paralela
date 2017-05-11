SOURCE = matrix_multiplier_cuda
all: compile link run destroy

compile:
	nvcc $(SOURCE).cu -c
link:
	nvcc $(SOURCE).o -o $(SOURCE)
run:
	./$(SOURCE)
destroy:
	rm -rf ./$(SOURCE) $(SOURCE).o