/** CS 302 Project 5 - node class header
@file node.h
@author Patrick Austin
@date 3/21/2015 */

#ifndef _NODE_H
#define _NODE_H

/**

Templated node class for use in linked-list based queue/sortedlist/priority queue
operations in this program. 
!!! ADAPTED FROM TEXTBOOK CODE !!!

*/

template < class ItemType >
class node {

	private:

	ItemType item;
	node<ItemType>* next;

	public:

	node();
	node( const ItemType& anItem );
	node( const ItemType& anItem, node<ItemType>* nextnodePtr);
	void setItem( const ItemType& anItem);
	void setNext(node<ItemType>* nextnodePtr);
	ItemType getItem() const ;
	node<ItemType>* getNext() const ;

	};

#endif
