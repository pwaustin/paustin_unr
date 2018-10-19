#include "classes.h"
#include "strings.h"
#include <iostream>
using namespace std;

	person::person()
		{

		cout << "In person constructor..." << endl;

		firstName = new char [50];
		strCopy( firstName, "First name" );

		lastName = new char [50];
		strCopy( lastName, "Last name" );

		age = 0;

		ssn = new int[9];
		
		for (int index = 0; index < 9; index++ )
			{

			ssn[index] = 0;

			}

		}

	person::~person()
		{

		cout << "In person destructor..." << endl;

		delete [] firstName;
		firstName = NULL;

		delete [] lastName;
		lastName = NULL;

		delete ssn;
		ssn = NULL;

		}

	void person::setFirstName ( char* target )
		{

		strCopy( firstName, target );

		}

	char* person::getFirstName()
		{

		return firstName;

		}

	void person::setLastName ( char* target )
		{

		strCopy( lastName, target );

		}

	char* person::getLastName()
		{

		return lastName;

		}

	void person::setAge( int target )
		{

		age = target;

		}
		
	int person::getAge()
		{

		return age;

		}

	void person::setSsn( char target, int index )
		{

		ssn[index] = int(target) - 48;

		}

	int* person::getSsn()
		{

		return ssn;

		}

	void person::print()
		{

		cout << "Printing person..." << endl;
		cout << "First name: " << firstName << endl;
		cout << "Last name : " << lastName << endl;
		cout << "Age       : " << age << endl;
		cout << "SSN       : ";

		for (int index = 0; index < 9; index++ )
			{

			cout << ssn[index];

			}

		cout << endl << endl;

		}

	employee::employee()
		{

		cout << "In employee constructor..." << endl;

		employeeNumber = new int[5];
		
		for ( int index = 0; index < 5; index++ )
			{

			employeeNumber[index] = 0;

			}

		title = new char [50];
		strCopy ( title, "Title" );

		salary = 0;

		}

	employee::~employee()
		{

		cout << "In employee destructor..." << endl;

		delete employeeNumber;
		employeeNumber = NULL;

		delete [] title;
		title = NULL;

		}

	void employee::setEmployeeNumber( char target, int index ) 
		{

		employeeNumber[index] = int(target) - 48;

		}

	int* employee::getEmployeeNumber()
		{

		return employeeNumber;

		}

	void employee::setTitle( char* target )
		{

		strCopy ( title, target );

		}

	char* employee::getTitle()
		{

		return title;

		}

	void employee::setSalary( int target )
		{

		salary = target;

		}

	int employee::getSalary()
		{

		return salary;

		}

	void employee::print()
		{

		cout << "Printing employee..." << endl;
		cout << "First name: " << firstName << endl;
		cout << "Last name : " << lastName << endl;
		cout << "Age       : " << age << endl;
		cout << "SSN       : ";

		int* temp = getSsn();

		for (int index1 = 0; index1 < 9; index1++ )
			{

			cout << temp[index1];

			}

		cout << endl;

		cout << "Employee number: ";

		for ( int index2 = 0; index2 < 5; index2++ )
			{

			cout << employeeNumber[index2];

			}

		cout << endl;

		cout << "Title          : " << title << endl;
		cout << "Salary         : " << salary << endl;

		cout << endl;

		temp = NULL;

		}

	student::student()
		{

		cout << "In student constructor..." << endl;

		nsheNumber = new int[10];
		
		for ( int index = 0; index < 10; index++ )
			{

			nsheNumber[index] = 0;

			}

		major = new char [50];
		strCopy ( major, "Major" );

		gpa = 0.0;

		}

	student::~student()
		{

		cout << "In student destructor..." << endl;

		delete nsheNumber;
		nsheNumber = NULL;

		delete [] major;
		major = NULL;

		}

	void student::setNsheNumber( char target, int index ) 
		{

		nsheNumber[index] = int(target) - 48;

		}

	int* student::getNsheNumber()
		{

		return nsheNumber;

		}

	void student::setMajor( char* target )
		{

		strCopy ( major, target );

		}

	char* student::getMajor()
		{

		return major;

		}

	void student::setGpa( double target )
		{

		gpa = target;

		}

	double student::getGpa()
		{

		return gpa;

		}

	void student::print()
		{

		cout << "Printing person..." << endl;
		cout << "First name: " << firstName << endl;
		cout << "Last name : " << lastName << endl;
		cout << "Age       : " << age << endl;
		cout << "SSN       : ";

		int* temp = getSsn();

		for (int index1 = 0; index1 < 9; index1++ )
			{

			cout << temp[index1];

			}

		cout << endl;

		cout << "NSHE number: ";

		for ( int index2 = 0; index2 < 10; index2++ )
			{

			cout << nsheNumber[index2];

			}

		cout << endl;
		cout << "Major      : " << major << endl;
		cout << "GPA        : " << gpa << endl;

		cout << endl;

		}
