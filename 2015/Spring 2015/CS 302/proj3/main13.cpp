/** CS 302 Project 3 Question 13 - main program for testing
@file main13.cpp
@author Patrick Austin
@date 2/21/2015 */

#include "myclass13.h"
#include <iostream>
using namespace std;

int main()
	{

	//print title

	cout << "CS 302 Project 3, Problem 13: Flight path map program" << endl << endl;

	//create a map object

	map test;

	cout << endl;

	//process each request

	for ( int index = 0; index < test.getNumRequests(); index++ )
		{

		//print the request

		cout << "Request is to fly from " << test.getRequestOrigin(index).getName() << 
		" to " << test.getRequestDestination(index).getName() << "." << endl;

		//if the origin or destination is not serviced, print a message saying so

		if ( !test.isValidRequest( index ) )
			{

			cout << "Sorry, CSair does not serve ";

			//if neither location is serviced

			if ( !test.isServicedCity( test.getRequestOrigin(index) ) && 
			!test.isServicedCity( test.getRequestDestination(index) ) )
				{

				cout << test.getRequestOrigin(index).getName() << 
				" or " << test.getRequestDestination(index).getName() << "." << endl << endl;

				}

			//if the origin is not serviced

			else if ( !test.isServicedCity( test.getRequestOrigin(index) ) )
				{

				cout << test.getRequestOrigin(index).getName() << "." << endl << endl;

				}

			//if the destination is not serviced

			else
				{

				cout << test.getRequestDestination(index).getName() << "." << endl << endl;

				}

			}

		//the request is valid - see if there is a path

		else
			{

			//there is a path, an itinerary will be printed. If there was no path, print an error

			if ( !test.isPath( test.getRequestOrigin(index), test.getRequestDestination(index) ) )
				{

				//print an error

				cout << "Sorry, CSAir does not fly from " << test.getRequestOrigin(index).getName() << 
				" to " << test.getRequestDestination(index).getName() << "." << endl << endl;			

				}

			}

		}

	//end program

	return 0;

	}
