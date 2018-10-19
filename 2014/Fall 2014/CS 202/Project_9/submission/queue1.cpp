//queue (stay) implementation

#include "queue.h"
#include <iostream>
using namespace std;

	Queue::Queue(int size)
	{

		//create array of specified size

		data = new int [size];

		//set max 

		max = size - 1;

		//set front and rear - no good data yet, so both -1

		front = -1;

		rear = -1;

	}

	Queue::Queue(const Queue &src)
	{

		//create a new array to hold the copied values

		data = new int [src.max + 1];

		//copy max

		max = src.max;

		//copy front and rear

		front = src.front;

		rear = src.rear;

		//copy the values in the src array into the new array

		for ( int index = 0 ; index < rear + 1 ; index++ )
			{

			data[index] = src.data[index];

			}

	}

	Queue::~Queue()
	{

		//deallocate data array

		delete [] data;

		//set pointer to null

		data = NULL;

	}

	Queue& Queue::operator=(const Queue &src)
	{

		//first, check to see if you're trying to assign a queue to itself

		if ( this != &src )
			{

			//if not, you're clear to copy the data

				//copy front and rear

				front = src.front;

				rear = src.rear;

				//if the sizes do not match, deallocate the old array and make a new one of the correct size

				if ( src.max != max )
					{

					max = src.max;
				
					delete [] data;

					data = new int [src.max + 1];

					}

				//copy the values in src array into dest array

				for ( int index = 0; index < rear + 1; index++ )
					{

					data[index] = src.data[index];

					}

			}

		//return "this" queue

		return (*this);

	}

	bool Queue::enqueue(int target)
	{

		//first, check to see if the array is full. if it's not full, you can enqueue
		
		if ( this->full() != true )
			{

			//set front to 0

			front = 0;

			//increment rear

			rear++;

			//add target value to the queue at rear

			data[rear] = target;

			//return true - specifies that enqueue succeeded

			return true;

			}

		//otherwise, could not enqueue because the array was full - return false

		else
			return false;

	}

	bool Queue::dequeue(int &value)
	{

		//first, check to ese if the array is empty. if it's not empty, you can dequeue

		if ( this->empty() != true )
			{

			//set the dequeued value to the reference parameter so user can retrieve it

			value = data[front];

			//shift the other values towards the front to occupy the empty space opened by the dequeue
			
			for ( int index = front + 1 ; index < rear + 1 ; index++ )
				{

				data[index - 1] = data[index];

				} 

			//decrement rear

			rear--;

			//if the only value in the array was just dequeued, set front back to -1 to keep it from pointing at garbage

			if ( rear == -1 )
				{

				front = -1;

				}

			//return true- specifies that dequeue succeeded

			return true;

			}

		//otherwise, the dequeue failed because the array was empty - return false

		else
			return false;

	}

	bool Queue::empty() const
	{

		//if the rear is at -1, the array is empty - return true

		if ( rear < 0 )
			{

			return true;

			}

		//otherwise, the array is not empty - return false

		else
			return false;

	}

	bool Queue::full() const
	{

		//if the rear is at max, the array is full - return true

		if ( rear == max )
			{

			return true;

			}

		//otherwise, the array is not full - return false

		else
			return false;

	}

	bool Queue::clear()
	{

		//check to see if the array isn't empty already

		if ( this->empty() != true )
			{

			//set front and rear back to -1; this effectively clears the array

			front = -1;

			rear = -1;

			//return true - indicates data was cleared

			return true;

			}

		//if the array was empty already, return false - indicates no data was cleared

		else
			return false;

	}

	bool Queue::operator==(const Queue &target) const
	{


		//if fronts/rears/maxes are not equal, return false

		if ( front != target.front )
			{

			return false;

			}

		if ( rear != target.rear )
			{

			return false;

			}

		if ( max != target.max )
			{

			return false;

			}

		//compare the valid items in the data array to see if they all match
		//Note: this loop will not fire if both queues are empty, so two empty queues will be considered equal

		for ( int index = 0; index < rear + 1; index++ )
			{

			//if valid values are not equal at any point, return false

			if ( data[index] != target.data[index] )
				{

				return false;

				}

			}

		//if all these checks passed, return true

		return true;

	}

	ostream& operator<< (ostream &out, const Queue &target)
	{

		//first, check to see if you're trying to print an empty array

		if ( target.empty() != true )
			{

			//print the valid values contained in the array

			for ( int index = 0; index < target.rear + 1; index++ )
				{

				//for values that aren't in the front or rear, just print the value

				if ( index != target.front && index != target.rear )
					{

					out << target.data[index];

					}
			
				//for the case where there is only one value, the front and the rear, print it surrounded by [| and |]

				if ( index == target.front && index == target.rear )
					{

					out << "[|" << target.data[index] << "|]";

					}

				//for a value at the front but not the rear, print it surrounded by square brackets

				if ( index == target.front && index != target.rear )
					{

					out << "[" << target.data[index] << "]";

					}

				//for a value at the rear but not the front, print it surrounded by pipes

				if ( index != target.front && index == target.rear )
					{

					out << "|" << target.data[index] << "|";

					}

				}

			//print endline

			cout << endl;

			}

		//if the array was empty, print a message

		else
			out << "Empty queue!" << endl;

		//return the ostream object
	
		return out;

	}	
