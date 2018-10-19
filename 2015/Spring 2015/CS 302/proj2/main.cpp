/** CS 302 Project 2 - test program for ksmall class
@file main.cpp
@author Patrick Austin
@date 2/9/2015 */

#include "ksmall.h"
#include <iostream>
#include <cstdlib>
using namespace std;

//global constant for testing size. Edit to run the test for an array of a different size. Must be greater than 0.

const int TEST_SIZE = 100;


/** Main function for testing the ksmall class. Creates a ksmall object with an array of TEST_SIZE elements, displays it,
prompts the user for a valid k value for which to seek the k-th smallest element, outputs the array after the ksmall
search operation has been conducted on it, and informs the user what the k-th smallest value was.
@pre Correctly implemented ksmall class included.
@post As above. No file I/O is conducted.
@return None. */

int main()
	{

	//print title

	cout << "CS 302 Project 2: ksmall Testing Program" << endl << endl;

	//create a ksmall object with TEST_SIZE values

	ksmall test(TEST_SIZE);

	//print data before algorithm

	cout << "Data before sort:" << endl << endl;

	test.display();

	//prompt the user for a target "k" value. Prompt until a valid k is entered

	int target = 0;

	while ( target <= 0 || target > TEST_SIZE )
		{

		cout << "Enter k, and the algorithm will seek the k-th smallest value. Value must be greater than or equal to 1, but less than or equal to " << TEST_SIZE << ": ";

		cin >> target;

		cout << endl;

		}

		cout << "The algorithm is seeking the k-th smallest value in the array for k = " << target << "..." << endl << endl;

	//run the algorithm

	int result = test.search(target, 0, TEST_SIZE - 1);

	//print output to screen

	cout << "Data after sort:" << endl << endl;

	test.display();
		
	//inform the user what the k-th smallest value was

	cout << "For k = " << target << " , the k-th smallest value in the array was " << result << endl << endl;

	//end program

	return 0;

	}

