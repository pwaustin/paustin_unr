all: p5.out

p5.out:	main.o node.o queue.o priorityQueue.o event.o stats.o simA.o simN.o
	g++ -o p5.out main.o node.o queue.o priorityQueue.o event.o stats.o simA.o simN.o -std=c++0x

simA.o:	simA.cpp 
	g++ -c simA.cpp -std=c++0x

simN.o:	simN.cpp
	g++ -c simN.cpp -std=c++0x

node.o:	node.cpp 
	g++ -c node.cpp -std=c++0x

queue.o:	queue.cpp 
		g++ -c queue.cpp -std=c++0x

priorityQueue.o:	priorityQueue.cpp 
			g++ -c priorityQueue.cpp -std=c++0x

event.o:	event.cpp 
		g++ -c event.cpp -std=c++0x

stats.o:	stats.cpp 
		g++ -c stats.cpp -std=c++0x

main.o:	main.cpp 
	g++ -c main.cpp -std=c++0x

clean:
		rm -rf *.o p5.out
