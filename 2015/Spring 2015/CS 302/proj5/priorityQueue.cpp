/** CS 302 Project 5 - sorted list and priority queue implementations
@file priorityQueue.cpp
@author Patrick Austin
@date 3/21/2015 */

#include "queues.h"
#include "event.h"
using namespace std;

//array based sorted list implementation

/** arraySortedList constructor.
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre Sufficient dynamic memory available to create an ItemType array of size == val
@post arraySortedList is created and ready for first entry.
@return None. */

template < class ItemType >
arraySortedList<ItemType>::arraySortedList(int val)
	{

	size = val;

	itemCount = 0;

	items = new ItemType [size];

	}

/** arraySortedList destructor.
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre None.
@post Dynamic memory allocated for the arraySortedList object has been freed.
@return None. */

template < class ItemType >
arraySortedList<ItemType>::~arraySortedList()
	{

	delete [] items;

	}

/** arraySortedList insertSorted function. Inserts an item into the sorted list in a position
that will maintain the list's sorted property (ascending order).
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre None.
@post newEntry inserted into the list if it was not full, list unchanged otherwise
@param newEntry The item to be added into the sorted list.
@return bool True if insert operation was successful, false otherwise */

template < class ItemType >
bool arraySortedList<ItemType>::insertSorted (const ItemType & newEntry)
	{

	//if full, can't insert - return false

	if ( itemCount == size )
		return false;

	//otherwise, can insert - will return true

	else
		{

		//if this is the first item being inserted, put it at index 0 and you're done

		if ( itemCount == 0 )
			items[0] = newEntry;

		//otherwise, find the location where the item belongs and shift other values
		//to make room if necessary

		else
			{

			//find the spot where the item will be inserted

			int index = 0;

			while ( index < itemCount && newEntry >= items[index] )
				index++;

			//shift values above that point over by one

			for ( int j = itemCount; j > index; j-- )
				items[j] = items[j-1];

			//insert the value

			items[index] = newEntry;

			}

		//increment itemCount

		itemCount++;

		//return true

		return true;

		}
	
	}

/** arraySortedList removeSorted function. Removes a specified item from the sorted list while
maintaining maintain the list's sorted property (ascending order).
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre None.
@post If the value was located in the list, it has been removed. If the array was empty or
the value was not found, the list is unchanged.
@param anEntry The entry to be removed from the sorted list.
@return bool True if remove operation was successful, false otherwise. */

template < class ItemType >
bool arraySortedList<ItemType>::removeSorted (const ItemType & anEntry)
	{

	int index = 0;

	//if empty, cannot remove, return false

	if ( isEmpty() )
		return false;

	//otherwise, see if the value is in the array
	
	else
		{

		while ( items[index] != anEntry && index < itemCount )
			index++;

		//if the value was not found it can't be removed, return false

		if ( index == itemCount )
			return false;

		//otherwise the value was found - shift items, decrement itemCount, return true

		else
			{

			for ( index; index < itemCount - 1; index++ )
				items[index] = items[index+1]; 

			itemCount--;

			return true;

			}
		
		}
	}

/** arraySortedList getPosition function. Searches the sorted list for a value matching
the one provided, and returns its index if it is found.
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre None.
@post List unchanged; position of a value in the sorted list that == newEntry returned
if one was found. If not found, returns -1
@param newEntry The entry which is to be attempted to be located in the sorted list.
@return int The position of the value if found, -1 if not found. */

template < class ItemType >
int arraySortedList<ItemType>::getPosition (const ItemType & newEntry) const
	{

	int index = 0;

	//if empty, the value is not present, return dummy value

	if ( isEmpty() )
		return -1;

	//otherwise, search the array to see

	else
		{

		while ( items[index] != newEntry && index < itemCount )
			index++;

		//if the value was not found in the array, return dummy value

		if ( index == itemCount )
			return -1;

		//otherwise the value was found - return index + 1

		else
			return index + 1;

		}

	}

/** arraySortedList isEmpty function. Checks whether the sorted list is empty.
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre None.
@post List unchanged; bool signifying empty status returned.
@return bool True if the list is empty, false otherwise */

template < class ItemType >
bool arraySortedList<ItemType>::isEmpty () const
	{

	return (itemCount == 0);

	}

