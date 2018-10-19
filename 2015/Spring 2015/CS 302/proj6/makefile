all: p6.out

p6.out:	main.o binarySearchTree.o
	g++ -o p6.out main.o binarySearchTree.o -std=c++0x

main.o:	main.cpp
	g++ -c main.cpp -std=c++0x

binarySearchTree.o:	binarySearchTree.cpp
			g++ -c binarySearchTree.cpp -std=c++0x

clean:
		rm -rf *.o *.gch p6.out
