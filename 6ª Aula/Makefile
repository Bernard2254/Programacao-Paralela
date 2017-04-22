SOURCE = vector_addition_blocks

all: compile run destroy

compile:
	nvcc $(SOURCE).cu -o $(SOURCE)
run:
	./$(SOURCE)
destroy:
	rm -rf ./$(SOURCE)
