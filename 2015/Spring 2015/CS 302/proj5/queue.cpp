/** CS 302 Project 5 - queue implementations
@file queue.cpp
@author Patrick Austin
@date 3/21/2015 */

#include "queues.h"
#include "event.h"
#include "node.h"
using namespace std;

//array queue implementation

/** arrayQueue constructor.
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre Sufficient dynamic memory available to create an ItemType array of size == val
@post arrayQueue is created and ready for first entry.
@return None. */

template < class ItemType > 
arrayQueue < ItemType >::arrayQueue (int val):front (-1), back (-1), count (0), size(val)
	{

	items = new ItemType [size];
 
	}				// end constructor

/** arrayQueue destructor.
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre None.
@post Dynamic memory allocated for the arrayQueue object has been freed.
@return None. */

template < class ItemType > 
arrayQueue < ItemType >::~arrayQueue ()
	{

	delete [] items;
 
	}				// end default constructor

/** arrayQueue isEmpty function. Checks whether the queue is empty.
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre None.
@post List unchanged; bool signifying empty status returned.
@return bool True if the list is empty, false otherwise */

template < class ItemType > bool arrayQueue < ItemType >::isEmpty () const
	{

	  return count == 0;

	}				// end isEmpty

/** arrayQueue enqueue function. Attempts to enqueue an item at the back of the queue.
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre None.
@post Value added at the back of the queue if the queue was not full.
@param newEntry The value to be enqueued.
@return bool True if the enqueue was successful, false if it failed. */

template < class ItemType > 
bool arrayQueue < ItemType >::enqueue (const ItemType & newEntry)
	{

	  bool result = false;

	  if (count == 0 )
	    {

	    front++;
	    back++;
	    count++;
	    items[back] = newEntry;
	    result = true;

	    }

	  else if (count < size)
	    {
	// Queue has room for another item
	      back++;
	      items[back] = newEntry;
	      count++;
	      result = true;
	    }				// end if
	  return result;

	}				// end enqueue

/** arrayQueue dequeue function. Attempts to remove an item from the front of the queue.
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre None.
@post Value removed from the queue, provided the queue was not empty.
@return bool True if the dequeue was successful, false if it failed. */

template < class ItemType > 
bool arrayQueue < ItemType >::dequeue ()
	{

	bool result = false;

	if ( !isEmpty() )
		{

		if ( count == 1 )
			{
			
			front--;

			}

		else
			{

			for ( int index = 0; index < back; index++ )
				{

				items[index] = items[index+1];

				}

			}

		back--;
		count--;
		result = true;
	
		}

	return result;

	}				// end dequeue

/** arrayQueue peek function. Returns the item currently stored at the front of the queue.
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre The queue must not be empty. Caveat emptor!
@post Item at the front of the queue returned; queue contents unchanged.
@return ItemType The item returned by the peek operation. */

template < class ItemType > 
ItemType arrayQueue < ItemType >::peek () const
	{

	  return items[front];

	}				// end peekFront

template class arrayQueue<event>;

//end array queue implementation

//node based queue implementation

/** linkedQueue constructor.
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre None.
@post linkedQueue is created and ready for first entry.
@return None. */

template < class ItemType >
linkedQueue<ItemType>::linkedQueue ()
	{
	frontPtr = backPtr = nullptr;
	}

/** linkedQueue destructor.
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre None.
@post Dynamic memory allocated for the arrayQueue object has been freed.
@return None. */

template < class ItemType >
linkedQueue<ItemType>::~linkedQueue ()
	{

	if ( !isEmpty() )
		{

		node<ItemType>* temp1;
		node<ItemType>* temp2;

		temp1 = temp2 = frontPtr;

		while ( temp1->getNext() != nullptr )
			{

			temp2 = temp2->getNext();

			delete temp1;

			temp1 = temp2;

			}

		delete temp1;

		frontPtr = backPtr = nullptr;
		
		}
		
	}

/** linkedQueue isEmpty function. Checks whether the sorted list is empty.
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre None.
@post List unchanged; bool signifying empty status returned.
@return bool True if the list is empty, false otherwise */

template < class ItemType >
bool linkedQueue<ItemType>::isEmpty () const
	{

	if ( backPtr == nullptr )
		return true;
	else
		return false;

	}

/** linkedQueue enqueue function. Attempts to enqueue an item at the back of the queue.
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre None.
@post Value added at the back of the queue.
@param newEntry The value to be enqueued.
@return bool Always returns true. */

template < class ItemType >
bool linkedQueue<ItemType>::enqueue (const ItemType & newEntry)
	{

	node<ItemType>* temp;

	temp = new node<ItemType>( newEntry, nullptr );

	if ( isEmpty() )
		{

		frontPtr = temp;

		backPtr = temp;

		}

	else
		{

		backPtr->setNext(temp);

		backPtr = temp;

		}

	return true;

	}

/** linkedQueue dequeue function. Attempts to remove an item from the front of the queue.
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre None.
@post Value removed from the queue, provided the queue was not empty.
@return bool True if the dequeue was successful, false if it failed. */

template < class ItemType >
bool linkedQueue<ItemType>::dequeue ()
	{

	if ( isEmpty() )
		return false;

	else
		{

		node<ItemType>* temp;

		temp = frontPtr;

		if ( frontPtr == backPtr )
			{

			frontPtr = backPtr = nullptr;

			}

		else
			frontPtr = frontPtr->getNext();

		delete temp;

		return true;

		}

	}

/** linkedQueue peek function. Returns the item currently stored at the front of the queue.
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre The queue must not be empty. Caveat emptor!
@post Item at the front of the queue returned; queue contents unchanged.
@return ItemType The item returned by the peek operation. */

template < class ItemType >
ItemType linkedQueue<ItemType>::peek () const
	{

	return ( frontPtr->getItem() );

	}

template class linkedQueue<event>;