/** arraySortedList getLength function. Returns the number of items, ie the length,
of the sorted list.
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre None.
@post List unchanged; length value returned.
@return int The length of the sorted list. */

template < class ItemType >
int arraySortedList<ItemType>::getLength () const
	{

	return itemCount;

	}

/** arraySortedList remove function. Removes the item at a specified location from the sorted list while
maintaining maintain the list's sorted property (ascending order).
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre None.
@post Value at position removed, so long as the list was not empty and the requested position was not > the length
of the list.
@param position The position of the list from which to remove a value.
@return bool True if removal operation was successful, false otherwise.  */

template < class ItemType >
bool arraySortedList<ItemType>::remove (int position)
	{

	//if array is empty or they're asking for an out of bounds value, return false

	if ( isEmpty() || position > itemCount )
		return false;

	else
		{

		for ( int index = position - 1 ; index < itemCount - 1; index++ )
			items[index] = items[index + 1]; 

		itemCount--;

		return true;

		}

	}

/** arraySortedList clear function. Resets the sorted list to an empty state.
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre None.
@post Array sorted list is reset to its empty state.
@return None. */

template < class ItemType >
void arraySortedList<ItemType>::clear ()
	{

	itemCount = 0;

	}

/** arraySortedList getEntry function. Returns the item in the sorted list located
at the specified location.
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre The list must not be empty, and the position requested must not be greated than
the length of the list. Caveat emptor!
@post The value in the sorted list at target position returned; list contents unchanged.
@param position The location in the sorted list from which to retrieve an item.
@return ItemType The item at the specified location. */

template < class ItemType >
ItemType arraySortedList<ItemType>::getEntry (int position) const
	{

	return items[position - 1];

	}

template class arraySortedList<event>;

//end array based sorted list implementation

//linked list based sorted list implementation

template < class ItemType >
node < ItemType >* linkedSortedList<ItemType>::getnodeBefore (const ItemType & anEntry) const
	{

	node<ItemType>* curPtr = headPtr;
	node<ItemType>* prevPtr = nullptr;

	while ( (curPtr != nullptr) && (anEntry > curPtr->getItem()) )
		{

		prevPtr = curPtr;
		curPtr = curPtr->getNext();

		}

	return prevPtr;

	}

template < class ItemType >
node < ItemType >* linkedSortedList<ItemType>::getnodeAt (int position) const
	{

	if ( position > itemCount )
		return nullptr;

	else
		{

		node<ItemType>* temp = headPtr;

		for ( int index = 0; index < position - 1; index++ )
			temp = temp->getNext();

		return temp;

		}
	
	}

/** linkedSortedList constructor.
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre None.
@post linkedSortedList is created and ready for first entry.
@return None. */

template < class ItemType >
linkedSortedList<ItemType>::linkedSortedList ()
	{

	itemCount = 0;
	headPtr = nullptr;

	}

/** arraySortedList destructor.
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre None.
@post Dynamic memory allocated for the sorted list, if any, has been freed
@return None. */

template < class ItemType >
linkedSortedList<ItemType>::~linkedSortedList ()
	{

	clear();

	}

/** linkedSortedList insertSorted function. Inserts an item into the sorted list in a position
that will maintain the list's sorted property (ascending order).
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre None.
@post newEntry inserted into the list in sorted position.
@param newEntry The item to be added into the sorted list.
@return None. */

template < class ItemType >
void linkedSortedList<ItemType>::insertSorted (const ItemType & newEntry)
	{

	node<ItemType>* newNodePtr = new node<ItemType>(newEntry);
	node<ItemType>* curPtr = headPtr;
	node<ItemType>* prevPtr = nullptr;

	while ( (curPtr != nullptr) && (newEntry >= curPtr->getItem()) )
		{

		prevPtr = curPtr;
		curPtr = curPtr->getNext();

		}

	if ( isEmpty() || prevPtr == nullptr )
		{

		newNodePtr->setNext(headPtr);
		headPtr = newNodePtr;

		}

	else
		{

		node<ItemType>* aftPtr = prevPtr->getNext();
		newNodePtr->setNext(aftPtr);
		prevPtr->setNext(newNodePtr);

		}

	itemCount++;

	}

