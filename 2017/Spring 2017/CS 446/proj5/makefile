all: Sim05

Sim05: main.o classes.o
	g++ -pthread -o Sim05 main.o classes.o -std=c++0x

main.o: main.cpp
	g++ -c main.cpp -std=c++0x

classes.o:	classes.cpp
		g++ -c classes.cpp -std=c++0x

clean:
	rm -rf *.o *.gch *.out 
