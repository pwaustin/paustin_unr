/** CS 302 Project 7 - scheduling with red black trees, main program for scheduling
@file main.cpp
@author Patrick Austin
@date 4/29/2015 */

#include "intervalTree.h"
#include <iostream>
#include <fstream>
using namespace std;

/** Readin function. Reads correctly formatted data from "data.txt" into target interval tree. Reads 10
intervals by default.
@pre Datafile is correctly formatted.
@post Intervals read into the interval tree.
@param target The interval tree into which the values should be inserted.
@return None. */

void readin ( IntervalTree& target );

int main()
	{

	//print title

		cout << "CS 302 Project 7: Interval Tree Testing Program" << endl << endl;

	//read in data from file

		cout << "Reading data from 'data.txt' into the interval tree..." << endl << endl;

		IntervalTree test1;

		readin ( test1 );

	//print preorder traversal

		cout << "Printing preorder traversal of the interval tree..." << endl << endl;

		test1.preorderTraverse();

		cout << endl;
	
	//prompt user for an interval to search for

		cout << "Initializing interval search..." << endl << endl;

		int start;

		int end;

		cout << "Enter start value of desired interval: " ;
	
		cin >> start;

		cout << endl;

		cout << "Enter end value of desired interval: " ;

		cin >> end;
	
		cout << endl;

	//search the interval tree for an overlapping interval

		cout << "Searching for overlapping interval..." << endl << endl;

		bool success;

		int foundS;

		int foundE;

		success = test1.search(start, end, foundS, foundE);

		if ( !success )
			cout << "No overlapping interval found." << endl << endl;

		else
			cout << "Overlapping interval found with start of " << foundS << " and end of " << foundE << "." << endl << endl;

	//print end title

		cout << "Ending CS 302 Project 7: Interval Tree Testing Program..." << endl << endl;

	//end program

		return 0;

	}

void readin ( IntervalTree& target )
	{

	ifstream fin;
	int start;
	int end;

	fin.open("data.txt");

	for ( int index = 0; index < 10; index++ )
		{

		fin >> start;
		fin >> end;

		target.add(start, end);

		cout << "Reading in interval with start = " << start << " and end = " << end << " ..." << endl;

		}

	cout << endl;

	fin.close();

	}