/** linkedSortedList removeSorted function. Removes a specified item from the sorted list while
maintaining maintain the list's sorted property (ascending order).
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre None.
@post If the value was located in the list, it has been removed. If the array was empty or
the value was not found, the list is unchanged.
@param anEntry The entry to be removed from the sorted list.
@return bool True if remove operation was successful, false otherwise. */

template < class ItemType >
bool linkedSortedList<ItemType>::remove (int position)
	{

	//if trying to remove from an empty list, or trying to remove out of bounds, return false

	if ( isEmpty() || position > itemCount )
		return false;

	else
		{

		int index;

		node<ItemType>* targetNodePtr = headPtr;

		//loop up to the specified node

		for ( index = 0; index < position - 1; index++ )
			targetNodePtr = targetNodePtr->getNext();

		node<ItemType>* prevNodePtr = nullptr;
		node<ItemType>* curPtr = headPtr;

		//while ( (curPtr != nullptr) && (targetNodePtr->getItem() > curPtr->getItem()) )
		for ( int j = 0; j < index; index++ )
			{

			prevNodePtr = curPtr;
			curPtr = curPtr->getNext();

			}

		//if this is the first node in the list, delete it and move head to the next item

		if ( prevNodePtr == nullptr && targetNodePtr->getNext() != nullptr )
			{

			headPtr = targetNodePtr->getNext();

			delete targetNodePtr;

			}

		//if this is the only node in the list, delete it and set head to nullptr

		else if ( prevNodePtr == nullptr && targetNodePtr->getNext() == nullptr )
			{

			delete targetNodePtr;

			headPtr = nullptr;

			}

		else 
			{

			//if this is the last node in the list but not the first, delete it and set the new last node's next
			//to nullptr

			if ( targetNodePtr->getNext() == nullptr )
				{

				delete targetNodePtr;

				prevNodePtr->setNext(nullptr);

				}

			//otherwise, remove the node and splice the pointers together

			else
				{

				node<ItemType>* aftPtr = targetNodePtr->getNext();

				prevNodePtr->setNext(aftPtr);

				delete targetNodePtr;

				}

			}

		itemCount--;	

		return true;

		}


	}

/** linkedSortedList isEmpty function. Checks whether the sorted list is empty.
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre None.
@post List unchanged; bool signifying empty status returned.
@return bool True if the list is empty, false otherwise */

template < class ItemType >
bool linkedSortedList<ItemType>::isEmpty () const
	{

	return ( itemCount == 0 );

	}

/** linkedSortedList getLength function. Returns the number of items, ie the length,
of the sorted list.
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre None.
@post List unchanged; length value returned.
@return int The length of the sorted list. */

template < class ItemType >
int linkedSortedList<ItemType>::getLength () const
	{

	return itemCount;

	}

/** linkedSortedList clear function. Resets the sorted list to an empty state.
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre None.
@post List is reset to its empty state. Any dynamic memory used has been freed.
@return None. */

template < class ItemType >
void linkedSortedList<ItemType>::clear ()
	{

	if ( !isEmpty() )
		{

		node<ItemType>* temp1;
		node<ItemType>* temp2;

		temp1 = temp2 = headPtr;

		while ( temp1->getNext() != nullptr )
			{

			temp2 = temp2->getNext();

			delete temp1;

			temp1 = temp2;

			}

		delete temp1;

		headPtr = nullptr;
		
		}

	}

/** linkedSortedList getEntry function. Returns the item in the sorted list located
at the specified location.
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre The list must not be empty, and the position requested must not be greater than
the length of the list. Caveat emptor!
@post The value in the sorted list at target position returned; list contents unchanged.
@param position The location in the sorted list from which to retrieve an item.
@return ItemType The item at the specified location. */

template < class ItemType >
ItemType linkedSortedList<ItemType>::getEntry (int position)
	{

	node<ItemType>* temp = headPtr;

	for ( int index = 0; index < position - 1; index++ )
		temp = temp->getNext();

	return temp->getItem();
		
	}

template class linkedSortedList<event>;

//end linked list based sorted list implementation

//array based priority queue implementation

/** priorityQueueArray constructor. 
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre Sufficient dynamic memory available to create an ItemType array of size == val
@post Priority queue created.
@return None. */

template < class ItemType >
priorityQueueArray<ItemType>::priorityQueueArray(int val)
	{

	size = val;

	aList = new arraySortedList<ItemType>(size);

	}

