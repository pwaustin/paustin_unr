//node based list implementation

#include "listN.h"
#include <iostream>
using namespace std;

	Node::Node(char target, Node* dest)
		{
	
		data = target;

		next = dest;

		}

	List::List(int unused)
		{

		head = NULL;

		cursor = NULL;

		}

	List::List(const List &src)
		{

		//if copying an empty list, just set the pointers to null

		if ( src.empty() )
			{

			head = NULL;
		
			cursor = NULL;

			}

		//otherwise, copy and link up nodes until next of a source node points to null
	
		else
			{

			//copy the head

				//create temp pointers

				Node* srctemp = src.head;
				Node* temp;
				Node* temp2;

				//create a new node with a copy of the head's data

				temp = new Node( srctemp->data , NULL );

				//set head and cursor to point here

				head = temp;

				cursor = head;

			//while there are additional nodes, copy them

			while ( srctemp->next != NULL )
				{

				//hold on to the address of the node you just made so you can hook up next

				temp2 = temp;
				
				//move src temp to the next node

				srctemp = srctemp->next;

				//create a new node with a copy of srctemp's data

				temp = new Node( srctemp->data, NULL );

				//hook up the previous node's next to this node
				
				temp2->next = temp;

				//if the cursor of the source list points to this value, point it to this temp node

				if ( src.cursor == srctemp )
					{

					cursor = temp;

					}

				}

			}

		}

	List::~List()
		{

		//while there are good nodes, deallocate them

		Node* temp1;
		Node* temp2;

		temp1 = head;

		while ( temp1 != NULL )
			{

			temp2 = temp1->next;

			delete temp1;

			temp1 = temp2;

			}

		}

	bool List::gotoBeginning()
		{

		//if empty, there is no beginning to go to, return false

		if ( empty() )
			{

			return false;

			}

		//otherwise, set cursor back to head and return true

		else
			{

			cursor = head;

			return true;

			}

		}

	bool List::gotoEnd()
		{

		//if empty, there is no end to go to, return false

		if ( empty() )
			{

			return false;

			}

		//otherwise, look through all the nodes until you hit the one where next points to null, and put the cursor there. then return true

		else
			{

			Node* temp;

			temp = head;

			while ( temp->next != NULL )
				{

				temp = temp->next;

				}

			cursor = temp;

			return true;			

			}

		}

	bool List::gotoNext()
		{

		//if empty, return false

		if ( empty() )
			{

			return false;

			}

		//if next points to null, return false

		if ( cursor->next == NULL )
			{

			return false;

			}
		
		//otherwise, set cursor to cursor->next and return true

		else
			{

			cursor = cursor->next;

			return true;

			}

		}

	bool List::gotoPrior()
		{

		//if empty, return false

		if ( empty() )
			{

			return false;

			}

		//if cursor is pointing to head, can't go back - return false

		else if ( cursor == head )
			{

			return false;

			}

		//otherwise, loop from the head until next equals cursor, and set cursor to that node

		else

			{

			Node* temp;

			temp = head;

			while ( temp->next != cursor )
				{
			
				temp = temp->next;

				}

			cursor = temp;

			return true;

			}

		}

	bool List::insertAfter(char target)
		{

		Node* temp;
		Node* temp2;
		
		//if this is the first node being added, make it, set it to head and cursor and return true

		if ( empty() )
			{

			head = new Node( target, NULL );

			cursor = head;

			return true;

			}

		//if this is the last node, add it, hook it up to where cursor is, then move cursor to it and return true

		else if ( cursor->next == NULL )
			{

			temp = new Node ( target, NULL );

			cursor->next = temp;

			cursor = temp;

			return true;

			}

		//otherwise, splice the new node in and hook up the pointers, update cursor, return true

		else
			{

			//grab the next pointer from the cursor and hold it for a second

			cursor->next = temp2;

			//make the new node and hook it up using temp2

			temp = new Node ( target, temp2 );

			cursor->next = temp;

			cursor = temp;

			return true;

			}

		}

	bool List::insertBefore(char target)
		{

		Node* temp;
		Node* temp2;

		//if this is the first node being added, make it, set it to head and cursor and return true

		if ( empty() )
			{

			head = new Node( target, NULL );

			cursor = head;

			return true;

			}
		
		//if this is the head, create the new node and make it the new head and return true

		else if ( cursor == head )
			{
		
			//hold on to the current head value for a second

			temp2 = head;

			//make the new node at head- its next will be temp2

			head = new Node( target, temp2 );

			cursor = head;

			return true;

			}

		//otherwise, splice the new node and hook up pointers, update cursor, return true

		else
			{

			//loop through the list for the value before cursor

			temp = head;

			while ( temp->next != cursor )
				{

				temp = temp->next;

				}

			//make a new node whose next is cursor

			temp2 = new Node ( target, cursor );

			temp->next = temp2;

			cursor = temp2;

			return true;

			}

		}

	bool List::remove(char &value)
		{

		Node* temp;
		Node* temp2;

		//if the list is empty, nothing to remove - return false

		if ( empty() )
			{

			return false;

			}

		//if there is only one item in the list, delete the node, set pointers to null, return true

		else if ( cursor->next == NULL && head->next == NULL )
			{

			value = cursor->data;

			delete cursor;

			cursor = NULL;

			head = NULL;

			return true;

			}

		//if the item is at the end of the list, loop back and change the pointer to the deleted node to null. return true

		else if ( cursor->next == NULL )
			{

			value = cursor->data;

			temp = head;

			//loop until the next of the NEXT node equals null

			while ( temp->next->next != NULL )
				{

				temp = temp->next;

				}

			//delete the node

			delete cursor;

			//fix the pointer that pointed at the node you just deleted

			temp->next = NULL;

			//update cursor - to beginning, as per specification

			cursor = head;

			return true;

			}

		//otherwise, the item is between values - the pointers need to be stitched together and the node needs to be deleted. return true
		
		else
			{

			value = cursor->data;

			temp2 = cursor->next;

			//get a temp pointing to the node before cursor

			temp = head;

			while ( temp->next != cursor )
				{

				temp = temp->next;

				}

			//that node's next needs to point to cursor's next

			temp->next = cursor->next;

			//delete node

			delete cursor;

			cursor = temp2;

			return true;

			}


		}

	bool List::replace(char target)
		{

		//if empty, nothing to replace, return false

		if ( empty() )
			{

			return false;

			}

		//otherwise overwrite the value with target and return true

		else
			{

			cursor->data = target;

			return true;

			}
			

		}

	bool List::getCursor(char &value) const
		{

		//if empty, nothing to get, return false

		if ( empty() )
			{

			return false;

			}

		//otherwise, copy cursor->data into value and return true

		else
			{

			value = cursor->data;

			return true;

			}

		}

	bool List::empty() const
		{

		//if head points to null, it's empty

		if ( head == NULL )
			{

			return true;

			}

		//otherwise it's not empty

		else
			{

			return false;

			}

		}

	bool List::full() const
		{

		//a node based list is never full for our purposes - return false

		return false;

		}

	bool List::clear()
		{

		//if empty, nothing to clear, return false

		if ( empty() )
			{

			return false;

			}

		//otherwise, deallocate the nodes, set pointers back to null and return true

		else
			{

			//while there are good nodes, deallocate them - as per destructor

			Node* temp1;
			Node* temp2;

			temp1 = head;

			while ( temp1 != NULL )
				{

				temp2 = temp1->next;

				delete temp1;

				temp1 = temp2;

				}

			//set head and cursor to null

			head = NULL;

			cursor = NULL;

			}

		}

	List& List::operator=(const List &src)
		{

		//make sure you're not trying to copy a list to itself

		if ( this != &src )
			{

			//first, attempt to clear this list of anything that may already be in it

			this->clear();

			//if src is not empty, copy its data

			if ( !src.empty() )
				{

				//now copy the data as per copy constructor

					//copy the head

						//create temp pointers

						Node* srctemp = src.head;
						Node* temp;
						Node* temp2;

						//create a new node with a copy of the head's data

						temp = new Node( srctemp->data , NULL );

						//set head and cursor to point here

						head = temp;

						cursor = head;

					//while there are additional nodes, copy them

					while ( srctemp->next != NULL )
						{

						//hold on to the address of the node you just made so you can hook up next

						temp2 = temp;
				
						//move src temp to the next node

						srctemp = srctemp->next;

						//create a new node with a copy of srctemp's data

						temp = new Node( srctemp->data, NULL );

						//hook up the previous node's next to this node
				
						temp2->next = temp;

						//if the cursor of the source list points to this value, point it to this temp node

						if ( src.cursor == srctemp )
							{

							cursor = temp;

							}

						}

				}
	
			}

		//return "this" list

		return (*this);

		}

	ostream& operator<<(ostream &out, const List &src)
		{

		//if the list is empty, print a message saying so

		if ( src.empty() )
			{

			out << "Empty List";

			}

		//otherwise, print the values from the nodes until you hit a node where next points to null

		else
			{

			//print the first value

			Node* temp = src.head;

				//print the value in square brackets if it is also at cursor

				if ( src.cursor == temp )
					{

					out << "[" << temp->data << "]";

					}

				//otherwise just print the value

				else
					{

					out << temp->data;

					}

			//continue printing values until you hit a node where next points to null

			while ( temp->next != NULL )
				{

				temp = temp->next;

				//print the value in square brackets if it is also at cursor

				if ( src.cursor == temp )
					{

					out << "[" << temp->data << "]";

					}

				//otherwise just print the value

				else
					{

					out << temp->data;

					}

				}

			
			}

		//return ostream object

		return out;

		}

	bool List::operator==(const List &target) const
		{

		//if head of both lists points at null, they're both empty, return true

		if ( empty() && target.empty() )
			{

			return true;

			}

		//otherwise you'll have to compare the data in each node and return a false if you find a mismatch

		else
			{

			Node* temp;
			Node* temp2;

			temp = head;
			temp2 = target.head;

			//compare the head values

			if ( temp->data != temp2->data )
				{

				return false;

				}

			if ( ( temp == cursor && temp2 != cursor ) || ( temp != cursor && temp2 == cursor ) )
				{

				return false;

				}

			//continue comparing values - stop when one of the lists hits null 

			while ( temp->next != NULL && temp2->next != NULL )
				{
				
				temp = temp->next;
				temp2 = temp2->next;

				if ( temp->data != temp2->data )
					{

					return false;

					}

				if ( ( temp == cursor && temp2 != cursor ) || ( temp != cursor && temp2 == cursor ) )
					{

					return false;

					}

				}

			//having exited the loop, return false if both next do not equal NULL

			if ( temp->next == NULL && temp2->next == NULL )
				{
				
				return true;

				}

			else
				return false;

			}

		}
