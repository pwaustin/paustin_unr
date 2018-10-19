all: p7.out

p7.out:	main.o intervalTree.o
	g++ -o p7.out main.o intervalTree.o -std=c++0x

main.o:	main.cpp
	g++ -c main.cpp -std=c++0x

intervalTree.o:		intervalTree.cpp
			g++ -c intervalTree.cpp -std=c++0x

clean:
		rm -rf *.o *.gch p7.out
