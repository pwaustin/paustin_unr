/** CS 302 Project 5 - array based simulation class implementation
@file simA.cpp
@author Patrick Austin
@date 3/21/2015 */

#include "simA.h"
#include "event.h"
#include "stats.h"
#include "queues.h"
using namespace std;

/** SimA class simOne function. Runs the 1 teller 1 queue simulation. Simulation conducted as per prompt.
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre Specified correctly formatted and named data files extant.
@post Simulation has been run. Statistics data is stored.
@param noisy Bool denoting whether the user would like console output going step by step through the simulation.
@param size The size of the simulation to be run, where size is the number of arrival events. Supported values are 10,
1 000, 10 000, 100 000, 1 000 000.
@return None. */

void simA::simOne(const bool& isNoisy, const int& size )
	{

	//set noisy bool to the value specified

	noisy = isNoisy;

	//create temp variables for processing and statistics

	int currentLineLength = 0;

	int currentTime = 1;

	int previousEventTime = 0;

	double cpuTime;

	event newEvent;

	//create empty queue

	arrayQueue<event> line(size*2);

	//create empty priority queue

	priorityQueueArray<event> events(size*2);

	//set teller availability to open

	bool tellerAvailable = true;

	//read event data from file into the priority queue

	readin(events, size);

	//start tracking CPU time of simulation

	clock_t start = clock();

	//process events until the priority queue is empty

	while ( !events.isEmpty() )
		{

		//get the top event

		newEvent = events.peek();

		//update the current event time and the previous event time
		//update average line length and teller idle time during this period

		previousEventTime = currentTime;

		currentTime = newEvent.getInitialTime();

		stats.setAvgLineLength( stats.getAvgLineLength() + 
				( (currentTime - previousEventTime) * currentLineLength ) );

		if ( tellerAvailable )
			stats.setIdleTime( 1 , stats.getIdleTime(1) + (currentTime - previousEventTime) );

		//if arrival event, process it

		if ( newEvent.getArrivalOrDeparture() == 'a' )
			processArrivalSimOne
			( newEvent, events, line, currentTime, currentLineLength, tellerAvailable );
		
		//if departure event, process it

		else
			processDepartureSimOne
			( newEvent, events, line, currentTime, currentLineLength, tellerAvailable );

		}

	//finish tracking CPU time of simulation and add the value to the stats

	clock_t finish = clock();

	cpuTime = static_cast<double>( finish - start ) / CLOCKS_PER_SEC;

	//endl for spacing if noisy

	if ( noisy )
		cout << endl;

	//manage statistics

		//add simulation time to stats

		stats.setSimulationTime( cpuTime + stats.getSimulationTime() );

		//final value of current time is the total simulation time the simulation took, add the value to the stats

		stats.setProcessingTime( currentTime + stats.getProcessingTime() );

	}

/** processArrival function for sim one. Processes an arrival event that has been removed from the priority queue of events.
Tracks statistical data for the operation. Simulation conducted as per prompt.
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre Called by simOne function as described and implemented herein.
@post The arrival event has been handled according to the rules of the simulation.
@param newEvent The arrival event instigating this call.
@param events The priority queue of events used by the simulation.
@param line The queue representing the line for the teller in the simulation.
@param currentTime The "current time" of the simulation. Used for processing statistics about the simulation.
@param currentLineLength The current length of the line. Incremented or decremented by certain operations of the function as
dictated by the rules of the simulation.
@param tellerAvailable Bool denoting whether the teller is available. Flipped by certain operations of the function as
dictated by the rules of the simulation.
herein.
@return None.*/


