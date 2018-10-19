/** CS 446 Project 3 - main program
@file main.cpp
@author Patrick Austin
@date 3/8/2017
@note: program tested on ECC ubuntu install, NOT on the nomachine */

#include "classes.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <exception>
using namespace std;

int main( int argc, char* argv[])
{

cout << "CS 446 Project 3: Patrick Austin" << endl << endl;

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

		try			//try to construct each dataVector object
			{
			dataVector.push_back( Data( argv[i] ) );
			}
		catch (const char* msg)	//if construction fails, print error to console and terminate
			{
			cerr << msg << endl;
			return 0;
			}
		}

//for each ConfigData object, run the simulation


	for ( int i = 0; i < dataVector.size(); i++ )
		{

		dataVector[i].simulate();

		}

//exit program

return 0;

}
