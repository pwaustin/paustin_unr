/**
@file main.cpp
@author Patrick Austin
@date 3/9/2015
*/

#include <iostream>
#include "sorts.h"
using namespace std;

	/** Conducts sorting operation for bubble sort - 10 iterations for values < 1 000 000, 
	1 iteration for values > 1 000 000. Conducts readin, sorts, and displays info to console.
	For reasons I was unable to resolve before submission, swaps and comparisons for
	the 100000 value analysis will return negative values due to integer overload. Short of
	including a third party BigInt library I was unable to resolve this issue, which seems
	to be partly OS/compiler based. My apologies; mercy please.	
	@pre Text files 1000.txt, 10000.txt, 100000.txt, 1000000.txt must exist and be formatted
	as specified.
	@post Sort info displayed to console.
	@param size The size of the data to be sorted - only 1000, 10000, 100000, 1000000
	supported.
	*/
  
void analyzeBubble(const int& size);

	/** Conducts sorting operation for merge sort - 10 iterations for all values. Conducts readin, 
	sorts, and displays info to console.
	@pre Text files 1000.txt, 10000.txt, 100000.txt, 1000000.txt must exist and be formatted
	as specified.
	@post Sort info displayed to console.
	@param size The size of the data to be sorted - only 1000, 10000, 100000, 1000000
	supported. */

void analyzeMerge(const int& size);

	/** Conducts sorting operation for counting sort - 10 iterations for all values. Conducts readin, 
	sorts, and displays info to console.
	@pre Text files 1000.txt, 10000.txt, 100000.txt, 1000000.txt must exist and be formatted
	as specified.
	@post Sort info displayed to console.
	@param size The size of the data to be sorted - only 1000, 10000, 100000, 1000000
	supported. */

void analyzeCounting(const int& size);

int main()
	{

	//print title

	cout << "CS 302 Project 4: Comparing Sorting Algorithms" << endl << endl;

	//test bubble sort

	cout << "Bubble sort analysis: " << endl << endl;

		//with 1 000 values

		analyzeBubble(1000);

		//with 10 000 values

		analyzeBubble(10000);

		//with 100 000 values

		analyzeBubble(100000);

		//with 1 000 000 values (will only do 1 iteration)

		analyzeBubble(1000000);

	//test merge sort

	cout << "Merge sort analysis: " << endl << endl;

		//with 1 000 values

		analyzeMerge(1000);

		//with 10 000 values

		analyzeMerge(10000);

		//with 100 000 values

		analyzeMerge(100000);

		//with 1 000 000 values

		analyzeMerge(1000000);

	//test counting sort

	cout << "Counting sort analysis: " << endl << endl;

		//with 1 000 values

		analyzeCounting(1000);

		//with 10 000 values

		analyzeCounting(10000);

		//with 100 000 values

		analyzeCounting(100000);

		//with 1 000 000 values

		analyzeCounting(1000000);

	//end program

	return 0;

	}

void analyzeBubble(const int& size)
	{

	//declare index

	int index;

	//declare sort object

	bubbleSort test;

	//if size < 1000000, analyze 10x

	if ( size < 1000000 )
		{

		//sort and reset 10 times

		for ( index = 0; index < 10; index++)
			{

			test.readin(size);
			test.sort(size);
	
			}

		//output summary info

		cout << size << " unsorted values (10 iterations): " << endl;

		cout << "Time: " << ( test.getTime() / 10 ) << " seconds" <<  endl;

		cout << "Comparisons: " << test.getComparisons() / 10 << endl;

		cout << "Swaps: " << test.getSwaps() / 10 << endl << endl;
	
		//sort the sorted data 10 times

		test.resetCounts();

		for ( index = 0; index < 10; index++ )
			{

			test.sort(size);

			}

		//output summary info

		cout << size << " sorted values (10 iterations): " << endl;

		cout << "Time: " << ( test.getTime() / 10 ) << " seconds" <<  endl;

		cout << "Comparisons: " << ( test.getComparisons() / 10 ) << endl;

		cout << "Swaps: " << ( test.getSwaps() / 10 ) << endl << endl;

		}

	//if size > 1000000, only analyze once

	else
		{

		//read in and sort

		test.readin(size);
		test.sort(size);

		//output summary info

		cout << size << " unsorted values (1 iteration): " << endl;

		cout << "Time: " << test.getTime() << " seconds" << endl;

		cout << "Comparisons: " << test.getComparisons() << endl;

		cout << "Swaps: " << test.getSwaps() << endl << endl;

		//sort the sorted data

		for ( index = 0; index < 10; index++ )
			{

			test.resetCounts();
			test.sort(size);

			}

		//output summary info

		cout << size << " sorted values (10 iterations): " << endl;

		cout << "Time: " << ( test.getTime() / 10 ) << " seconds" <<  endl;

		cout << "Comparisons: " << ( test.getComparisons() / 10 ) << endl;

		cout << "Swaps: " << ( test.getSwaps() / 10 ) << endl << endl;

		}

	}

void analyzeMerge(const int& size)
	{

	int index;

	mergeSort test;

	//sort and reset 10 times

	for ( index = 0; index < 10; index++)
		{

		test.readin(size);

		test.timeSort(0, size);

		}

	//output summary info

	cout << size << " unsorted values (10 iterations): " << endl;

	cout << "Time: " << ( test.getTime() / 10 ) << " seconds" << endl;

	cout << "Comparisons: " << ( test.getComparisons() / 10 ) << endl;

	cout << "Swaps: " << ( test.getSwaps() / 10 ) << endl << endl;

	//sort the sorted data 10 times

	test.resetCounts();

	for ( index = 0; index < 10; index++ )
		{

		test.timeSort(0, size);

		}

	//output summary info

	cout << size << " sorted values (10 iterations): " << endl;

	cout << "Time: " << ( test.getTime() / 10 ) << " seconds" << endl;

	cout << "Comparisons: " << ( test.getComparisons() / 10 ) << endl;

	cout << "Swaps: " << ( test.getSwaps() / 10 ) << endl << endl;

	}

void analyzeCounting(const int& size)
	{

	int index;

	countingSort test;

	//sort and reset 10 times

	for ( index = 0; index < 10; index++)
		{

		test.readin(size);
		test.sort(size);

		}

	//output summary info

	cout << size << " unsorted values (10 iterations): " << endl;

	cout << "Time: " << ( test.getTime() / 10 ) << " seconds" <<  endl;

	cout << "Comparisons: " << ( test.getComparisons() / 10 ) << endl;

	cout << "Swaps: " << ( test.getSwaps() / 10 ) << endl << endl;

	//sort the sorted data 10 times

	test.resetCounts();

	for ( index = 0; index < 10; index++ )
		{

		test.sort(size);

		}

	//output summary info

	cout << size << " sorted values (10 iterations): " << endl;

	cout << "Time: " << ( test.getTime() / 10 ) << " seconds" <<  endl;

	cout << "Comparisons: " << ( test.getComparisons() / 10 ) << endl;

	cout << "Swaps: " << ( test.getSwaps() / 10 ) << endl << endl;

	}