void simA::processArrivalSimOne( event newEvent, priorityQueueArray<event>& events, arrayQueue<event>& line, 
			int& currentTime, int& currentLineLength, bool& tellerAvailable )
	{

	//create temp departure event

	event newDepartureEvent;

	//remove this event from the priority queue

	events.remove();

	//if the line is empty and the teller is avaliable, process the event. This person did not have to wait

	if ( tellerAvailable && line.isEmpty() )
		{

		newDepartureEvent.setInitialTime( currentTime + newEvent.getTransactionDuration() );

		newDepartureEvent.setArrivalOrDeparture('d');

		events.add(newDepartureEvent);

		//print diagnostic message if specified

		if ( noisy )
			cout << "T = " << currentTime << 
			": Customer enters empty line and is served, with transaction duration of " 
			<< newEvent.getTransactionDuration() << ", will be finished at " 
			<< newDepartureEvent.getInitialTime() << endl;

		//the teller is no longer available, flip the bool and add the time the teller was idle to the total idle time

		tellerAvailable = false;

		}

	//otherwise, put the arrival in the queue. track max and average line length using current line length

	else
		{

		line.enqueue(newEvent);

		currentLineLength++;


		//print diagnostic message if specified

		if ( noisy )
			cout << "T = " << currentTime << ": Customer with a transaction that will take " << newEvent.getTransactionDuration() 
			<< " enters line, now line length of " << currentLineLength << endl;

		if ( currentLineLength > stats.getMaxLineLength() )
			{

			stats.setMaxLineLength(currentLineLength);

			}

		}

	}

/** processDeparture function for sim one. Processes a departure event that has been removed from the priority queue of events.
Tracks statistical data for the operation. Simulation conducted as per prompt.
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre Called by simOne function as described and implemented herein.
@post The departure event has been handled according to the rules of the simulation.
@param newEvent The departure event instigating this call.
@param events The priority queue of events used by the simulation.
@param line The queue representing the line for the teller in the simulation.
@param currentTime The "current time" of the simulation. Used for processing statistics about the simulation.
@param currentLineLength The current length of the line. Incremented or decremented by certain operations of the function as
dictated by the rules of the simulation.
@param tellerAvailable Bool denoting whether the teller is available. Flipped by certain operations of the function as
dictated by the rules of the simulation.
herein.
@return None.*/

void simA::processDepartureSimOne( event newEvent, priorityQueueArray<event>& events, arrayQueue<event>& line, 
			int& currentTime, int& currentLineLength, bool& tellerAvailable )
	{

	//create temp current event

	event currentEvent;

	//create temp departure event	

	event newDepartureEvent;

	//remove this event from the priority queue

	events.remove();

	//process the next arrival event in the queue, if there is one

	if ( !line.isEmpty() )
		{

		//the teller takes the next customer. The length of the line goes down by one. 
		//this person had to wait- track average and max wait time

		currentEvent = line.peek();

		line.dequeue();

		currentLineLength--;

		if ( currentTime - currentEvent.getInitialTime() > stats.getMaxWaitTime() )
			stats.setMaxWaitTime( currentTime - currentEvent.getInitialTime() );
	
		stats.setAvgWaitTime( stats.getAvgWaitTime() + (currentTime - currentEvent.getInitialTime() ) );

		//create a corresponding departure event

		newDepartureEvent.setInitialTime( currentTime + currentEvent.getTransactionDuration() );

		newDepartureEvent.setArrivalOrDeparture('d');

		//print diagnostic message if specified

		if ( noisy )
			cout << "T = "<< currentTime << ": Customer exits line and is served, transaction takes " 
			<< currentEvent.getTransactionDuration() << ", will be finished at " <<
			newDepartureEvent.getInitialTime() << endl;

		events.add(newDepartureEvent);

		}

	//otherwise, the teller processed their only current customer and their line is now empty; set the teller to available

	else
		{

		//print diagnostic message if specified

		if ( noisy )
			cout << "T = " << newEvent.getInitialTime() << 
			": Customer is finished being served, line is now empty and teller available" << endl;

		tellerAvailable = true;

		}

	}

/** simTwo function. Runs the 3 teller 3 queue simulation. Simulation conducted as per prompt.
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre Specified correctly formatted and named data files extant.
@post Simulation has been run. Statistics data is stored in the statistics object.
@param noisy Bool denoting whether the user would like console output going step by step through the simulation.
@param size The size of the simulation to be run, where size is the number of arrival events. Supported values are 10,
1 000, 10 000, 100 000, 1 000 000.
@return None. */

