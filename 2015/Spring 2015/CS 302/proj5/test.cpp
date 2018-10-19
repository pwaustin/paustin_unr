#include "queues.h"
#include "event.h"
#include <iostream>
#include <fstream>
using namespace std;

int main()
	{

	int index;

	int count = 0;

	priorityQueueArray<event> testPQ(1000);

	ifstream fin;

	int newArrivalTime;

	int newTransactionTime;

	event newArrivalEvent;

	fin.open("1 000.txt");

	for ( index = 0; index < 1000; index++ )
		{

		//get arrival and transaction time

		fin >> newArrivalTime >> newTransactionTime;

		//make a new arrival event with these values

		newArrivalEvent.setInitialTime(newArrivalTime);

		newArrivalEvent.setTransactionDuration(newTransactionTime);

		newArrivalEvent.setArrivalOrDeparture('a');

		//enqueue the event

		testPQ.add(newArrivalEvent);

		}

	for ( index = 0; index < 1000; index++ )
		{

		cout << testPQ.peek().getInitialTime() << endl;

		testPQ.remove();

		}

	return 0;

	}
