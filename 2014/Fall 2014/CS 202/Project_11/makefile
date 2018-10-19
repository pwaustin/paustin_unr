project11.out:	project11.o listA.o listN.o
		g++ -o project11.out project11.o listA.o listN.o

project11.o:	project11.cpp listN.h listA.h
		g++ -c project11.cpp

listN.o:	listN.cpp listN.h
		g++ -c listN.cpp

listA.o:	listA.cpp listA.h
		g++ -c listA.cpp

clean:
		rm -rf *.o project11.out
