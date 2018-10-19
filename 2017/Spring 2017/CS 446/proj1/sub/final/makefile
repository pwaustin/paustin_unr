all: Sim01

Sim01: main.o classes.o
	g++ -o Sim01 main.o classes.o -std=c++0x

main.o: main.cpp
	g++ -c main.cpp -std=c++0x

classes.o:	classes.cpp
		g++ -c classes.cpp -std=c++0x

clean:
	rm -rf *.o *.gch *.out 
