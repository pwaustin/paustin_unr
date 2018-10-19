/** CS 302 Project 1 - code shell for use in employee data sorting/analyzing program
@file project1.cpp
@author Patrick Austin
@date 1/28/2015 */

#include <iostream>
#include <fstream>
#include <string>
#include "project1.h"
using namespace std;

		/** Sets the name data member for an employee object. Use in conjunction with file read-in to load the employee data.
		@param newName The name to be stored.
		@pre None.
		@post The parameter string will be stored as the name data member of the object.
		@return None. */
		void Employee::setName(string newName) 
			{}

		/** Sets the employeeID data member for an employee object. Use in conjunction with file read-in to load the employee data.
		@param newEmployeeID The employeeID to be stored.
		@pre None.
		@post The parameter int will be stored as the employeeID data member of the object.
		@return None. */
		void Employee::setEmployeeID(int newEmployeeID) 
			{}

		/** Sets the age data member for an employee object. Use in conjunction with file read-in to load the employee data.
		@param newAge The age to be stored.
		@pre None.
		@post The parameter int will be stored as the age data member of the object.
		@return None. */
		void Employee::setAge(int newAge) 
			{}

		/** Sets the salary data member for an employee object. Use in conjunction with file read-in to load the employee data.
		@param newSalary The salary to be stored.
		@pre None.
		@post The parameter double will be stored as the salary data member of the object.
		@return None. */
		void Employee::setSalary(double newSalary) 
			{}


		/** Retrieves the name data member from an employee object.
		@param None.
		@pre None, but caveat emptor - value could be temp or garbage if good data has not yet been entered.
		@post The stored string in the name data member will be returned by the function.
		@return String stored in name data member. */
		string Employee::getName()
			{}

		/** Retrieves the employeeID data member from an employee object.
		@param None.
		@pre None, but caveat emptor - value could be temp or garbage if good data has not yet been entered.
		@post The stored int in the employeeID data member will be returned by the function.
		@return Int stored in employeeID data member. */
		int Employee::getEmployeeID()
			{}

		/** Retrieves the age data member from an employee object.
		@param None.
		@pre None, but caveat emptor - value could be temp or garbage if good data has not yet been entered.
		@post The stored int in the age data member will be returned by the function.
		@return Int stored in age data member. */
		int Employee::getAge()
			{}

		/** Retrieves the salary data member from an employee object.
		@param None.
		@pre None, but caveat emptor - value could be temp or garbage if good data has not yet been entered.
		@post The stored double in the salary data member will be returned by the function.
		@return Double stored in salary data member. */
		double Employee::getSalary()
			{}

		/** Returns the number of employee objects stored in the EmployeeContainer.
		@param None.
		@pre None.
		@post The stored int in the numEmployees data member will be returned by the function. If the container is empty, the function will return 0.
		@return Int stored in numEmployees data member. */
		int EmployeeContainer::getNumEmployees() 
			{}

		/** Calculates the average of the salaries of the employee objects stored in the EmployeeContainer.
		@param None.
		@pre None.
		@post The calculated value will be returned by the function. If the container is empty, the function will return -1.
		@return The calculated average of the employee salaries stored in the EmployeeContainer, or -1 if the container is empty. */
		double EmployeeContainer::getAvgSalary() 
			{}

		/** Calculates the average age of the employee objects stored in the EmployeeContainer.
		@param None.
		@pre None.
		@post The calculated age will be returned by the function. If the container is empty, the function will return -1.
		@return The calculated average of the ages of the employees stored in the EmployeeContainer, or -1 if the container is empty. */
		int EmployeeContainer::getAvgAge() 
			{}

		/** Sorts the employees within the EmployeeContainer in ascending order of employeeID in subsequent elements of the container (ie employee 
		with the lowest employeeID in the first element, employee with the highest employeeID in the final used element).
		@param None.
		@pre None.
		@post The employees will be sorted within the EmployeeContainer. If the number of employees is less than or equal to 1, no sorting can be done and 
		no action will be performed.
		@return None. */
		void EmployeeContainer::sortByID() 
			{}

		/** Attempts to add a new employee object to the first empty element of the EmployeeContainer.
		@param targetEmployee The employee to be stored.
		@pre None.
		@post If successful, the newEmployee object will be stored in the first empty element of the container and numEmployees will be incremented by 1. 
		Otherwise, the container is unchanged and numEmployees remains the same.
		@return True if the addition was successful, or false otherwise (eg if the container was full). */
		bool EmployeeContainer::addEmployee( Employee targetEmployee )
			{}

		/** Prints stored employee information to console from the first stored element to the last. Note that if the data has been previously sorted, 
		this will print employee's data to the console in order of ascending employeeID. If the data has not been sorted, employee data will be printed 
		in the order in which it was entered into the container. In other words, in order to print sorted data, use the sortByID method before this one.
		@param None.
		@pre None.
		@post If successful, the information will be printed to the console. Otherwise, nothing will be printed.
		@return True if data was printed, or false otherwise (eg if the container was empty and there was nothing to print). */
		bool EmployeeContainer::exportEmployeeData() 
			{}

