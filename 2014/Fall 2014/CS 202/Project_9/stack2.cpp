//stack (move) implementation

#include "stack.h"
#include <iostream>
using namespace std;

	Stack::Stack(int size)
	{

		//create array of specified size

		data = new char [size];

		//set max

		max = size - 1;

		//set top to -1, since there are no good values yet

		top = -1;

		//set actual to dummy value - not used in this implementation

		actual = -9999;

	}

	Stack::Stack(const Stack &src)	//copy constructor
	{

		//create a new stack to hold the copied values

		data = new char [src.max + 1];

		//copy max

		max = src.max;

		//copy top

		top = src.top;

		//copy actual's dummy value - not used in this implementation

		actual = src.actual;

		//copy the values in the src array into the new array

		for ( int index = 0; index < top + 1; index++ )
			{

			data[index] = src.data[index];

			}

	}

	Stack::~Stack()
	{

		//deallocate the data array

		delete [] data;

		//set pointer to null

		data = NULL;

	}

	Stack& Stack::operator=(const Stack &src)
	{

		//check to see if you're trying to assign a stack to itself

		if ( this != &src )
			{

			//if not, you're clear to copy the data

				//copy top

				top = src.top;

				//if the sizes do not match, deallocate the old array and make a new one of the correct size with a matching max

				if ( src.max != max )
					{

					max = src.max;
				
					delete [] data;

					data = new char [src.max + 1];

					}

				//copy the values in src array into new array

				for ( int index = 0; index < top + 1; index++ )
					{

					data[index] = src.data[index];

					}

			}

		//return "this" stack

		return (*this);

	}

	bool Stack::push(char target)
	{

		//first, check to see if the array is full. If it's not full, you're clear to push

		if ( this->full() != true )
			{

			//increment top

			top++;

			//insert specified value at the new top

			data[top] = target;

			//return true - specifies that push succeeded

			return true;		

			}

		//otherwise, the push failed because the array was full - return false

		else
			return false;

	}

	bool Stack::pop(char &value )
	{

		//first, check to see if the array is empty. If it's not empty, you're clear to pop

		if ( this->empty() != true )
			{

			//set the popped value to the reference parameter so the user can retrieve it

			value = data[top];

			//decrement top

			top--;

			//return true - specifies that pop succeeded

			return true;

			}

		//otherwise, the pop failed because the array was empty - return false

		else
			return false;

	}

	bool Stack::empty() const
	{

		//if the top is at -1, the array is empty - return true
		
		if ( top < 0 )
			{

			return true;
	
			}	

		//otherwise, the array is not empty - return false

		else
			return false;

	}

	bool Stack::full() const
	{

		//if the top is at max, the array is full - return true

		if ( top == max )
			{

			return true;

			}

		//otherwise, the array is not full - return false

		else
			return false;

	}

	bool Stack::clear()
	{

		//check to see if the array isn't empty already

		if ( this->empty() != true )
			{

			//set top back to -1; this effectively clears the array

			top = -1;

			//return true - indicates data was cleared

			return true;

			}

		//if the array was empty already, return false - indicates no data was clared

		else
			return false;

	}

	bool Stack::operator==(const Stack &target) const
	{

		//if tops are not equal, return false

		if ( top != target.top )
			{

			return false;

			}

		//if max is not equal, return false

		if ( max != target.max )
			{

			return false;

			}

		//compare the valid items in the data array 
		//Note: this loop will not fire if both stacks are empty, so two empty stacks will be considered equal

		for ( int index = 0; index < top + 1; index++ )
			{

			//if valid values are not equal, set flag to false

			if ( data[index] != target.data[index] )
				{

				return false;

				}

			}

		//if none of these returned false, return true

		return true;

	}

	ostream& operator<< (ostream &out, const Stack &target )
	{

		//first, check to see if you're trying to print an empty array

		if ( target.empty() != true )
			{

			//print the valid values contained in the array:
	
			for ( int index = 0; index < target.top + 1; index++ )
				{

				//for values that aren't at the top, just print the value
	
				if ( index != target.top )
					{

					out << target.data[index];

					}

				//for the value at the top, print it surrounded by square brackets

				if ( index == target.top )
					{

					out << "[" << target.data[index] << "]";

					out << endl;

					}

				}

			}

		//if the array was empty, print a message

		else
			out << "Empty stack!" << endl;

		//return the ostream object

		return out;

	}
