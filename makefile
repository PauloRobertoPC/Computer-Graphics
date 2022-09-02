execute: compile
	./main

compile: object
	g++ -std=c++17 main.cpp -o main

object:
