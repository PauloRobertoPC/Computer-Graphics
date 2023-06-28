clear: compile
	rm *.o

compile: object
	g++ main.cpp \
		implementation/utils/*.cpp \
		implementation/objects/*.cpp \
		implementation/lights/*.cpp \
		implementation/cameras/*.cpp \
		implementation/samplers/*.cpp \
		implementation/tracers/*.cpp \
		implementation/world/*.cpp \
		implementation/SDL/*.cpp \
		-std=c++20 -Ofast -flto -pipe -lSDL2 -o main
	
object:
	g++ -c -std=c++20 main.cpp \
		implementation/utils/*.cpp \
		implementation/objects/*.cpp \
		implementation/lights/*.cpp \
		implementation/cameras/*.cpp \
		implementation/samplers/*.cpp \
		implementation/tracers/*.cpp \
		implementation/world/*.cpp \
		implementation/SDL/*.cpp