void simA::simTwo(const bool& isNoisy, const int& size)
	{

	//set noisy bool to the value specified

	noisy = isNoisy;

	//create temp variables for processing and statistics

	int currentLineLength1 = 0;
	int currentLineLength2 = 0;
	int currentLineLength3 = 0;

	int previousEventTime = 0;

	double cpuTime;

	event newEvent;

	int currentTime = 1;

	//create three empty queues

	arrayQueue<event> line1(size*2);
	arrayQueue<event> line2(size*2);
	arrayQueue<event> line3(size*2);

	//create empty priority queue

	priorityQueueArray<event> events(size*2);

	//set teller availability to open

	bool tellerAvailable1 = true;
	bool tellerAvailable2 = true;
	bool tellerAvailable3 = true;

	//read event data from file into the priority queue

	readin(events, size);

	//start tracking CPU time of simulation

	clock_t start = clock();

	//process events until the priority queue is empty

	while ( !events.isEmpty() )
		{

		//get the top event

		newEvent = events.peek();

		//update the current event time and the previous event time
		//manage average line length (remember, there are three lines) and teller idle time

		previousEventTime = currentTime;

		currentTime = newEvent.getInitialTime();

		stats.setAvgLineLength
			( stats.getAvgLineLength() + ( (currentTime - previousEventTime) * currentLineLength1 ) );

		stats.setAvgLineLength
			( stats.getAvgLineLength() + ( (currentTime - previousEventTime) * currentLineLength2 ) );

		stats.setAvgLineLength
			( stats.getAvgLineLength() + ( (currentTime - previousEventTime) * currentLineLength3 ) );

		if ( tellerAvailable1 )
			stats.setIdleTime( 1 , stats.getIdleTime(1) + (currentTime - previousEventTime) );

		if ( tellerAvailable2 )
			stats.setIdleTime( 2 , stats.getIdleTime(2) + (currentTime - previousEventTime) );

		if ( tellerAvailable3 )
			stats.setIdleTime( 3 , stats.getIdleTime(3) + (currentTime - previousEventTime) );

		//determine which queue will handle the event

			//if departure event, use TransactionDuration value of newEvent 
			//to determine which teller and queue to update

			if ( newEvent.getArrivalOrDeparture() == 'd' )
				{

				if ( newEvent.getTransactionDuration() == 1 )
					processDepartureSimTwo
					( newEvent, events, line1, currentTime, currentLineLength1, 1, tellerAvailable1 );

				else if ( newEvent.getTransactionDuration() == 2 )
					processDepartureSimTwo
					( newEvent, events, line2, currentTime, currentLineLength2, 2, tellerAvailable2 );

				else if ( newEvent.getTransactionDuration() == 3 )
					processDepartureSimTwo
					( newEvent, events, line3, currentTime, currentLineLength3, 3, tellerAvailable3 );

				}

			//if arrival event and tellers are available, just go to that line (preferring 1 to 2 to 3)
			//otherwise, go to the shortest line, preferring 1 to 2 to 3 in cases of equal length

			else
				{

				if ( tellerAvailable1 )
					processArrivalSimTwo
					( newEvent, events, line1, currentTime, currentLineLength1, 1, tellerAvailable1 );

				else if ( tellerAvailable2 )
					processArrivalSimTwo
					( newEvent, events, line2, currentTime, currentLineLength2, 2, tellerAvailable2 );

				else if ( tellerAvailable3 )
					processArrivalSimTwo
					( newEvent, events, line3, currentTime, currentLineLength3, 3, tellerAvailable3 );

				else if ( (currentLineLength1 == currentLineLength2 && 
									currentLineLength2 == currentLineLength3) || 
					(currentLineLength1 <= currentLineLength2 && 
									currentLineLength1 <= currentLineLength3) )
					processArrivalSimTwo
					( newEvent, events, line1, currentTime, currentLineLength1, 1, tellerAvailable1 );

				else if ( currentLineLength2 < currentLineLength1 && 
									currentLineLength2 <= currentLineLength3 ) 

					processArrivalSimTwo
					( newEvent, events, line2, currentTime, currentLineLength2, 2, tellerAvailable2 );

				else
					processArrivalSimTwo
					( newEvent, events, line3, currentTime, currentLineLength3, 3, tellerAvailable3 );
				}

		}

	//finish tracking CPU time of simulation, add the value to the stats

	clock_t finish = clock();

	cpuTime = static_cast<double>( finish - start ) / CLOCKS_PER_SEC;

	//manage statistics

		//add simulation time to stats

		stats.setSimulationTime( cpuTime + stats.getSimulationTime() );

		//final value of current time is the total simulation time the simulation took, add the value to the stats

		stats.setProcessingTime( currentTime + stats.getProcessingTime() );

	}

