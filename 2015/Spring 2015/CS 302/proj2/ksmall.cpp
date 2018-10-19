/** CS 302 Project 2 - implementation for ksmall sort class
@file ksmall.cpp
@author Patrick Austin
@date 2/9/2015 */

#include <ctime>
#include <cstdlib>
#include <iostream>
#include "ksmall.h"
using namespace std;


		/** Constructor for ksmall class object. Takes user specified value to determine the size of the array. Randomizes
		all values in the array between 0-999.
		@param value The size of the array that will be generated and randomized.
		@pre Value must be greater than 0 to generate an array with data to sort.
		@post ksmall object will have been created with size = value, with a randomized int in each element.
		@return None. */

		ksmall::ksmall(const int value)
			{

			//make an array of the specified size

			size = value;

			data = new int [size];

			//randomize the values in each element of the array

				//seed random number generator

				srand( time(NULL) );

				//assign random values to each element from 0-999

				for ( int index = 0 ; index != size; index++ )
					{

					data[index] = rand() % 1000;

					}

			}

		/** Destructor for ksmall class object. Deallocates data from the array created in the constructor, returning the memory to the system.
		@pre None.
		@post None.
		@return None. */

		ksmall::~ksmall()
			{

			//deallocate the data

			delete [] data;

			}

		/** ksmall search function; finds the k-th smallest element in the ksmall object's data array, where k = target.
		@param 	target The function finds the k-th smallest value in the array, where k = target.
		@param	first The first value that will be searched in the array.
		@param	last The last value that will be searched in the array.
		@pre Target must be greater than or equal to 1. First must be greater than or equal to 0. Last must be greater than or equal to first.
		@post the ksmall object's array will be partially sorted such that all elements less than or equal to target - 1 will be sorted in ascending order.
		@return The k-th smallest value in the array, where k = target. */

		int ksmall::search(const int target, const int first, const int last)
			{
	
			//the first value will be the pivot

			int pivot = first;

			//lowestSoFar will begin holding the value in the pivot. lowestLoc will be used to remember where the lowest value so far was found, if a lower one is found

			int lowestSoFar = data[pivot];
			int lowestLoc;

			//make a temp bool to detect if a swap needs to be made

			bool swap = false;

			//now search for the smallest value in the array after the pivot

			for ( int index = first + 1; index <= last; index++ )

				{

				//compare each analyzed value to the lowest value found so far

				if ( data[index] < lowestSoFar )
					{

					//if you find a lower value, remember it and remember its location

					lowestSoFar = data[index];

					lowestLoc = index;

					//set the swap flag to true

					swap = true;

					}

				}

			//swap the values at the index holding the lowest item with the pivot, unless the pivot was already the lowest value

			if ( swap )
				{

				data[lowestLoc] = data[pivot];

				data[pivot] = lowestSoFar;

				}

			//now determine what, if any, additional recursion needs to happen

				//base case: if target = pivot+1 (ie the k-th smallest value was just found), return the value, the recursion is finished

				if ( target == pivot + 1 )
					{

					return data[pivot];

					}

				//otherwise, search the array again using first + 1 as the beginning of the array - will get closer to the base case

				else
					{

					search ( target, first + 1, last );

					}

	
			}

		/** Display function for ksmall class object. Prints formatted contents of data array to console so user can see the data before and after the ksmall
		search function has been run on it.
		@pre None.
		@post Contents of ksmall data array are printed to consle in a formatted fashion. Contents of array are unchanged.
		@return None. */

		void ksmall::display() const
			{

			//print each value with appropriate spacing, 10 to a line

			for ( int index = 0; index < size; index++ )
				{

				if ( data[index] >= 100 )
					{

					cout << data[index] << " ";

					}

				if ( data[index] < 100 && data[index] >= 10 )
					{

					cout << data[index] << "  ";

					}

				if ( data[index] < 10 )
					{

					cout << data[index] << "   ";

					}

				if ( (index + 1) % 10 == 0 )
					{

					cout << endl;

					}

				}

				cout << endl;

			}


