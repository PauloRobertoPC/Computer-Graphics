clear: compile
	rm *.o

compile: object
	g++ main.cpp \
		implementation/utils/*.cpp \
		implementation/objects/*.cpp \
		implementation/lights/*.cpp \
		implementation/cameras/*.cpp \
		implementation/samplers/*.cpp \
		implementation/world/*.cpp \
		implementation/SDL/*.cpp \
		-Ofast -flto -pipe -lSDL2 -o main
	
object:
	g++ -c  main.cpp \
		implementation/utils/*.cpp \
		implementation/objects/*.cpp \
		implementation/lights/*.cpp \
		implementation/cameras/*.cpp \
		implementation/samplers/*.cpp \
		implementation/world/*.cpp \
		implementation/SDL/*.cpp