/** processArrival function for sim two. Processes an arrival event that has been removed from the priority queue of events.
Tracks statistical data for the operation. Simulation conducted as per prompt.
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre Called by simTwo function as described and implemented herein.
@post The arrival event has been handled according to the rules of the simulation.
@param newEvent The arrival event instigating this call.
@param events The priority queue of events used by the simulation.
@param line The queue representing the line for the teller in the simulation. Which queue is called is determined by the
simTwo function when calling this function as per the rules of the simulation.
@param currentTime The "current time" of the simulation. Used for processing statistics about the simulation.
@param currentLineLength The current length of the line. Incremented or decremented by certain operations of the function as
dictated by the rules of the simulation. Which line length is manipulated is determined by the simTwo function when calling
this function as per the rules of the simulation.
@param tellerNum Int denoting which teller/queue is being referred to by this event.
@param tellerAvailable Bool denoting whether the teller is available. Flipped by certain operations of the function as
dictated by the rules of the simulation. Which bool is manipulated is determined by the simTwo function when calling this 
function as per the rules of the simulation.
@return None.*/

void simA::processArrivalSimTwo( event newEvent, priorityQueueArray<event>& events, arrayQueue<event>& line, int& currentTime, 
				int& currentLineLength, int tellerNum, bool& tellerAvailable )
	{

	//create temp departure event

	event newDepartureEvent;

	//remove this event from the priority queue

	events.remove();

	//if the line is empty and the teller is avaliable, process the event. This person did not have to wait

	if ( tellerAvailable && line.isEmpty() )
		{

		newDepartureEvent.setInitialTime( currentTime + newEvent.getTransactionDuration() );

		newDepartureEvent.setArrivalOrDeparture('d');

		//as said in documentation, this implementation will use transaction 
		//duration member of a departure event to denote which teller is being departed from

		newDepartureEvent.setTransactionDuration(tellerNum);

		events.add(newDepartureEvent);

		//print diagnostic message if specified

		if ( noisy )
			cout << "T = " << currentTime << ": Customer enters empty line " << tellerNum << 
			" and is served by teller " << tellerNum << ",  with transaction duration of " 
			<< newEvent.getTransactionDuration() << ", will be finished at " 
			<< newDepartureEvent.getInitialTime() << endl;

		//the teller is no longer available, flip the bool and add the time the teller was idle to the total idle time

		tellerAvailable = false;

		}

	//otherwise, put the arrival in the queue. track max and average line length using current line length

	else
		{

		line.enqueue(newEvent);

		currentLineLength++;

		//print diagnostic message if specified

		if ( noisy )
			cout << "T = " << currentTime << ": Customer with a transaction that will take " << newEvent.getTransactionDuration() 
			<< " enters line " << tellerNum << ", now line length of " << currentLineLength << endl;

		if ( currentLineLength > stats.getMaxLineLength() )
			{

			stats.setMaxLineLength(currentLineLength);

			}

		}

	}

/** processDeparture function for sim two. Processes a departure event that has been removed from the priority queue of events.
Tracks statistical data for the operation. Simulation conducted as per prompt.
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre Called by simTwo function as described and implemented herein.
@post The departure event has been handled according to the rules of the simulation.
@param noisy Bool denoting whether the user would like console output going step by step through the simulation.
@param newEvent The departure event instigating this call.
@param events The priority queue of events used by the simulation.
@param line The queue representing the line for the teller in the simulation. Which queue is called is determined by the
simTwo function when calling this function as per the rules of the simulation.
@param currentTime The "current time" of the simulation. Used for processing statistics about the simulation.
@param currentLineLength The current length of the line. Incremented or decremented by certain operations of the function as
dictated by the rules of the simulation. Which line length is manipulated is determined by the simTwo function when calling
this function as per the rules of the simulation.
@param tellerNum Int denoting which teller/queue is being referred to by this event.
@param tellerAvailable Bool denoting whether the teller is available. Flipped by certain operations of the function as
dictated by the rules of the simulation. Which bool is manipulated is determined by the simTwo function when calling this 
function as per the rules of the simulation.
@return None.*/

