/** CS 302 Project 5 - queue, sorted list, and priority queue specifications
@file queues.h
@author Patrick Austin
@date 3/21/2015 */

#ifndef _QUEUES_H
#define _QUEUES_H
#include "node.h"

//queues

/**

Array based queue. Templated.
!!! ADAPTED FROM TEXTBOOK CODE !!!

*/

template < class ItemType >	//array-based queue
class arrayQueue {

	private:

	ItemType* items;
	int front;			
	int back;			
	int count;
	int size;		

	public:

	arrayQueue (int);
	~arrayQueue();
	bool isEmpty () const;
	bool enqueue (const ItemType & newEntry);
	bool dequeue ();
	ItemType peek () const;

	};	

/**

Node based queue. Templated.
!!! ADAPTED FROM TEXTBOOK CODE !!!

*/	

template < class ItemType >	//node based queue
class linkedQueue {				

	private:

	node<ItemType>* backPtr;
	node<ItemType>* frontPtr;

	public:

	linkedQueue ();
	~linkedQueue ();
	bool isEmpty () const;
	bool enqueue (const ItemType & newEntry);
	bool dequeue ();
	ItemType peek () const;

	};	

//sorted lists

/**

Array based sorted list. Templated.
!!! ADAPTED FROM TEXTBOOK CODE !!!

*/

template < class ItemType >	//array list based sorted list
class arraySortedList {

	private:

	ItemType* items;
	int itemCount;
	int size;

	public:

	arraySortedList (int);
	~arraySortedList ();
	bool insertSorted (const ItemType & newEntry);
	bool removeSorted (const ItemType & anEntry);
	int getPosition (const ItemType & newEntry) const;
	bool isEmpty () const;
	int getLength () const;
	bool remove (int position);
	void clear ();
	ItemType getEntry (int position) const;

	};

/**

Node based sorted list. Templated.
!!! ADAPTED FROM TEXTBOOK CODE !!!

*/			

template < class ItemType > 	//node based sorted list
class linkedSortedList {

	private:

	node < ItemType > *headPtr;
	int itemCount;
	node < ItemType >* getnodeBefore (const ItemType & anEntry) const;
	node < ItemType >* getnodeAt (int position) const;

	public:

	linkedSortedList ();
	~linkedSortedList ();
	void insertSorted (const ItemType & newEntry);
	bool remove (int position);
	int getPosition (const ItemType & newEntry) const;
	bool isEmpty () const;
	int getLength () const;
	void clear ();
	ItemType getEntry (int position);

	}; 

//priority queues

/**

Array based priority queue ( using arraySortedList ). Templated. 
!!! ADAPTED FROM TEXTBOOK CODE !!!

*/

template < class ItemType > 	//array sorted list based priority queue
class priorityQueueArray {

	private:

	arraySortedList<ItemType>* aList;
	int size;

	public:

	priorityQueueArray(int);
	~priorityQueueArray();
	bool isEmpty () const;
	bool add (const ItemType & newEntry);
	bool remove ();
	ItemType peek () const;

	};

/**

Node based priority queue ( using linkedSortedList ). Templated.
!!! ADAPTED FROM TEXTBOOK CODE !!!

*/

template < class ItemType > 	//linked sorted list based priority queue
class priorityQueueLinked {		

	private:

	linkedSortedList<ItemType>* slistPtr;
								
	public:

	priorityQueueLinked ();
	~priorityQueueLinked ();
	bool isEmpty () const;
	bool add (const ItemType & newEntry);
	bool remove ();
	ItemType peek () const;

	};

#endif

