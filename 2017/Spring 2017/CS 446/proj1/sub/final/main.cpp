/** CS 446 Project 1 - main program
@file main.cpp
@author Patrick Austin
@date 1/27/2017 */

#include "classes.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <exception>
using namespace std;

int main( int argc, char* argv[])
{

cout << "CS 446 Project 1: Patrick Austin" << endl << endl;

//use command line arguments to initialize ConfigData objects

	if (argc == 1)	//if no arguments, print an error and exit
		{
	
		cout << "ERROR: At least one config file location expected in command line. Exiting program." << endl;
		return 0;

		}

	//intialize a vector of ConfigData objects, one for each command line argument

	vector<Data> dataVector;

	for ( int i = 1; i < argc; i++ )
		{

		try			//try to construct each configVector object
			{
			dataVector.push_back( Data( argv[i] ) );
			}
		catch (const char* msg)	//if construction fails, print error to console and terminate
			{
			cerr << msg << endl;
			return 0;
			}
		}

//for each ConfigData object, produce an output


	for ( int i = 0; i < dataVector.size(); i++ )
		{

		dataVector[i].output();

		}

//exit program

return 0;

}
