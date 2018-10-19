

        /***************************************************************/

        /* PROGRAM: project11.cpp

        /*                                                                                       */

        /* AUTHOR: Patrick Austin

        /*                                                                                       */

        /* DATE: 11/25/2014

        /*                                                                                      */

        /* REVISIONS: N/A

        /*                                                                                      */

        /* PURPOSE: Reads in a data file of integers provided by user. Sorts the integers in a linked list.
		Translates the linked list into an array based list. Prompts user for a search value, and then
		searches the sorted list for that value. Returns index of item, if found, to user.

        /*                                                                                      */

        /**************************************************************/


//header files

#include "listA.h"
#include "listN.h"
#include <iostream>
#include <fstream>
using namespace std;

//function prototypes

        /**************************************************************/

        /* FUNCTION: sortList

        /*                                                                                      */

        /* PURPOSE: Performs a bubble sort algorithm on a linked list of integers, sorting the items into ascending order.

        /*                                                                                      */

        /**************************************************************/

	ListN sortList ( ListN list );

        /**************************************************************/

        /* FUNCTION: binarySearch

        /*                                                                                      */

        /* PURPOSE: Searches an array based list for a target value. Returns the index of the value if the value is found,
		and -1 if the value is not found. Calls itself recursively until the value is found or the whole list has been searched.

        /*                                                                                      */

        /**************************************************************/

	int binarySearch ( int target, int min, int max, ListA list );

//main program

int main ()
{

	//read values from data file into linked list

		//declare variables

		ifstream fin;

		ListN l;

		char* filename = new char [50];

		int temp;

		int counter = 0;

		//prompt user for filename

		cout << "Welcome to the int sorting program." << endl << endl << "Enter filename: ";

		cin >> filename;

		cout << endl;

		fin.open(filename);

		fin.clear();

		//if invalid filename, print an error and abort program

		if ( !fin.good() )
			{

			cout << "ERROR: unable to read file. Aborting program..." << endl;

			return 0;

			}

		//read in all the values from the file

		fin >> temp;

		while ( fin.good() )
			{

			l.insertAfter(temp);

			counter++;

			fin >> temp;

			}	

		//close file, delete and null filename pointer - done with them

		fin.close();

		delete filename;

		filename = NULL;

		//show the data collected

		cout << "Data before sorting             : " << l << endl << endl;

	//sort the list

		l = sortList( l );

		cout << "Data after sorting              : " << l << endl << endl;

	//copy linked list data into an array based list

		//declare array based list - use size of counter

		ListA a(counter);

		//copy each value from the beginning of the linked list to the end into the array based list

		l.gotoBeginning();

		for ( int index = 0; index < counter; index++ )
			{

			l.getCursor(temp);

			a.insertAfter(temp);

			l.gotoNext();

			}

		//show the data copied

		cout << "Data after copy into array list : " << a << endl << endl;

	//perform binary search on the array based list

		//prompt user for a value to search for

		cout << "Enter the value you are searching for: ";

		cin >> temp;

		cout << endl;

		//perform binary search

		int result = binarySearch( temp, 0, counter, a );

	//print index of searched value (if there is one) to console

		if ( result == -1 )
			{

			cout << "The value was not found. Ending program..." << endl;

			}

		else
			{

			cout << "The value " << temp << " was located at index " << result << " of the sorted list. Ending program..." << endl;

			}

	//end program

	return 0;

}

//function implementations

	ListN sortList ( ListN list )
		{

		//count the number of elements in the list

		int count;
		int temp1;
		int temp2;

		bool swapped = true;

		list.gotoBeginning();

		while ( list.gotoNext() )
			{

			count++;

			}

		//bubble sort - loop over the whole list, repeating as long as a swap was made the previous time

		while ( swapped == true )
			{

			//return to the beginning of the list and reset the flag

			swapped = false;

			list.gotoBeginning();

			//loop over the list

			for ( int index = 0; index < count; index++ )
				{

				//get the data value at cursor and at cursor+1

				list.getCursor(temp1);

				list.gotoNext();

				list.getCursor(temp2);

				list.gotoPrior();

				//swap the values if necessary

				if ( temp2 < temp1 )
					{

					list.replace(temp2);

					list.gotoNext();
			
					list.replace(temp1);

					list.gotoPrior();

					swapped = true;

					}

				//go to the next item

				list.gotoNext();
							
				}

			}

		return list;			

		}

	int binarySearch ( int target, int min, int max, ListA list )
		{

		//if max is less than min, the value was not found, return -1

		if ( max < min )
			{

			return -1;

			}

		//otherwise, determine what to do next

		else
			{

			//start at the beginning of the list

			list.gotoBeginning();

			//calculate the midpoint of the items in the list

			int midpoint = min + ( (max-min) / 2 );

			//loop to the midpoint

			for ( int index = 0; index < midpoint; index++ )
				{

				list.gotoNext();

				}

			//get the value at the midpoint

			int value;

			list.getCursor(value);

			//if target is greater than the value at the midpoint, search the lower half of the list

			if ( value > target )
				{

				return binarySearch ( target, min, midpoint-1, list );

				}

			//if the target is less than the value at the midpoint, search the upper half of the list

			if ( value < target )
				{

				return binarySearch ( target, midpoint+1, max, list );

				}

			//otherwise, you found it - check if this is the "leftmost" incidence of the value and return that- otherwise just return midpoint

			if ( value == target)
				{

				return midpoint;

				}

			}

		}
