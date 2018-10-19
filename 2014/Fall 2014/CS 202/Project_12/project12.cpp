

        /***************************************************************/

        /* PROGRAM: project12.cpp                                                              */

        /*                                                                                       */

        /* AUTHOR: Patrick Austin                                                                   */

        /*                                                                                       */

        /* DATE: 12/8/2014                                                                   */

        /*                                                                                      */

        /* REVISIONS: N/A                                                                 */

        /*                                                                                      */

        /* PURPOSE: Reads in employee and student data from provided data file into class objects.
			Then conducts various experiments with class inheritance.                    */

        /*                                                                                      */

        /**************************************************************/



#include "classes.h"
#include "strings.h"
#include <iostream>
#include <fstream>
using namespace std;

int main()
	{

	ifstream fin;

	cout << "Patrick's CS 202 Inheritance Test Program" << endl << endl;

	//first, read in the values from the data file

		//open the file

		fin.clear();

		fin.open("persons");

		//let's create some temp variables for read-in, an array of students and employees to hold the read-in, and indices for looping

		int index;
		char temp;
		char* temp2 = new char [50];
		int tempInt;
		double tempDouble;

		int studentIndex = 0;
		int employeeIndex = 0;

		student* studentPointer = new student [8];	//this is also a way of testing the constructors
		employee* employeePointer = new employee [10];

		cout << endl;

		cout << "Reading 'persons' datafile..." << endl << endl;

		//read in the first char

		fin >> temp;

		//use the first char to determine which type of object to read in, and continue to the end of the file

		while ( fin.good() )
			{

			//if s, read in the data members for a student

			if ( temp == 's' )
				{

				//take the :

				fin >> temp;

				//read in the first name

				fin.getline( temp2, 1000, ':' );

				studentPointer[studentIndex].setFirstName(temp2);

				//read in the last name

				fin.getline( temp2, 1000, ':' );

				studentPointer[studentIndex].setLastName(temp2);

				//read in the age

				fin >> tempInt;

				studentPointer[studentIndex].setAge(tempInt);

				//take the :

				fin >> temp;

				//read in the SSN

				for ( index = 0; index < 9; index++ )
					{

					fin >> temp;

					studentPointer[studentIndex].setSsn(temp, index);

					}

				//take the :

				fin >> temp;

				//read in the NSHE number

				for ( index = 0; index < 10; index++ )
					{

					fin >> temp;

					studentPointer[studentIndex].setNsheNumber(temp, index);

					}

				//take the :

				fin >> temp;

				//read in the major

				fin.getline( temp2, 1000, ':' );

				studentPointer[studentIndex].setMajor(temp2);

				//read in the gpa

				fin >> tempDouble;

				studentPointer[studentIndex].setGpa(tempDouble);

				//print the student

				studentPointer[studentIndex].print();

				//increment studentIndex

				studentIndex++;

				}

			//if e, read in the data members for an employee

			if ( temp == 'e' )
				{

				//take the :

				fin >> temp;

				//read in the first name

				fin.getline( temp2, 1000, ':' );

				employeePointer[employeeIndex].setFirstName(temp2);

				//read in the last name

				fin.getline( temp2, 1000, ':' );

				employeePointer[employeeIndex].setLastName(temp2);

				//read in the age

				fin >> tempInt;

				employeePointer[employeeIndex].setAge(tempInt);

				//take the :

				fin >> temp;

				//read in the SSN

				for ( index = 0; index < 9; index++ )
					{

					fin >> temp;

					employeePointer[employeeIndex].setSsn(temp, index);

					}

				//take the :

				fin >> temp;

				//read in employee number

				for ( index = 0; index < 5; index++ )
					{

					fin >> temp;

					employeePointer[employeeIndex].setEmployeeNumber(temp, index);

					}

				//take the :

				fin >> temp;

				//read in the title

				fin.getline( temp2, 1000, ':' );

				employeePointer[employeeIndex].setTitle(temp2);

				//read in the salary

				fin >> tempInt;

				employeePointer[employeeIndex].setSalary(tempInt);

				//print the employee

				employeePointer[employeeIndex].print();

				//increment employeeIndex

				employeeIndex++;

				}

			//read in the next char and start over

			fin >> temp;		

			}

	//clean up temps

	delete [] temp2;
	temp2 = NULL;

	cout << "Read in " << studentIndex << " students." << endl;
	cout << "Read in " << employeeIndex << " employees." << endl << endl;

	//now, let's manipulate and experiment with the data

		//make some temp class objects

		student a;
		person b;

		//now let's play around with pointers and variables with these objects

			person* pPointer;
			student* sPointer;
			employee* ePointer;

			//does a person pointer work with a student object?

			cout << "Testing student object with person pointer..." << endl << endl;

			pPointer = &a;	//yes, compiles

			pPointer->print();

			/*

			//does a student pointer work with a person object?

			sPointer = &b; 	//no, does not compile

			sPointer->print();
		
			//does an employee pointer work with a student object?

			ePointer = &a;	//no, does not compile

			ePointer->print();

			//can you typecast a person object as a student?

			student(b).print(); //no, does not compile

			*/

			//can you typecast a student object as a person?

			cout << "Testing typecasting a student object as a person..." << endl << endl;

			person(a).print();	//yes, compiles

			//can you hold a student object in a person variable?

			cout << "Testing storing a student class object in a person variable..." << endl << endl;

			b = a;

			b.print(); 		//yes, compiles. However, data in the char* data members is lost.

			/*

			//can you put it back?

			a = b;			//no, does not compile. requires overloaded assignment operator

			a.print();

			*/		

	//now, let's clean up temps, deallocate memory and end the program

	ePointer = NULL;
	sPointer = NULL;
	pPointer = NULL;

	delete [] studentPointer;	//this also lets us test the destructors
	studentPointer = NULL;

	delete [] employeePointer;
	employeePointer = NULL;

	cout << endl;

	cout << "Exiting Patrick's CS 202 Inheritance Testing Program..." << endl;

	return 0;

	}
