/** CS 302 Project 5 - event class header
@file event.h
@author Patrick Austin
@date 3/21/2015 */

#ifndef _EVENT_H
#define _EVENT_H

/**

Event class for use in queue and priority queue simulation operations.
Uses char 'a' in arrivalOrDeparture member to signify arrival and
char 'd' to signify departure. TransactionDuration member is used
in the departure event in sims with multiple lines/tellers to denote
the line/teller of origin for the event.
Uses overloaded comparison operators in order to ensure correct
sorted list operations.

*/

class event{

	public:
	event();
	void setInitialTime(const int&);
	int getInitialTime() const;
	void setArrivalOrDeparture(const char&);
	char getArrivalOrDeparture() const;
	void setTransactionDuration(const int&);
	int getTransactionDuration() const;
	bool operator< ( const event& ) const;
	bool operator<= ( const event& ) const;
	bool operator> ( const event& ) const;
	bool operator>= ( const event& ) const;
	bool operator== ( const event& ) const;
	bool operator!= ( const event& ) const;
	
	private:
	int initialTime;
	int transactionDuration;
	char arrivalOrDeparture;

	};

#endif
