/**
@file counting.cpp
@author Patrick Austin
@date 3/9/2015
*/

#include <algorithm>
#include <ctime>
#include <fstream>
#include "sorts.h"
using namespace std;

	/** Counting sort class constructor. Initializes count and time analysis values to 0.
	@pre None.
	@post Object created with time, comparisons, swaps = 0 */

countingSort::countingSort()
	{

	time = 0;

	comparisons = 0;

	swaps = 0;

	}

	/** Counting sort sort function. Sorts values in arr data member from 0 to size into
	ascending order using counting sort. Tracks time of operation, number of
	comparisons, number of swaps.
	Time operation coded in Linux.
	!!! ADAPTED FROM POWERPOINT SLIDE CODE!!!
	@pre size > 0
	@post Values sorted from 0 to size
	@param size The size of the array to be sorted. */

void countingSort::sort(const int& size)
	{

	//start clock

	clock_t start = clock();

	//declare index

	int index;

	//create array of counts, initialize all values to 0

	int* tempArr = new int [1000000];

	//create destination array of same size as source array

	int* destArr = new int [size];

	//set all values in the array of counts to 0

	for ( index = 0; index < 1000000; index++ )
		{
		tempArr[index] = 0;
		}

	//go through the source array, counting the incidence of each value in the temp array

	for ( index = 0; index < size; index++ )
		{

		tempArr[ arr[index] ]++;

		}

	//go through the temp array, setting each value to += the previous value

	for ( index = 1; index < 1000000; index++ )
		{
		
		tempArr[index] += tempArr[index-1];

		}

	//now go down tempArray, copying values into destArray - the result will be destArray sorted correctly

	for ( index = size - 1; index != 0 ; index-- )
		{

		destArr[ tempArr[ arr[index] ] ] = arr[index];

		tempArr[ arr[index] ]--;
		
		}

	//copy destArray's values back into the original array

	for ( index = 0; index < size; index++ )
		{

		arr[index] = destArr[index];

		}

	//deallocate dynamic memory

	delete [] tempArr;

	delete [] destArr;

	//end clock, add the time to the time data member. there are no comparisons or swaps
	clock_t finish = clock();

	time += static_cast<double>( finish - start ) / CLOCKS_PER_SEC;

	}

	/** Counting sort readin function. Reads in random data of specified
	size to sort.
	@pre Extant and correctly formatted text files 1000.txt,
	10000.txt, 100000.txt, 1000000.txt, size paramter = 1000, 10000, 100000,
	1000000
	@post Countingsort array filled with read in values from 0 to size
	@param size The size of the data to be read in. Only sizes of 1000, 10000, 
	100000, and 1000000 are supported in this implementation! */

void countingSort::readin(const int& size)
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

	/** Counting sort getTime function. Returns time data member, used to track time spent sorting.
	@pre None.
	@post Time returned; value unchanged.*/

double countingSort::getTime() const
	{

	return time;

	}

	/** Counting sort getComparisons function. Returns comparisons data member, tracking number of
	comparisons carried out during sorting. Always returns 0, counting sort does no comparisons.
	@pre None.
	@post Comparisons returned; value unchanged.*/

int countingSort::getComparisons() const
	{

	return comparisons;

	}

	/** Bubble sort getSwaps function. Returns swaps data member, tracking number of
	swaps carried out during sorting. Always returns 0, counting sort does not sort by swapping values per se.
	@pre None.
	@post Swaps returned; value unchanged.*/

int countingSort::getSwaps() const
	{

	return swaps;

	}

	/** Counting sort resetCounts function. Resets time, comparisons, and swaps values to 0
	if user wishes to reset the tracking of the sorting algorithm that has happened so far.
	@pre None.
	@post Time, comparisons, swaps set to 0. */

void countingSort::resetCounts()
	{

	time = 0;

	comparisons = 0;

	swaps = 0;

	}
