/* CS 477 Homework 4 Programming Problems
Patrick Austin
10/2/2016 

NOTE: this program concerns problems 2 of the homework. The other 
problems are solved in the attached document, which was also submitted as the hard copy.*/

#include <iostream>
#include <cstdlib>
#include <algorithm>
using namespace std;

/*numberInRange: given an array of ints with range arrayMin to arrayMax, returns the number of values
in the array that fall in the range of rangeMin to rangeMax. Assumes array values >= 0. Returns -1 if 
rangeMin is greater than rangeMax or arrayMin is greater than arrayMax.

@param data The target array.
@param arrayMin the index of the first value in the array to be considered.
@param arrayMax the index of the final value in the array to be considered.
@param rangeMin the lower bound of the range to be considered.
@param rangeMax the upper bound of the range to be considered. */

int numberInRange ( int* data, int arrayMin, int arrayMax, int rangeMin, int rangeMax );

int main()
	{

	//run the algorithms on the specified array and spit output to console

	cout << "Welcome to Patrick's CS 477 Homework 4 Testing Program" << endl << endl;
	
	int result;
	int testArray[] = {5, 6, 9, 4, 4, 2, 2, 9, 5, 3, 4, 0, 1, 8, 5, 3, 8, 7};

	cout << "Testing how many elements in the specified array fall in the range of 2 to 7..." << endl << endl;
	
	result = numberInRange ( testArray, 0, 17, 2, 7 );

	cout << result << " value(s) fall in the range of 2 to 7." << endl << endl;

	//test complete, end program

	cout << "Testing complete, exiting program... " << endl;

	return 0;

	}

int numberInRange ( int* data, int arrayMin, int arrayMax, int rangeMin, int rangeMax )
	{

	//if array or range min > max, no processing needed. Return an error value

	if ( rangeMin > rangeMax || arrayMin > arrayMax )
		return -1;

	//create an array of size 0-max value in data array. Uses std::max_element method

	int maxValue = *max_element ( data, data + arrayMax ) ;

	int counts[ maxValue ];

	//zero out the values in the new array

	for ( int i = 0; i <= maxValue; i++ )
		counts[i] = 0;

	//c[i] will contain the number of elements equal to i in data

	for ( int j = 0; j <= arrayMax; j++ )
		counts[data[j]]++;
	
	//c[i] will contain the number of elements <= to i in data

	for ( int k = 1; k <= maxValue; k++ )
		counts[k] = counts[k] + counts[k-1];

	//the final range will be the number of values <= to rangeMax minus the number of values <= rangeMin - 1

	return counts[rangeMax] - counts[rangeMin - 1];

	}
