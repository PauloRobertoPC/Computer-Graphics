clear: compile
	rm *.o

compile: object
	g++ main.cpp implementation/*.cpp -Ofast -flto -pipe -lSDL2 -o main 
	
object:
	g++ -c  main.cpp implementation/*.cpp 
