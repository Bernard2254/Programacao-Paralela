all: make run

make:
	gcc speedTest.cpp -o speedTest

run: make
	./speedTest

clean:
	rm -rf speedTest

make++:
	g++ speedTest.cpp -o speedTest

run++: make++
	./speedTest

make++11:
	g++ speedTest.cpp -std=c++11 -o speedTest

run++11: make++11
	./speedTest