void simA::processDepartureSimTwo( event newEvent, priorityQueueArray<event>& events, arrayQueue<event>& line, 
				int& currentTime, int& currentLineLength, int tellerNum, bool& tellerAvailable )
	{

	//create temp current event

	event currentEvent;

	//create temp departure event	

	event newDepartureEvent;

	//remove this event from the priority queue

	events.remove();

	//process the next arrival event in the queue, if there is one

	if ( !line.isEmpty() )
		{

		//the teller takes the next customer. The length of the line goes down by one. 
		//This person had to wait- track average and max wait time

		currentEvent = line.peek();

		line.dequeue();

		currentLineLength--;

		if ( currentTime - currentEvent.getInitialTime() > stats.getMaxWaitTime() )
			stats.setMaxWaitTime( currentTime - currentEvent.getInitialTime() );
	
		stats.setAvgWaitTime( stats.getAvgWaitTime() + (currentTime - currentEvent.getInitialTime() ) );

		//create a corresponding departure event

		newDepartureEvent.setInitialTime( currentTime + currentEvent.getTransactionDuration() );

		newDepartureEvent.setArrivalOrDeparture('d');

		//as said in documentation, this implementation will use transaction 
		//duration member of a departure event to denote which teller is being departed from

		newDepartureEvent.setTransactionDuration(tellerNum);

		//print diagnostic message if specified

		if ( noisy )
			cout << "T = "<< currentTime << ": Customer exits line " << tellerNum << " and is served by teller "
			<< tellerNum << ", transaction takes " << currentEvent.getTransactionDuration() << 
			", will be finished at " << newDepartureEvent.getInitialTime() << endl;

		events.add(newDepartureEvent);

		}

	//otherwise, the teller processed their only current customer and their line is now empty; set the teller to available

	else
		{

		//print diagnostic message if specified

		if ( noisy )
			cout << "T = " << newEvent.getInitialTime() << ": Customer in line " << tellerNum << 
			" is finished being served by teller " << tellerNum << 
			", line is now empty and teller available" << endl;

		tellerAvailable = true;

		}
	}

/** simThree function. Runs the 3 teller 1 queue simulation. Simulation conducted as per prompt.
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre Specified correctly formatted and named data files extant.
@post Simulation has been run. Statistics data is stored in the statistics object.
@param noisy Bool denoting whether the user would like console output going step by step through the simulation.
@param size The size of the simulation to be run, where size is the number of arrival events. Supported values are 10,
1 000, 10 000, 100 000, 1 000 000.
@return None. */

