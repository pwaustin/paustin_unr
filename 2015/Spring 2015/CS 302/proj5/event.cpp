/** CS 302 Project 5 - event class implementation
@file event.cpp
@author Patrick Austin
@date 3/21/2015 */

#include "event.h"
using namespace std;

/** Event class constructor.
@pre None.
@post Event is created with default values of 0, 0, 'a'
@return None. */

event::event()
	{

	//set initial values

	initialTime = 0;
	transactionDuration = 0;
	arrivalOrDeparture = 'a';

	}

/** Event setInitialTime function. Set for initialTime data member.
@pre None.
@post initialTime data member holds val.
@param val The int value to which initialTime is to be set.
@return None. */

void event::setInitialTime(const int& val)
	{

	initialTime = val;

	}

/** Event getInitialTime function. Returns the initialTime data member of an event object.
@pre None.
@post Event object's initialTime returned; object itself unchanged.
@return int - The value held by initialTime. */

int event::getInitialTime() const
	{

	return initialTime;

	}

/** Event setArrivalOrDeparture function. Set for arrivalOrDeparture data member.
@pre None.
@post arrivalOrDeparture data member holds val.
@param val The char value to which arrivalOrDeparture is to be set.
@return None. */

void event::setArrivalOrDeparture(const char& val)
	{

	arrivalOrDeparture = val;

	}

/** Event getArrivalOrDeparture function. Returns the arrivalOrDeparture data member of an event object.
@pre None.
@post Event object's arrivalOrDeparture returned; object itself unchanged.
@return char - The value held by arrivalOrDeparture. */

char event::getArrivalOrDeparture() const
	{

	return arrivalOrDeparture;

	}

/** Event setTransactionDuration function. Set for transactionDuration data member.
@pre None.
@post transactionDuration data member holds val.
@param val The int value to which transactionDuration is to be set.
@return None. */

void event::setTransactionDuration(const int& val)
	{

	transactionDuration = val;

	}

/** Event getTransactionDuration function. Returns the transactionDuration data member of an event object.
@pre None.
@post Event object's transactionDuration returned; object itself unchanged.
@return int - The value held by transactionDuration. */

int event::getTransactionDuration() const
	{

	return transactionDuration;

	}

/** Event overloaded < operator. Evaluates using initialTime data members of the objects.
@pre None.
@post Bool returned; both objects unchanged.
@param val The event to which this one is being compared.
@return bool - True if this object's initialTime < val's initialTime, false otherwise. */

bool event::operator< ( const event& val ) const
	{

	return ( initialTime < val.initialTime );

	}

/** Event overloaded <= operator. Evaluates using initialTime data members of the objects.
@pre None.
@post Bool returned; both objects unchanged.
@param val The event to which this one is being compared.
@return bool - True if this object's initialTime <= val's initialTime, false otherwise. */

bool event::operator<= ( const event& val ) const
	{

	return ( initialTime <= val.initialTime );
	
	}

/** Event overloaded > operator. Evaluates using initialTime data members of the objects.
@pre None.
@post Bool returned; both objects unchanged.
@param val The event to which this one is being compared.
@return bool - True if this object's initialTime > val's initialTime, false otherwise. */

bool event::operator> ( const event& val ) const
	{

	return ( initialTime > val.initialTime );

	}

/** Event overloaded >= operator. Evaluates using initialTime data members of the objects.
@pre None.
@post Bool returned; both objects unchanged.
@param val The event to which this one is being compared.
@return bool - True if this object's initialTime >= val's initialTime, false otherwise. */

bool event::operator>= ( const event& val ) const
	{

	return ( initialTime >= val.initialTime );

	}

/** Event overloaded == operator. Evaluates using initialTime data members of the objects.
@pre None.
@post Bool returned; both objects unchanged.
@param val The event to which this one is being compared.
@return bool - True if this object's initialTime == val's initialTime, false otherwise. */

bool event::operator== ( const event& val ) const
	{

	return ( initialTime == val.initialTime );

	}

/** Event overloaded != operator. Evaluates using initialTime data members of the objects.
@pre None.
@post Bool returned; both objects unchanged.
@param val The event to which this one is being compared.
@return bool - True if this object's initialTime != val's initialTime, false otherwise. */

bool event::operator!= ( const event& val ) const
	{
	
	return ( initialTime != val.initialTime );

	}

//end event.h implementation
