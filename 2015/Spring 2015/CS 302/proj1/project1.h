/** CS 302 Project 1 - code shell for use in employee data sorting/analyzing program
@file project1.h
@author Patrick Austin
@date 1/28/2015 */

#include <string>
using namespace std;

	class Employee{
	
		public:

		void setName(string newName);
		void setEmployeeID(int newEmployeeID);
		void setAge(int newAge);
		void setSalary(double newSalary);
		string getName();
		int getEmployeeID();
		int getAge();
		double getSalary();

		private:

		string name;
		int employeeID;
		int age;
		double salary;

		};

	class EmployeeContainer{
	
		public:

		int getNumEmployees();
		double getAvgSalary();
		int getAvgAge();
		void sortByID();
		bool addEmployee(Employee targetEmployee);
		bool exportEmployeeData();

		private:

		Employee* container;
		int numEmployees;

		};
