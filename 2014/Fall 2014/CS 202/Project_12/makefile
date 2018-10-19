p12.out:	project12.o classes.o strings.o
		g++ -o p12.out project12.o classes.o strings.o

project12.o:	project12.cpp classes.h strings.h
		g++ -c project12.cpp

classes.o:	classes.cpp classes.h
		g++ -c classes.cpp

strings.o:	strings.cpp strings.h
		g++ -c strings.cpp

clean:
		rm -rf *.o p12.out
