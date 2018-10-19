/* CS 477 Homework 3 Programming Problems
Patrick Austin
9/26/2016 

NOTE: this program concerns problems 1a. and 3 of the homework. The other 
problems are solved in the attached document, which was also submitted as the hard copy.*/

#include <iostream>
#include <cstdlib>
using namespace std;

/*findMaxIndex: Uses a divide and conquer strategy to find the position of the 
largest element in target array. Uses console output to display operation to user.

@param data The target array.
@param search_start The position of the first element to be considered.
@param search_end The position of the last element to be considered.

*/

template <typename ItemType>
int findMaxIndex( ItemType* data, int search_start, int search_end );

/*negBeforePos: rearranges an array of real numbers such that all the negative 
numbers come before the positive ones.

@param data The target array.
@param data_start The position of the first element to be considered.
@param data_end The position of the last element to be considered.

*/

template <typename ItemType>
void negBeforePos( ItemType* data, int data_start, int data_end );

int main()
{

//run the algorithms on the specified arrays and spit output to console

cout << "Welcome to Patrick's CS 477 Homework 3 Testing Program" << endl << endl;

int testArrayOne[] = {1, 4, 9, 3, 4, 9, 5, 6, 9, 3, 7};
int testArrayTwo[] = {4, -3, 9, 8, 7, -4, -2, -1, 0, 6, -5};
int testOneResult;

//testing algorithm 1

cout << "Testing findMaxIndex on specified array..." << endl << endl;

testOneResult = findMaxIndex ( testArrayOne, 0, 10 );

cout << endl << "Test complete. Max index found at " << testOneResult << "." << endl << endl;

//testing algorithm 2

cout << "Testing negBeforePos on specified array..." << endl << endl;

negBeforePos( testArrayTwo, 0, 10 );

cout << "Test complete. After sorting, the array contains: " << endl << endl;

for (int index = 0; index != 11; index++ )
	cout << testArrayTwo[index] << " ";

//tests complete, end program

cout << endl << endl << "Testing complete, exiting program... " << endl;

return 0;
}

template <typename ItemType>
int findMaxIndex( ItemType* data, int search_start, int search_end )
{

//declare variables

int leftResult;
int rightResult;
int median;

//base case: if considering one element, just return the current index

if ( search_start == search_end )
	{

	cout << "Base case reached: returning index " << search_start << " with value " << data[search_start] << endl;

	return search_start;

	}
//recursive case

else
	{

	//calculate the median

	median = ( search_start + search_end ) / 2;

	//recursive call: get max index from the start to the median

	cout << "New call: Finding index of max between " << search_start << " and " << median << endl;

	leftResult = findMaxIndex ( data, search_start, median);

	//recursive call: get max index from median + 1 to the end

	cout << "New call: Finding index of max between " << (median + 1) << " and " << search_end << endl; 

	rightResult = findMaxIndex ( data, median + 1, search_end );

	//return the larger of the values

	if ( data[leftResult] >= data[rightResult] )
		{
		
		cout << data[leftResult] << " at index " << leftResult << " >= " 
		<< data[rightResult] << " at index " << rightResult << 
		". Therefore returning " << leftResult << endl;

		return leftResult;

		}
	else
		{

		cout << data[rightResult] << " at index " << rightResult << " > " 
		<< data[leftResult] << " at index " << leftResult << 
		". Therefore returning " << rightResult << endl;

		return rightResult;

		}
	}

}

template <typename ItemType>
void negBeforePos ( ItemType* data, int data_start, int data_end )
{

//declare variables

int startIndex = data_start;
int endIndex = data_end;
int swapTemp;

//stop when the two indices cross

while ( startIndex <= endIndex )
	{

	//if the element at the left index is a negative number, its location is fine. Increment left index and move on

	if ( data[startIndex] < 0 )
		startIndex++;

	//otherwise, the value at left index needs to be swapped with the value at right index. 
	//Now the value at right index is fine, so decrement right index and move on 
	
	else
		{

		swapTemp = data[startIndex];
		data[startIndex] = data[endIndex];
		data[endIndex] = swapTemp;

		endIndex--;

		}

	}

}
