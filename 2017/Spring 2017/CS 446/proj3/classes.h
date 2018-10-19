/** CS 446 Project 3 - supporting data structures, class specification
@file classes.h
@author Patrick Austin
@date 3/8/2017 */

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
		char getCode() const;
		string getDescriptor() const;
		int getCycles() const;
		
};


/**

ProcessControlBlock class: a glorified int. Used in sim operations to track the state of the simulated processor, with 5 possibile states:
0 to denote start state, 1 to denote ready state, 2 to denote running state, 3 to denote waiting state, 4 to denote exit state.

*/

class ProcessControlBlock {

	private:

		int state;	//convention: 0 = start, 1 = ready, 2 = running, 3 = waiting, 4 = exit

	public:

		void setState (int);
		int getState() const;

};

/*

Data class: contains config and metafile data for one complete readin. Class constructor handles all file readin during object creation, and
requires the location of a config file as a parameter. Constructor will throw an exception if readin fails. If readin succeeds, the eventSequence 
vector will contain at least one event from the metadata file. Read in data can then be simulated via simulate method.

@exception: class constructor throws with error message in case of invalid file readin

*/

class Data {

	private:

		//config file data

		int versionNumber;
		string inputPath;
		int logValue;			//convention: 0 is log to monitor, 1 is log to file, 2 is log to both
		string logPath;
		int processorCycleTime;
		int monitorDisplayTime;
		int hardDriveCycleTime;
		int printerCycleTime;
		int keyboardCycleTime;
		int memoryCycleTime;
		int mouseCycleTime;
		int speakerCycleTime;

		int printerQuantity;		//new values for resource control and memory alloc in version 3 (convention: memory sizes in kbytes)
		int hardDriveQuantity;
		int systemMemoryQuantity;
		int systemMemoryBlockSize;

		//input file data: a vector of events

		vector<Event> eventSequence;

	protected:

		//helper functions

		void readConfigFile (char* targetPath);
		void readInputFile ();

		void simToMonitor () const;			//new in project 2
		void simToFile () const;

		unsigned int simMemory (unsigned int) const;	//new in project 3

	public:

		//class constructor - conducts readin from datafiles

		Data( char* configPath );

		//public method: simulate on the read in data

		void simulate() const;

};
