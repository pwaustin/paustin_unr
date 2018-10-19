/**
@file merge.cpp
@author Patrick Austin
@date 3/9/2015
*/

#include <algorithm>
#include <ctime>
#include <fstream>
#include "sorts.h"
using namespace std;

	/** Merge sort class constructor. Initializes count and time analysis values to 0.
	@pre None.
	@post Object created with time, comparisons, swaps = 0 */

mergeSort::mergeSort()
	{

	time = 0;

	comparisons = 0;

	swaps = 0;

	}

	/** Merge sort timeSort function. Sorts the values in the arr data member of the class
	by calling the sort function. Tracks the time the sort operation takes.
	Timing operation coded for Linux.
	@pre first <= last
	@post Array values [first..last] sorted into ascending order, time of operation 
		stored in time double. data member.
	@param first The index of the first element to be sorted.
	@param last The index of the last element to be sorted. */

void mergeSort::timeSort ( const int& first, const int& last)
	{

	//start clock
	clock_t start = clock();

	//sort the values
	sort(first, last);

	//end clock, add the time to the time data member
	clock_t finish = clock();

	time += static_cast<double>( finish - start ) / CLOCKS_PER_SEC;

	}

	/** Recursively merge sorts arr data member of mergeSort class, from first
	element to last. Tracks time of operation, number of swaps, number of comparisons.
	!!! ADAPTED FROM POWERPOINT SLIDE CODE !!!
	@pre   first <= last
	@post Array values[first..last] sorted into ascending order. 
	@param first The index of the first element to be sorted.
	@param last The index of the last element to be sorted. */

void mergeSort::sort ( const int& first, const int& last )		
	{

	if  ( first < last ) 	           //  general case
		{	

                int  middle = ( first  +  last ) / 2;
		sort ( first, middle );	
		sort ( middle + 1, last );

		// now  merge two subarrays
		// values [ first . . . middle ] with 
		// values [ middle + 1,  . . . last ].

		merge(first, middle, last);

		}

	}

	/** Merges two sorted array segments theArray[first..mid] and
	theArray[mid+1..last] into one sorted array.
	Tracks time of operation, number of swaps, number of comparisons.
	There seems to be a bug in this method when run with 1000000 values
	where a small number of values are erroneously swapped when sorting an
	already sorted array. I was not able to ascertain why this happens,
	but even if I could I am not allowed to modify the sorting algorithm's 
	code for this project. For 1000, 10000, and 100000 values the algorithm 
	appears to work correctly in the specified circumstances. 
	In order to prevent running out of memory on my system when
	analyzing 1 000 000 values, tempArray had to be changed from a static array 
	to a dynamic one. This does not strike me as an unreasonable adaptation, 
	but if it strikes you as unreasonable then please show mercy.
	!!! ADAPTED FROM TEXTBOOK CODE !!!
	@pre first <= mid <= last. The subarrays theArray[first..mid] and
	theArray[mid+1..last] are each sorted in increasing order.
	@post arr[first..last] is sorted.
	@param first The index of the beginning of the first segment in
	theArray.
	@param mid The index of the end of the first segment in theArray;
	mid + 1 marks the beginning of the second segment.
	@param last The index of the last element in the second segment in
	theArray.
	@note This function merges the two subarrays into a temporary
	array and copies the result into the original array theArray. */

void mergeSort::merge (const int& first, const int& mid, const int& last)
	{

	  int* tempArray = new int [MAX_VALUES];	// Temporary array
	// Initialize the local indices to indicate the subarrays
	  int first1 = first;		// Beginning of first subarray
	  int last1 = mid;		// End of first subarray
	  int first2 = mid + 1;		// Beginning of second subarray
	  int last2 = last;		// End of second subarray
	// While both subarrays are not empty, copy the
	// smaller item into the temporary array
	  int index = first1;		// Next available location in tempArray
	  while ((first1 <= last1) && (first2 <= last2))
	    {
	//increment comparisons
	      comparisons++;
	// At this point, tempArray[first..index-1] is in order
	      if (arr[first1] <= arr[first2])
		{
		  tempArray[index] = arr[first1];
		  first1++;
		}
	      else
		{
		  tempArray[index] = arr[first2];
		  first2++;
		//increment swaps
		  swaps++;
		}			// end if
	      index++;
	    }				// end while
	// Finish off the first subarray, if necessary
	  while (first1 <= last1)
	    {
	// At this point, tempArray[first..index-1] is in order
	      tempArray[index] = arr[first1];
	      first1++;
	      index++;
	    }				// end while
	// Finish off the second subarray, if necessary
	  while (first2 <= last2)
	    {
	// At this point, tempArray[first..index-1] is in order
	      tempArray[index] = arr[first2];
	      first2++;
	      index++;
	    }				// end for
	// Copy the result back into the original array
	  for (index = first; index <= last; index++)
	    arr[index] = tempArray[index];

	//clear dynamic memory
	delete [] tempArray;

	}				// end merge

	/** Merge sort readin function. Reads in random data of specified
	size to sort.
	@pre Extant and correctly formatted text files 1000.txt,
	10000.txt, 100000.txt, 1000000.txt, size paramter = 1000, 10000, 100000,
	1000000
	@post Mergesort array filled with read in values from 0 to size
	@param size The size of the data to be read in. Only sizes of 1000, 
	10000, 100000, and 1000000 are supported in this implementation! */

void mergeSort::readin(const int& size)
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

	/** Merge sort getTime function. Returns time data member, used to track time spent sorting.
	@pre None.
	@post Time returned; value unchanged.*/

double mergeSort::getTime() const
	{

	return time;

	}

	/** Merge sort getComparisons function. Returns comparisons data member, tracking number of
	comparisons carried out during sorting.
	@pre None.
	@post Comparisons returned; value unchanged.*/

int mergeSort::getComparisons() const
	{

	return comparisons;

	}

	/** Merge sort getSwaps function. Returns swaps data member, tracking number of
	swaps carried out during sorting.
	@pre None.
	@post Swaps returned; value unchanged.*/

int mergeSort::getSwaps() const
	{

	return swaps;

	}

	/** Merge sort resetCounts function. Resets time, comparisons, and swaps values to 0
	if user wishes to reset the tracking of the sorting algorithm that has happened so far.
	@pre None.
	@post Time, comparisons, swaps set to 0. */

void mergeSort::resetCounts()
	{

	time = 0;

	comparisons = 0;

	swaps = 0;

	}
