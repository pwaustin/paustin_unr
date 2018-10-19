/** CS 446 Project 1 - supporting data structures, class specification
@file classes.h
@author Patrick Austin
@date 1/27/2017 */

#include <string>
#include <vector>
using namespace std;

/**

Event class: contains data for one event read from the metadata file. a glorified struct

*/

class Event {

	private:

		char code;
		string descriptor;
		int cycles;

	public:
		Event( char targetCode, string targetDescriptor, int targetCycles );	//constructor for ease of creating Event objects
		char getCode() const;		//get functions to access private data members
		string getDescriptor() const;
		int getCycles() const;
		
};

/*

Data class: contains config and metafile data for one complete readin. Class constructor handles all file readin during object creation, and
requires the location of a config file as a parameter. Constructor will throw an exception if readin fails. If readin succeeds, the eventSequence 
vector will contain at least one event from the metadata file. Read in data can then be spat to console or log file via the public output method.

@exception: class constructor throws with error message in case of invalid file readin

*/

class Data {

	private:

		//config file data

		int versionNumber;
		string inputPath;
		int logValue;	//convention: 0 is log to monitor, 1 is log to file, 2 is log to both
		string logPath;
		int processorCycleTime;
		int monitorDisplayTime;
		int hardDriveCycleTime;
		int printerCycleTime;
		int keyboardCycleTime;
		int memoryCycleTime;
		int mouseCycleTime;
		int speakerCycleTime;

		//input file data: a vector of events

		vector<Event> eventSequence;

	protected:

		//helper functions

		void readConfigFile (char* targetPath);
		void readInputFile ();	

	public:

		//class constructor - conducts readin from datafiles

		Data( char* configPath );

		//public method: output read in data

		void output() const;

};
