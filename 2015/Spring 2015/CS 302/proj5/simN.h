/** CS 302 Project 5 - node based simulation class specification
@file sim.h
@author Patrick Austin
@date 3/21/2015 */

#ifndef _SIMN_H
#define _SIMN_H
#include "stats.h"
#include "event.h"
#include "queues.h"
#include <iostream>
#include <ctime>
using namespace std;


/**

Sim class using node based implementation for queue and priority queue data structures.. Conducts 
bank queue simulation operations as specified in the prompt. Uses simulation
object data member to track statistics of the operation and conduct console and file output. User
can call three different simulations of specified size, with full step by step of each event printed
to console or summary statistic data. Pretty nifty. Supported sizes are 10, 1 000, 10 000, 100 000,
1 000 000.

*/

class simN {

	public:
	void simOne(const bool&, const int&);
	void simTwo(const bool&, const int&);
	void simThree(const bool&, const int&);
	void outputToConsole(const int&, const int&) const;
	void initCSVOutput();
	void outputToCSV(const int&, const int&);
	void endCSVOutput();
	void resetStats();

	private:
	void processArrivalSimOne
		( event, priorityQueueLinked<event>&, linkedQueue<event>&, int&, int&, bool& );
	void processDepartureSimOne
		( event, priorityQueueLinked<event>&, linkedQueue<event>&, int&, int&, bool& );
	void processArrivalSimTwo
		( event, priorityQueueLinked<event>&, linkedQueue<event>&, int&, int&, int, bool& );
	void processDepartureSimTwo
		( event, priorityQueueLinked<event>&, linkedQueue<event>&, int&, int&, int, bool& );
	void processArrivalSimThree
		( event, priorityQueueLinked<event>&, linkedQueue<event>&, int&, int&, int, bool& );
	void processDepartureSimThree
		( event, priorityQueueLinked<event>&, linkedQueue<event>&, int&, int&, int, bool& );
	void readin( priorityQueueLinked<event>&, const int& );

	bool noisy;
	statistics stats;
	
	};

#endif

