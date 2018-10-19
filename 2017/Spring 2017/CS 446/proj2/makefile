all: Sim02

Sim02: main.o classes.o MemoryFunction.o
	g++ -pthread -o Sim02 main.o classes.o MemoryFunction.o -std=c++0x

main.o: main.cpp
	g++ -c main.cpp -std=c++0x

classes.o:	classes.cpp
		g++ -c classes.cpp -std=c++0x

MemoryFunction.o:	MemoryFunction.cpp
			g++ -c MemoryFunction.cpp -std=c++0x

clean:
	rm -rf *.o *.gch *.out 