void simA::simThree(const bool& isNoisy, const int& size)
	{

	//set noisy bool to the value specified

	noisy = isNoisy;

	//create temp variables for processing and statistics

	int currentLineLength = 0;

	int previousEventTime = 0;

	double cpuTime;

	event newEvent;

	int currentTime = 1;

	//create an empty queue

	arrayQueue<event> line(size*2);

	//create empty priority queue

	priorityQueueArray<event> events(size*2);

	//set teller availability to open

	bool tellerAvailable1 = true;
	bool tellerAvailable2 = true;
	bool tellerAvailable3 = true;

	//read event data from file into the priority queue

	readin(events, size);

	//start tracking CPU time of simulation

	clock_t start = clock();

	//process events until the priority queue is empty

	while ( !events.isEmpty() )
		{

		//get the top event

		newEvent = events.peek();

		//update the current event time and the previous event time - manage average line length and teller idle time

		previousEventTime = currentTime;

		currentTime = newEvent.getInitialTime();

		stats.setAvgLineLength
				( stats.getAvgLineLength() + ( (currentTime - previousEventTime) * currentLineLength ) );

		if ( tellerAvailable1 )
			stats.setIdleTime( 1 , stats.getIdleTime(1) + (currentTime - previousEventTime) );

		if ( tellerAvailable2 )
			stats.setIdleTime( 2 , stats.getIdleTime(2) + (currentTime - previousEventTime) );

		if ( tellerAvailable3 )
			stats.setIdleTime( 3 , stats.getIdleTime(3) + (currentTime - previousEventTime) );

		//determine which teller will handle the event

			//if departure event, use TransactionDuration value of newEvent to determine which teller is finished

			if ( newEvent.getArrivalOrDeparture() == 'd' )
				{

				if ( newEvent.getTransactionDuration() == 1 )
					processDepartureSimThree
					( newEvent, events, line, currentTime, currentLineLength, 1, tellerAvailable1 );

				else if ( newEvent.getTransactionDuration() == 2 )
					processDepartureSimThree
					( newEvent, events, line, currentTime, currentLineLength, 2, tellerAvailable2 );

				else if ( newEvent.getTransactionDuration() == 3 )
					processDepartureSimThree
					( newEvent, events, line, currentTime, currentLineLength, 3, tellerAvailable3 );

				}

			//if arrival event and empty line, send the customer to the first available teller 
			//( prefer 1 to 2 to 3 )
			//if arrival event, empty line, and all tellers occuped, it doesn't matter which teller you call with
			//if arrival event and customers already in line, it doesn't matter which teller you call with
			//I arbitrarily use teller 1 in situations where which teller the function is called with won't matter

			else if ( line.isEmpty() )
				{

				if ( tellerAvailable1 )
					processArrivalSimThree
					( newEvent, events, line, currentTime, currentLineLength, 1, tellerAvailable1 );
					

				else if ( tellerAvailable2 )
					processArrivalSimThree
					( newEvent, events, line, currentTime, currentLineLength, 2, tellerAvailable2 );

				else if ( tellerAvailable3 )
					processArrivalSimThree
					( newEvent, events, line, currentTime, currentLineLength, 3, tellerAvailable3 );

				else //1 chosen arbitrarily
					processArrivalSimThree
					( newEvent, events, line, currentTime, currentLineLength, 1, tellerAvailable1 );

				}

			else //1 chosen arbitrarily
				processArrivalSimThree
				( newEvent, events, line, currentTime, currentLineLength, 1, tellerAvailable1 );

		}

	//finish tracking CPU time of simulation, add the value to the stats

	clock_t finish = clock();

	cpuTime = static_cast<double>( finish - start ) / CLOCKS_PER_SEC;

	//endl for spacing if noisy

	if ( noisy )
		cout << endl;

	//manage statistics

		//add simulation time to stats

		stats.setSimulationTime( cpuTime + stats.getSimulationTime() );

		//final value of current time is the total simulation time the simulation took, add the value to the stats

		stats.setProcessingTime( currentTime + stats.getProcessingTime() );

	}

/** processArrival function for sim three. Processes an arrival event that has been removed from the priority queue of events.
Tracks statistical data for the operation. Simulation conducted as per prompt.
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre Called by simThree function as described and implemented herein.
@post The arrival event has been handled according to the rules of the simulation.
@param newEvent The arrival event instigating this call.
@param events The priority queue of events used by the simulation.
@param line The queue representing the line for the tellers in the simulation.
@param currentTime The "current time" of the simulation. Used for processing statistics about the simulation.
@param currentLineLength The current length of the line. Incremented or decremented by certain operations of the function as
dictated by the rules of the simulation. Which line length is manipulated is determined by the simThree function when calling
this function as per the rules of the simulation.
@param tellerNum Int denoting which teller is being referred to by this event.
@param tellerAvailable Bool denoting whether the teller is available. Flipped by certain operations of the function as
dictated by the rules of the simulation. Which bool is manipulated is determined by the simThree function when calling this 
function as per the rules of the simulation.
@return None.*/

