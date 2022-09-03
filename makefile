clear: compile
	rm *.o

compile: object
	g++ -o main *.o
object:
	g++ -c main.cpp implementation/*.cpp
