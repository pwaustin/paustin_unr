project8.out:	project8.o scat.o strings.o
		g++ -o project8.out project8.o scat.o strings.o

project6.o:	project8.cpp my_scat.h my_strings.h
		g++ -c project8.cpp

scat.o:		scat.cpp my_scat.h
		g++ -c scat.cpp

strings.o:	strings.cpp my_strings.h
		g++ -c strings.cpp

clean:
		rm -rf *.o project8.out