void simA::processArrivalSimThree( event newEvent, priorityQueueArray<event>& events, arrayQueue<event>& line, 
				int& currentTime, int& currentLineLength, int tellerNum, bool& tellerAvailable )
	{

	//create temp departure event

	event newDepartureEvent;

	//remove this event from the priority queue

	events.remove();

	//if the line is empty and the teller is avaliable, process the event. This person did not have to wait

	if ( tellerAvailable && line.isEmpty() )
		{

		newDepartureEvent.setInitialTime( currentTime + newEvent.getTransactionDuration() );

		newDepartureEvent.setArrivalOrDeparture('d');

		//as said in documentation, this implementation will use transaction duration 
		//member of a departure event to denote which teller is being departed from

		newDepartureEvent.setTransactionDuration(tellerNum);

		events.add(newDepartureEvent);

		//print diagnostic message if specified

		if ( noisy )
			cout << "T = " << currentTime << ": Customer enters empty line and is served by teller " 
			<< tellerNum << ",  with transaction duration of " << newEvent.getTransactionDuration() << 
			", will be finished at " << newDepartureEvent.getInitialTime() << endl;

		//the teller is no longer available, flip the bool and add the time the teller was idle to the total idle time

		tellerAvailable = false;

		}

	//otherwise, put the arrival in the queue. track max and average line length using current line length

	else
		{

		line.enqueue(newEvent);

		currentLineLength++;

		//print diagnostic message if specified

		if ( noisy )
			cout << "T = " << currentTime << ": Customer with a transaction that will take " << newEvent.getTransactionDuration() 
			<< " enters line, now line length of " << currentLineLength << endl;

		if ( currentLineLength > stats.getMaxLineLength() )
			{

			stats.setMaxLineLength(currentLineLength);

			}

		}
	}

/** processDeparture function for sim three. Processes a departure event that has been removed from the priority queue of events.
Tracks statistical data for the operation. Simulation conducted as per prompt.
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre Called by simThree function as described and implemented herein.
@post The departure event has been handled according to the rules of the simulation.
@param newEvent The arrival event instigating this call.
@param events The priority queue of events used by the simulation.
@param line The queue representing the line for the tellers in the simulation.
@param currentTime The "current time" of the simulation. Used for processing statistics about the simulation.
@param currentLineLength The current length of the line. Incremented or decremented by certain operations of the function as
dictated by the rules of the simulation. Which line length is manipulated is determined by the simThree function when calling
this function as per the rules of the simulation.
@param tellerNum Int denoting which teller is being referred to by this event.
@param tellerAvailable Bool denoting whether the teller is available. Flipped by certain operations of the function as
dictated by the rules of the simulation. Which bool is manipulated is determined by the simThree function when calling this 
function as per the rules of the simulation.
@return None.*/

void simA::processDepartureSimThree( event newEvent, priorityQueueArray<event>& events, arrayQueue<event>& line, 
				int& currentTime, int& currentLineLength, int tellerNum, bool& tellerAvailable )
	{

	//create temp current event

	event currentEvent;

	//create temp departure event	

	event newDepartureEvent;

	//remove this event from the priority queue

	events.remove();

	//process the next arrival event in the queue, if there is one

	if ( !line.isEmpty() )
		{

		//the teller takes the next customer. The length of the line goes down by one. 
		//This person had to wait- track average and max wait time

		currentEvent = line.peek();

		line.dequeue();

		currentLineLength--;

		if ( currentTime - currentEvent.getInitialTime() > stats.getMaxWaitTime() )
			stats.setMaxWaitTime( currentTime - currentEvent.getInitialTime() );
	
		stats.setAvgWaitTime( stats.getAvgWaitTime() + (currentTime - currentEvent.getInitialTime() ) );

		//create a corresponding departure event

		newDepartureEvent.setInitialTime( currentTime + currentEvent.getTransactionDuration() );

		newDepartureEvent.setArrivalOrDeparture('d');

		//as said in documentation, this implementation will use transaction duration 
		//member of a departure event to denote which teller is being departed from

		newDepartureEvent.setTransactionDuration(tellerNum);

		//print diagnostic message if specified

		if ( noisy )
			cout << "T = "<< currentTime << ": Customer exits line and is served by teller " << tellerNum << 
			", transaction takes " << currentEvent.getTransactionDuration() << ", will be finished at " <<
			newDepartureEvent.getInitialTime() << endl;

		events.add(newDepartureEvent);

		}

	//otherwise, the teller processed their only current customer and their line is now empty; set the teller to available

	else
		{

		//print diagnostic message if specified

		if ( noisy )
			cout << "T = " << newEvent.getInitialTime() << ": Customer is finished being served by teller " 
			<< tellerNum << ", line is now empty and teller available" << endl;

		tellerAvailable = true;

		}

	}