/** priorityQueueArray destructor. 
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre None.
@post Dynamic memory allocated for the priorityQueueArray object has been freed.
@return None. */

template < class ItemType >
priorityQueueArray<ItemType>::~priorityQueueArray()
	{

	delete aList;

	}

/** priorityQueueArray isEmpty function. Checks whether the priority queue is empty.
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre None.
@post PQ unchanged; bool signifying empty status returned.
@return bool True if the list is empty, false otherwise */

template < class ItemType >
bool priorityQueueArray<ItemType>::isEmpty () const
	{

	return ( aList->isEmpty() );

	}

/** priorityQueueArray add function. Attempts to add an item to the priority queue while
maintaining the queue's arrangement in order of priority.
@pre None.
@post newEntry added to PQ if the PQ was not already full.
@param newEntry The value to be added to the PQ.
@return bool True if the add was successful, false otherwise. */

template < class ItemType >
bool priorityQueueArray<ItemType>::add (const ItemType & newEntry)
	{

	if ( aList->getLength() < size )
		{

		aList->insertSorted(newEntry);

		return true;

		}

	else
		return false;

	}

/** priorityQueueArray remove function. Attempts to remove the highest
priority item from the PQ.
@pre None.
@post Highest priority item removed from the PQ if the PQ was not empty.
@return bool True if the removal was successful, false otherwise. */

template < class ItemType >
bool priorityQueueArray<ItemType>::remove ()
	{

	if ( isEmpty() )
		return false;

	else
		{

		aList->remove(1);

		return true;

		}

	}

/** priorityQueueArray peek function. Returns the highest priority item
currently stored in the PQ.
@pre The PQ must not be empty. Caveat emptor!
@post Highest priority item returned; PQ contents unchanged.
@return ItemType The highest priority item in the PQ. */

template < class ItemType >
ItemType priorityQueueArray<ItemType>::peek () const
	{

	return aList->getEntry(1);

	}

template class priorityQueueArray<event>;

//end array based priority queue implementation

//linked list based priority queue implementation

/** priorityQueueLinked constructor. 
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre Sufficient dynamic memory available to create a linkedSortedList object.
@post Priority queue created.
@return None. */

template < class ItemType >
priorityQueueLinked<ItemType>::priorityQueueLinked ()
	{

	slistPtr = new linkedSortedList<ItemType>;

	}

/** priorityQueueLinked destructor. 
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre None.
@post Dynamic memory allocated for the priorityQueueLinked object has been freed.
@return None. */

template < class ItemType >
priorityQueueLinked<ItemType>::~priorityQueueLinked ()
	{

	slistPtr->clear();

	}

/** priorityQueueLinked isEmpty function. Checks whether the priority queue is empty.
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre None.
@post PQ unchanged; bool signifying empty status returned.
@return bool True if the list is empty, false otherwise */

template < class ItemType >
bool priorityQueueLinked<ItemType>::isEmpty () const
	{

	return ( slistPtr->getLength() == 0 );

	}

/** priorityQueueLinked add function. Adds an item to the priority queue while
maintaining the queue's arrangement in order of priority.
@pre Sufficient dynamic memory available for a new ItemType object.
@post newEntry added to the PQ.
@param newEntry The value to be added to the PQ.
@return bool Always returns true. */

template < class ItemType >
bool priorityQueueLinked<ItemType>::add (const ItemType & newEntry)
	{

	slistPtr->insertSorted(newEntry);

	return true;

	}

/** priorityQueueLinked remove function. Attempts to remove the highest
priority item from the PQ.
@pre None.
@post Highest priority item removed from the PQ if the PQ was not empty.
@return bool True if the removal was successful, false otherwise. */

template < class ItemType >
bool priorityQueueLinked<ItemType>::remove ()
	{

	if ( slistPtr->isEmpty() )
		return false;

	else
		{

		slistPtr->remove(1);

		return true;

		}

	}

/** priorityQueueLinked peek function. Returns the highest priority item
currently stored in the PQ.
@pre The PQ must not be empty. Caveat emptor!
@post Highest priority item returned; PQ contents unchanged.
@return ItemType The highest priority item in the PQ. */

template < class ItemType >
ItemType priorityQueueLinked<ItemType>::peek () const
	{

	return slistPtr->getEntry(1);

	}

template class priorityQueueLinked<event>;

//end linked list based priority queue implementation

