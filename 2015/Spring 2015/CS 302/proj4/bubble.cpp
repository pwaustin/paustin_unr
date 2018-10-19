/**
@file bubble.cpp
@author Patrick Austin
@date 3/9/2015
*/

#include <algorithm>
#include <ctime>
#include <fstream>
#include "sorts.h"
using namespace std;

	/** Bubble sort class constructor. Initializes count and time analysis values to 0.
	@pre None.
	@post Object created with time, comparisons, swaps = 0 */

bubbleSort::bubbleSort()
	{

	time = 0;

	comparisons = 0;

	swaps = 0;

	}

	/** Sorts the items in an array into ascending order using bubble sort.
	Tracks time of operation, number of swaps, number of comparisons.
	Expect extremely long runtime with 1000000 values.
	Time operation coded for Linux.
	!!! ADAPTED FROM POWERPOINT SLIDE CODE !!!
	@pre None.
	@post theArray is sorted into ascending order; n is unchanged.
	@param n The size of theArray. */

void bubbleSort::sort(const int& numValues)
	{

	//start counting time

	clock_t start = clock();

	//sort to completion

	  int current = 0;

	  bool sorted = false;

	  while (current < numValues-1 && ! sorted)
	  {
	    bubbleUp( current, numValues-1, sorted);
	    current++;
	  }

	//finish counting time

	clock_t finish = clock();

	time += static_cast<double>( finish - start ) / CLOCKS_PER_SEC;

	}

	/** bubbleSort bubbleUp function. Called by the sort function to loop
	through the array, conducting comparisons and swaps as needed. Tracks
	comparisons and swaps, as specified in the prompt.
	!!! ADAPTED FROM POWERPOINT SLIDE CODE !!!
	@pre Comparable data between startIndex and endIndex.
	@post One 'bubble up' completed, if possible.
	@param startIndex The first value to be compared.
	@param endIndex The last value to be compared.
	@bool sorted Bool used in internal bubble sort operations to help the
	sort terminate early if possible.*/

void bubbleSort::bubbleUp( const int& startIndex, const int& endIndex, bool& sorted)
	{

	  sorted = true;

	  for (int index = endIndex; index > startIndex; index--)
		{
		//increment comparisons
		comparisons++;

	    	if (arr[index] < arr[index-1])
			{
	      		swap(arr[index], arr[index-1]);
			sorted = false;
			//increment swaps
			swaps++;
			}
	
		}

	}

	/** Bubble sort readin function. Reads in random data of specified
	size to sort.
	@pre Extant and correctly formatted text files 1000.txt,
	10000.txt, 100000.txt, 1000000.txt, size parameter = 1000, 10000, 100000,
	1000000
	@post Bubblesort array filled with read in values from 0 to size
	@param size The size of the data to be read in. Only sizes of 1000, 10000,
	100000, and 1000000 are supported in this implementation! */

void bubbleSort::readin(const int& size)
	{

	//create fstream object

	ifstream fin;

	//determine which input file to open

	if ( size == 1000 )
		{

		fin.open("1000.txt");

		}

	else if ( size == 10000 )
		{

		fin.open("10000.txt");

		}

	else if ( size == 100000 )
		{

		fin.open("100000.txt");

		}

	else if ( size == 1000000 )
		{

		fin.open("1000000.txt");

		}

	//read in data from this file

	for ( int index = 0; index < size; index++ )
		{

		fin >> arr[index];

		}

	//close input file

	fin.close();

	}

	/** Bubble sort getTime function. Returns time data member, used to track time spent sorting.
	@pre None.
	@post Time returned; value unchanged.*/

double bubbleSort::getTime() const
	{

	return time;

	}

	/** Bubble sort getComparisons function. Returns comparisons data member, tracking number of
	comparisons carried out during sorting.
	@pre None.
	@post Comparisons returned; value unchanged.*/

int bubbleSort::getComparisons() const
	{

	return comparisons;

	}

	/** Bubble sort getSwaps function. Returns swaps data member, tracking number of
	swaps carried out during sorting.
	@pre None.
	@post Swaps returned; value unchanged.*/

int bubbleSort::getSwaps() const
	{

	return swaps;

	}

	/** Bubble sort resetCounts function. Resets time, comparisons, and swaps values to 0
	if user wishes to reset the tracking of the sorting algorithm that has happened so far.
	@pre None.
	@post Time, comparisons, swaps set to 0. */

void bubbleSort::resetCounts()
	{

	time = 0;

	comparisons = 0;

	swaps = 0;

	}
