SOURCE = vector_addition_blocks

all: compile link run destroy

compile:
	nvcc $(SOURCE).cu -c 
link:
	nvcc $(SOURCE).cu -o $(SOURCE)
run:
	./$(SOURCE)
destroy:
	rm -rf ./$(SOURCE) $(SOURCE).o
