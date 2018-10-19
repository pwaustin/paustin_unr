#include "event.h"
#include "queues.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
	{

	//seed random number generator and initialize variables

	srand( time(NULL) );

	ofstream fout;

	int size;

	char* filename = new char [100];

	int index;

	//prompt for number of values

	cout << "Enter number of random values desired: ";

	cin >> size;

	//make PQ and event

	priorityQueueArray<event> values(size);

	event value;

	//prompt for filename

	cout << "Enter desired filename, ie 'filename.txt': ";

	cin >> filename;

	//open file

	fout.open(filename);

	//sort values

	for ( index = 0; index < size; index++ )
		{

		value.setInitialTime( rand() % size );
		value.setTransactionDuration( ( rand() % 100) + 1 );

		values.add(value);

		}

	//print values

	for ( index = 0; index < size; index++ )
		{

		fout << values.peek().getInitialTime() << '\t';

		fout << values.peek().getTransactionDuration() << endl;

		values.remove();

		}

	//close file

	fout.close();
	
	//end program

	delete [] filename;

	return 0;
	
	}
