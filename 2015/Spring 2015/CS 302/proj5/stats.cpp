/** CS 302 Project 5 - statistics class implementation
@file stats.cpp
@author Patrick Austin
@date 3/21/2015 */

#include <iostream>
#include <fstream>
#include "stats.h"
using namespace std;

/** Statistics class constructor. Initializes statistics class values to 0.
@pre None.
@post Statistics object created with zeroed out initial values.
@return None. */

statistics::statistics()
	{

	//initialize values to 0

	simulationTime = 0;
	processingTime = 0;
	avgWaitTime = 0;
	maxWaitTime = 0;
	avgLineLength = 0;
	maxLineLength = 0;
	idleTime1 = 0;
	idleTime2 = 0;
	idleTime3 = 0;
	
}

/** Statistics class set for simulationTime. Sets simulationTime data member to specified value.
@pre None.
@post Specified value stored.
@param val The specified value.
@return None. */

void statistics::setSimulationTime(const double& val)
	{

	simulationTime = val;

	}

/** Statistics class get for simulationTime. Returns value stored in simulationTime data member.
@pre None.
@post Value returned.
@return double The value. */

double statistics::getSimulationTime() const
	{

	return simulationTime;

	}

/** Statistics class set for processingTime. Sets processingTime data member to specified value.
@pre None.
@post Specified value stored.
@param val The specified value.
@return None. */

void statistics::setProcessingTime(const int& val)
	{

	processingTime = val;

	}

/** Statistics class get for processingTime. Returns value stored in processingTime data member.
@pre None.
@post Value returned.
@return int The value. */

int statistics::getProcessingTime() const
	{

	return processingTime;

	}

/** Statistics class set for avgWaitTime. Sets avgWaitTime data member to specified value.
@pre None.
@post Specified value stored.
@param val The specified value.
@return None. */


void statistics::setAvgWaitTime(const double& val)
	{

	avgWaitTime = val;

	}

/** Statistics class get for avgWaitTime. Returns value stored in avgWaitTime data member.
@pre None.
@post Value returned.
@return double The value. */

double statistics::getAvgWaitTime() const
	{

	return avgWaitTime;

	}

/** Statistics class set for maxWaitTime. Sets maxWaitTime data member to specified value.
@pre None.
@post Specified value stored.
@param val The specified value.
@return None. */


void statistics::setMaxWaitTime(const int& val)
	{

	maxWaitTime = val;

	}

/** Statistics class get for maxWaitTime. Returns value stored in maxWaitTime data member.
@pre None.
@post Value returned.
@return int The value. */
	
int statistics::getMaxWaitTime() const
	{

	return maxWaitTime;

	}

/** Statistics class set for avgLineLength. Sets avgLineLength data member to specified value.
@pre None.
@post Specified value stored.
@param val The specified value.
@return None. */


void statistics::setAvgLineLength(const double& val)
	{

	avgLineLength = val;

	}

/** Statistics class get for avgLineLength Returns value stored in avgLineLength data member.
@pre None.
@post Value returned.
@return double The value. */

double statistics::getAvgLineLength() const
	{

	return avgLineLength;

	}

/** Statistics class set for maxLineLength. Sets maxLineLength data member to specified value.
@pre None.
@post Specified value stored.
@param val The specified value.
@return None. */


void statistics::setMaxLineLength(const int& val)
	{

	maxLineLength = val;

	}

/** Statistics class get for maxLineLength. Returns value stored in maxLineLength data member.
@pre None.
@post Value returned.
@return int The value. */

int statistics::getMaxLineLength() const
	{

	return maxLineLength;

	}

/** Statistics class set for idleTime values. Sets specified teller's idle time to specified value.
@pre None.
@post Specified value stored in specified variable.
@param teller The specified teller (1 2 or 3)
@param val The specified value.
@return None. */

void statistics::setIdleTime(const int& teller, const int& val)
	{

	if ( teller == 1 )
		idleTime1 = val;

	else if ( teller == 2 )
		idleTime2 = val;

	else if ( teller == 3 )
		idleTime3 = val;

	}

/** Statistics class get for idleTime values. Returns value stored in specified teller's idleTime
data member.
@pre None.
@post Value for specified teller returned.
@param teller The specified teller (1 2 or 3)
@return int The value. */

int statistics::getIdleTime(const int& teller) const
	{

	if ( teller == 1 )
		return idleTime1;

	else if ( teller == 2 )
		return idleTime2;

	else if ( teller == 3 )
		return idleTime3;

	}

/** Statistics class reset function. Resets all tracked statistics to 0.
@pre None.
@post Stored values reset to 0.
@return None. */

void statistics::reset()
	{

	//reset values to 0

	simulationTime = 0;
	processingTime = 0;
	avgWaitTime = 0;
	maxWaitTime = 0;
	avgLineLength = 0;
	maxLineLength = 0;
	idleTime1 = 0;
	idleTime2 = 0;
	idleTime3 = 0;

	}

/** Statistics class outputToConsole function. Spits processed statistics data to console.
Supported sizes noted below. 
@pre None.
@post Processed values printed to console; stored values unchanged.
@param simNum The type of simulation that was run. 1 denotes 1 teller 1 queue. 
2 denotes 3 tellers 3 queues. 3 denotes 3 tellers 1 queue.
@param size The size of the simulation that was run. Supported sizes for this function are 10,
1 000, 10 000, 100 000, 1 000 000. For size 10, data is printed assuming one iteration.
For the other sizes, data is printed assuming 10 iterations.
@return None. */