/** readin function for the simulations described above. Called by simOne, simTwo, and simThree to load raw event data from
datafiles. 
@pre Datafiles must be formatted and named as specified. Supported datafiles are "1 000.txt", "10 000.txt", "100 000.txt",
"1 000 000.txt" (please note the spaces). Consult the format of the included datafiles and make sure they match if you intend
to provide your own. Thanks.
@post Data read in to the provided priorityQueue.
@param events The priorityQueue of events that will be used to run the simulation.
@param size The size of the simulation to be conducted. Supported sizes are 10(uses "100 000.txt") , 1 000, 10 000, 100 000, 
1 000 000.
@return None.*/

void simA::readin(priorityQueueArray<event>& events, const int& size)
	{

	ifstream fin;

	int newArrivalTime;

	int newTransactionTime;

	event newArrivalEvent;

	//open an appropriate datafile for the size provided

	if ( size == 1000 )
		fin.open("1 000.txt");

	else if ( size == 10000 )
		fin.open("10 000.txt");

	else if ( size == 10 || size == 100000 )
		fin.open("100 000.txt");

	else if ( size == 1000000 )
		fin.open("1 000 000.txt");

	for ( int index = 0; index < size; index++ )
		{

		//get arrival time and transaction

		fin >> newArrivalTime >> newTransactionTime;

		//make a new arrival event with these values

		newArrivalEvent.setInitialTime(newArrivalTime);

		newArrivalEvent.setTransactionDuration(newTransactionTime);

		newArrivalEvent.setArrivalOrDeparture('a');

		//enqueue the event

		events.add(newArrivalEvent);

		}

	}

/** Sim outputToConsole function. Calls the outputToConsole function of the sim
class's stats data member. Spits processed statistics data to console.
Supported sizes noted below. 
@pre None.
@post Processed values printed to console; stored values unchanged.
@param simNum The type of simulation that was run. 1 denotes 1 teller 1 queue. 
2 denotes 3 tellers 3 queues. 3 denotes 3 tellers 1 queue.
@param size The size of the simulation that was run. Supported sizes for this function are 10,
1 000, 10 000, 100 000, 1 000 000. For size 10 and 1 000 000, data is printed assuming one iteration.
For the other sizes, data is printed assuming 10 iterations.
@return None. */

void simA::outputToConsole(const int& simNum, const int& size) const
	{

	stats.outputToConsole(simNum, size);

	}

/** Sim initCSVOutput function. Calls the initCSVOutput function of the sim
class's stats data member. Opens output file (output.csv) for subsequent functions
and prints a header row to the file.
@pre None.
@post Fstream to output.csv opened, header row printed in output.csv
@return None. */

void simA::initCSVOutput()
	{

	stats.initCSVOutput();

	}

/** Sim outputToCSV function. Calls the initCSVOutput function of the sim
class's stats data member. Spits processed statistics data to output.csv.
Supported sizes noted below. 
@pre function initCSVOutput must have been run before this one in order to open the fstream.
@post Processed values printed to output.csv, stored values unchanged.
@param simNum The type of simulation that was run. 1 denotes 1 teller 1 queue. 
2 denotes 3 tellers 3 queues. 3 denotes 3 tellers 1 queue.
@param size The size of the simulation that was run. Supported sizes for this function are 1 000, 
10 000, 100 000, 1 000 000. For size 1 000 000, data is printed assuming one iteration.
For the other sizes, data is printed assuming 10 iterations.
@return None. */

void simA::outputToCSV(const int& simNum, const int& size)
	{

	stats.outputToCSV( 'a', simNum, size);

	}

/** Sim class endCSVOutput function. Calls the endCSVOutput function of the
sim class's stats data member. Closes output.csv file, ending file output operations.
@pre None.
@post Fstream to output.csv closed.
@return None. */

void simA::endCSVOutput()
	{

	stats.endCSVOutput();

	}

/** Sim class resetStats function. Calls the reset function of the sim class's stats
data member. Resets all tracked statistics to 0.
@pre None.
@post Stored values reset to 0.
@return None. */

void simA::resetStats()
	{

	stats.reset();

	}
