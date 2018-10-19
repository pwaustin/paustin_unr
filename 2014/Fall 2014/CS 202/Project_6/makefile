project6.out:	project6.o scat.o strings.o
		g++ -o project6.out project6.o scat.o strings.o

project6.o:	project6.cpp my_scat.h my_strings.h
		g++ -c project6.cpp

scat.o:		scat.cpp my_scat.h
		g++ -c scat.cpp

strings.o:	strings.cpp my_strings.h
		g++ -c strings.cpp

clean:
		rm -rf *.o project6.out
