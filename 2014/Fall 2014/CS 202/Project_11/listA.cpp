//array based list implementation

#include "listA.h"
#include <iostream>
using namespace std;

	ListA::ListA(int target)
		{

		data = new int [target];

		size = target;

		actual = 0;

		cursor = -1;

		}

	ListA::ListA(const ListA &src)
		{

		data = new int [src.size];

		size = src.size;

		actual = src.actual;

		cursor = src.cursor;

		for ( int index = 0; index != src.actual+1; index++ )
			{

			data[index] = src.data[index];

			}

		}

	ListA::~ListA()
		{

		delete [] data;

		data = NULL;

		}

	bool ListA::gotoBeginning()
		{

		if ( cursor == -1 )
			{

			return false;

			}

		else
			{

			cursor = 0;

			return true;

			}

		}

	bool ListA::gotoEnd()
		{

		//if already at the end, return false

		if ( cursor == actual - 1 )
			{

			return false;

			}

		//if empty, you're already at the end - return false

		else if ( empty() )
			{

			return false;

			}

		//otherwise, go to the end and return true

		else
			{

			cursor = actual - 1;

			return true;

			}
		}

	bool ListA::gotoNext()
		{

		//if the array is empty you can't go to next, return false

		if ( empty() )
			{

			return false;

			}

		//if the cursor is at the last position you can't go to next, return false

		else if ( cursor == actual - 1 )
			{

			return false;

			}

		//otherwise, increment the cursor by 1 and return true

		else
			{

			cursor++;

			return true;

			}

		}

	bool ListA::gotoPrior()
		{

		//if the array is empty you can't go to prior, return false

		if ( empty() )
			{

			return false;

			}

		//if the cursor is at 0, you can't go to prior, return false

		else if ( cursor == 0 )
			{

			return false;

			}

		//otherwise decrement cursor and return true

		else 
			{

			cursor--;

			return true;

			}

		}

	bool ListA::insertAfter(int target)
		{

		//if the array is full, you can't insert anything else, return false

		if ( full() )
			{

			return false;

			}

		//if the array is empty, put the value at 0 and return true

		else if ( empty() )
			{

			cursor++;

			data[cursor] = target;

			actual++;

			return true;

			}

		//otherwise, move the other values, insert the target value, and have the cursor at that value. then return true

		else
			{

			for ( int index = actual - 1; index != cursor; index-- )
				{

				data[index] = data[index-1];

				}

			cursor++;

			data[cursor] = target;

			actual++;

			return true;

			}

		}

	bool ListA::insertBefore(int target)
		{

		//if the array is full you can't insert anything, return false

		if ( full() )
			{

			return false;

			}

		//if the array is empty, put the value at zero and return true

		else if ( empty() )
			{

			cursor++;

			data[cursor] = target;

			actual++;

			return true;

			}

		//otherwise, move the other values, insert target value and have the cursor at that value, and return true

		else
			{

			for ( int index = actual - 1; index != cursor -1; index-- )
				{

				data[index] = data[index-1];

				}

			data[cursor] = target;

			actual++;

			return true;

			}
		
		}

	bool ListA::remove(int &value)
		{

		//if the array is empty there's nothing to remove, return false

		if ( empty() )
			{

			return false;

			}

		//otherwise, pull any extant values up the array, leaving cursor where it is unless it was at actual - 1, and return true 

		else
			{

			//grab the value to return

			value = data[cursor];

			//if actual - 1 is equal to cursor, ie cursor is at the end of the good values in the array, just decrement actual and cursor

			if ( cursor == actual - 1 )
				{

				actual--;
				
				cursor--;

				}

			//otherwise, pull up extant values

			else
				{

				for ( int index = cursor; index != actual - 1; index++ )
					{

					data[index] = data[index + 1];

					}

				actual--;

				}

			return true;

			}

		}

	bool ListA::replace(int target)
		{

		//if empty, there's nothing to replace - return false

		if ( empty() )
			{

			return false;

			}

		//otherwise, copy target value into cursor location and return true

		else
			{

			data[cursor] = target;

			return true;

			}

		}

	bool ListA::getCursor(int &value) const
		{

		if ( empty() )
			{

			value = data[cursor];

			return false;

			}

		else
			{

			value = data[cursor];

			return true;

			}

		}

	bool ListA::empty() const
		{

		if ( cursor == -1 && actual == 0 )
			{

			return true;

			}

		else
			return false;

		}

	bool ListA::full() const
		{

		if ( actual == size )
			{

			return true;

			}

		else
			return false;

		}

	bool ListA::clear()
		{

		if ( empty() )
			{

			return false;

			}

		else
			{

			cursor = -1;

			actual = 0;

			return true;

			}

		}

	ListA& ListA::operator=(const ListA &src)
		{

		//first, check to see if you're assigning a list to itself

		if ( this != &src )
			{

			//copy data members

			actual = src.actual;

			cursor = src.cursor;

			//if the sizes do not match, deallocate the old array and make a new one of the correct size with a matching max

			if ( src.size != size )
				{

				size = src.size;
				
				delete [] data;

				data = new int [src.size];

				}

			//if not empty, copy the values in src array into new array

			if ( !empty() )
				{

				for ( int index = 0; index != actual; index++ )
					{

					data[index] = src.data[index];

					}

				}
		
		}

		//return this list
	
		return (*this);		

		}

	ostream& operator<<(ostream& out, const ListA &src)
		{

		//check to see if the list is empty

		if ( src.empty() )
			{

			//if so, print a message

			out << "Empty List ";
		
			}

		//otherwise, print the good values to console

		else
			{

			for ( int index = 0; index != src.actual; index++ )
				{

				//if the value is the one the cursor is pointing to, print it in []

				if ( index == src.cursor )
					{

					out << "[" << src.data[index] << "]" << " ";

					}

				//otherwise, just print the value

				else
					{

					out << src.data[index] << " ";

					}

				}

			}

		//return ostream object

		return out;

		}

	bool ListA::operator==(const ListA &target) const
		{

		//compare the data members

		if ( actual != target.actual )
			{

			return false;

			}

		if ( cursor != target.cursor )
			{

			return false;

			}

		if ( size != target.size )
			{

			return false;

			}

		//compare the contents of the array - loop does not trigger on an empty array

		for ( int index = 0; index != actual; index++ )
			{

			if ( data[index] != target.data[index] )
				{

				return false;

				}

			}

		//if everything matched return true

		return true;		

		}
		
