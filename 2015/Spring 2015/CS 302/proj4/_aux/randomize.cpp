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

	//prompt for number of values

	cout << "Enter number of random values desired: ";

	cin >> size;

	//prompt for filename

	cout << "Enter desired filename, ie 'filename.txt': ";

	cin >> filename;

	//open file

	fout.open(filename);

	//print values

	for ( int index = 0; index < size; index++ )
		{

		fout << rand() % 1000000;

		fout << " ";

		}

	//close file

	fout.close();
	
	//end program

	delete [] filename;

	return 0;
	
	}
