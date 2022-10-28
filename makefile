clear: compile
	rm *.o

compile: object
	g++ -lSDL2 -o  main *.o
	
object:
	g++ -c  main.cpp implementation/*.cpp 
