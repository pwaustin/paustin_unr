/** CS 302 Project 5 - node class implementation
@file node.cpp
@author Patrick Austin
@date 3/21/2015 */

#include "node.h"
#include "event.h"
#include <cstddef>
#include <cstdlib>

/** Node default constructor. Sets next value to nullptr.
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre Enough available memory for a new node to be created.
@post Node created with next == nullptr.
@return None. */

template < class ItemType > node < ItemType >::node ():next (nullptr)
	{
	}   // end default constructor

/** Node parameterized constructor. Sets next value to nullptr and item to the one provided.
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre Enough available memory for a new node to be created.
@post Node created with next == nullptr and item == anItem.
@param anItem The item which will be held by this node.
@return None. */

template < class ItemType > node < ItemType >::node (const ItemType & anItem):
	item (anItem),
	next (nullptr)
	{
	}   // end constructor

/** Node parameterized constructor. Sets next value to nextNodePtr and item to the one provided.
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre Enough available memory for a new node to be created.
@post Node created with next == nextNodePtr and item == anItem
@param anItem The item which will be held by this node
@param nextNodePtr A pointer which will be held by the node's next data member.
@return None. */

template < class ItemType > node < ItemType >::node (const ItemType & anItem,
						     node < ItemType > *nextNodePtr):
	item (anItem),
	next (nextNodePtr)
	{
	}   // end constructor

/** Node setItem function. Sets the node's item data member to the one provided.
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre None.
@post Node's item data member set to anItem
@param anItem The item which will be held by this node.
@return None. */

template < class ItemType > void node < ItemType >::setItem (const ItemType & anItem)
	{
	  item = anItem;
	}   // end setItem

/** Node setNext function. Sets the node's next data member to the one provided.
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre None.
@post Node's next data member set to nextNodePtr
@param nextNodePtr The pointer which this node's next data member will point to.
@return None. */

template < class ItemType > void node < ItemType >::setNext (node < ItemType > *nextNodePtr)
	{
	  next = nextNodePtr;
	}   // end setNext

/** Node getItem function. Returns the item held in this node's item data member.
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre None.
@post Value returned; node is unchanged
@return ItemType The item held by the node's item data member. */

template < class ItemType > ItemType node < ItemType >::getItem () const
	{
	  return item;
	}   // end getItem

/** Node getNext function. Returns the pointer held in this node's next data member.
!!! ADAPTED FROM TEXTBOOK CODE !!!
@pre None.
@post Value returned; node is unchanged
@return node<ItemType>* The pointer held by the node's next data member. */

template < class ItemType > node < ItemType > *node < ItemType >::getNext () const
	{
	  return next;
	}   // end getNext

template class node<event>;
