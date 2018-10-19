//queue (wrap) implementation

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

				//copy the values in src array into dest array - two cases, full array or no

					//see if the array is full

					if ( src.full() == true )
						{

						//if it's full, then copy max + 1 values, wrapping around if necessary

						for ( int index = src.front ; index < src.front + src.max + 1 ; index++ )
							{

							data[index%(src.max+1)] = src.data[index%(src.max+1)];

							}

						}

				//if the array isn't full, print the values starting from front, and continue, wrapping around if necessary, up to and including rear
				//note: this logic works for every situation except a full array, hence the division between the two cases in this code

				else
					{

					for ( int index = src.front; (index)%(src.max+1) != (src.rear+1)%(src.max+1) ; index++ )
						{

						data[index%(src.max+1)] = src.data[index%(src.max+1)];

						}

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

			//if this is the first item added to the queue, set front to 0

			if ( front == -1 )
				{

				front = 0;

				}

			//increment rear - use modulo operator to wrap-around as specified

			rear = ( rear + 1 ) % ( max + 1 );

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

			//if front and rear point to the same location, you're dequeuing the last good value. reset front and rear to -1

			if ( front == rear )
				{

				front = -1;

				rear = -1;

				}

			//otherwise, dequeue as normal

			else
				{

				//increment front - use modulo operator to wrap-around as specified

				front = ( front + 1 ) % ( max + 1 );

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

		//if rear + 1 (accounting for wrap-around) equals front, the array is full

		if ( (rear + 1) % (max + 1) == front )
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

		//if front/rear/max are not equal, return false

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

		//compare the good values - two cases, full array or no

			//see if the array is full

			if ( target.full() == true )
				{

				//if it's full, then compare max + 1 values, wrapping around if necessary

				for ( int index = target.front ; index < target.front + target.max + 1 ; index++ )
					{

					//if values being compared do not match at any point, return false

					if ( data[index%(max+1)] != target.data[index%(max+1)] )
						{

						return false;

						}

					}

				}

			//if the array isn't full, compare the values starting from front, and continue, wrapping around if necessary, up to and including rear
			//note: this logic works for every situation except a full array, hence the division between the two cases in this code

			else
				{

				for ( int index = target.front; (index)%(target.max+1) != (target.rear+1)%(target.max+1) ; index++ )
					{

					//if values being compared do not match at any point, return false

					if ( data[index%(max+1)] != target.data[index%(max+1)] )
						{

						return false;

						}

					}

				}

		//if everything matched, return true

		return true;

	}

	ostream& operator<< (ostream &out, const Queue &target)
	{

		//first, check to see if you're trying to print an empty array

		if ( target.empty() != true )
			{

			//next, see if the array is full

			if ( target.full() == true )
				{

				//if it's full, then print max + 1 values, wrapping around if necessary

				for ( int index = target.front ; index < target.front + target.max + 1 ; index++ )
					{

					//for values that aren't in the front or rear, just output the value

					if ( index%(target.max+1) != target.front && index%(target.max+1) != target.rear )
						{

						out << target.data[index%(target.max+1)];

						}
			
					//for the case where there is only one value, the front and the rear, print it surrounded by [| and |]

					if ( index%(target.max+1) == target.front && index%(target.max+1) == target.rear )
						{

						out << "[|" << target.data[index%(target.max+1)] << "|]";

						}

					//for a value at the front but not the rear, print it surrounded by square brackets

					if ( index%(target.max+1) == target.front && index%(target.max+1) != target.rear )
						{

						out << "[" << target.data[index%(target.max+1)] << "]";

						}

					//for a value at the rear but not the front, print it surrounded by pipes

					if ( index%(target.max+1) != target.front && index%(target.max+1) == target.rear )
						{

						out << "|" << target.data[index%(target.max+1)] << "|";

						}

					}

				}

				//if the array is neither empty nor full, print the values starting from front, and continue, wrapping around if necessary, up to and including rear
				//note: this logic works for every situation except a full array, hence the division between the two cases in this code
				
				else
					{

					for ( int index = target.front; (index)%(target.max+1) != (target.rear+1)%(target.max+1) ; index++ )
						{

						//for values that aren't in the front or rear, just output the value

						if ( index%(target.max+1) != target.front && index%(target.max+1) != target.rear )
							{

							out << target.data[index%(target.max+1)];

							}
			
						//for the case where there is only one value, the front and the rear, print it surrounded by [| and |]

						if ( index%(target.max+1) == target.front && index%(target.max+1) == target.rear )
							{

							out << "[|" << target.data[index%(target.max+1)] << "|]";

							}

						//for a value at the front but not the rear, print it surrounded by square brackets

						if ( index%(target.max+1) == target.front && index%(target.max+1) != target.rear )
							{

							out << "[" << target.data[index%(target.max+1)] << "]";

							}

						//for a value at the rear but not the front, print it surrounded by pipes

						if ( index%(target.max+1) != target.front && index%(target.max+1) == target.rear )
							{

							out << "|" << target.data[index%(target.max+1)] << "|";

							}

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