void statistics::outputToConsole(const int& simNum, const int& size) const
	{

	if ( size == 10 ) //if size = 10 or 1000000, only 1 iteration assumed
		{

		cout << "Simulation time (CPU time, in seconds): " << simulationTime  << endl;
		cout << "Processing time (in simulation time units): " << processingTime  << endl;
		cout << "Average wait time (per customer): " << ( avgWaitTime ) / size << endl;
		cout << "Maximum wait time: " << maxWaitTime << endl;
		cout << "Average line length (for total simulation time): ";

		if ( simNum == 1 || simNum == 3 )
			cout << ( (avgLineLength ) / ( processingTime ) ) << endl;

		else
			cout << ( (avgLineLength ) / ( processingTime ) ) / 3 << endl;

		cout << "Maximum line length: " << maxLineLength << endl;

		if ( simNum == 1 )
			{
	
			cout << "Teller idle time: " << idleTime1 << endl << endl;

			}

		else if ( simNum == 2 || simNum == 3 )
			{
	
			cout << "Teller 1 idle time: " << idleTime1 << endl;
			cout << "Teller 2 idle time: " << idleTime2 << endl;
			cout << "Teller 3 idle time: " << idleTime3 << endl << endl;

			}

		}

	else	//for other sizes, 10 iterations assumed
		{

		cout << "Simulation time (CPU time, in seconds): " << simulationTime / 10  << endl;
		cout << "Processing time (in simulation time units): " << processingTime / 10 << endl;
		cout << "Average wait time (per customer): " << ( ( avgWaitTime ) / size ) / 10 << endl;
		cout << "Maximum wait time: " << maxWaitTime << endl;
		cout << "Average line length (for total simulation time): ";

		if ( simNum == 1 || simNum == 3 )
			cout << ( (avgLineLength ) / ( processingTime ) ) / 10 << endl;

		else
			cout << ( (avgLineLength ) / ( processingTime ) ) / 10 / 3 << endl;

		cout << "Maximum line length: " << maxLineLength << endl;

		if ( simNum == 1 )
			{
	
			cout << "Teller idle time: " << idleTime1 / 10 << endl << endl;

			}

		else if ( simNum == 2 || simNum == 3)
			{
	
			cout << "Teller 1 idle time: " << idleTime1 / 10 << endl;
			cout << "Teller 2 idle time: " << idleTime2 / 10 << endl;
			cout << "Teller 3 idle time: " << idleTime3 / 10 << endl << endl;

			}

		}

	}

/** Statistics class initCSVOutput function. Opens output file (output.csv) for subsequent functions
and prints a header row to the file.
@pre None.
@post Fstream to output.csv opened, header row printed in output.csv
@param dataStructureType The type of data structure used in the simulation, either 'a' 
to signify array based or 'n' to signify node based.
@return None. */

void statistics::initCSVOutput()
	{

	//open the output datafile

	fout.open( "output.csv", ofstream::out | ofstream::app );

	//print the header row for the output

		fout << "Sim Type,";
		fout << "Sim Data Structure,";
		fout << "Sim Size,";
		fout << "Iterations,";
		fout << "Sim Time,";
		fout << "Processing Time,";
		fout << "Avg Wait Time,";
		fout << "Max Wait Time,";
		fout << "Avg Line Length,";
		fout << "Max Line Length,";
		fout << "Teller 1 Idle Time,";
		fout << "Teller 2 Idle Time,";
		fout << "Teller 3 Idle Time," << endl;

	}

/** Statistics class outputToCSV function. Spits processed statistics data to output.csv.
Supported sizes noted below. 
@pre function initCSVOutput must have been run before this one in order to open the fstream.
@post Processed values printed to output.csv, stored values unchanged.
@param simType The type of simulation, either 'a' to signify array based or 'n' to signify node based.
@param simNum The type of simulation that was run. 1 denotes 1 teller 1 queue. 
2 denotes 3 tellers 3 queues. 3 denotes 3 tellers 1 queue.
@param size The size of the simulation that was run. Supported sizes for this function are 1 000, 
10 000, 100 000, 1 000 000. For size 1 000 000, data is printed assuming one iteration.
For the other sizes, data is printed assuming 10 iterations.
@return None. */

void statistics::outputToCSV(const char& simType, const int& simNum, const int& size)
	{

	//print the data for this run

		if ( simNum == 1 )
			fout << "1 Teller/1 Queue,";

		else if ( simNum == 2 )
			fout << "3 Teller/3 Queue,";

		else
			fout << "3 Teller/1 Queue,";

		if ( simType == 'a' )
			fout << "Array Based,";

		else
			fout << "Node Based,";

		fout << size << ",";

		fout << "10,";
		fout << simulationTime / 10 << ",";
		fout << processingTime / 10 << ",";
		fout << ( (avgWaitTime) / size ) / 10 << ",";
		fout << maxWaitTime << ",";

		if ( simNum == 1 || simNum == 3 )
			fout << ( (avgLineLength ) / ( processingTime ) ) / 10 << ",";

		else
			fout << ( (avgLineLength ) / ( processingTime ) ) / 10 / 3 << ",";

		fout << maxLineLength << ",";

		if ( simNum == 1 )
			{
	
			fout << idleTime1 / 10 << "," << endl;

			}

		else if ( simNum == 2 || simNum == 3)
			{
	
			fout << idleTime1 / 10 << ",";
			fout << idleTime2 / 10 << ",";
			fout << idleTime3 / 10 << "," << endl;

			}

	}

/** Statistics class endCSVOutput function. Closes output.csv file, ending file output operations.
@pre None.
@post Fstream to output.csv closed.
@return None. */

void statistics::endCSVOutput()
	{

	//close output datafile

	fout.close();

	}

//end stats.h implementation
