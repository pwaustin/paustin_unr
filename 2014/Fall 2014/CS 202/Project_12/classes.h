#include <iostream>
using namespace std;

class person{

	public:
	person();
	~person();
	void setFirstName ( char* );
	char* getFirstName();
	void setLastName ( char* );
	char* getLastName();
	void setAge( int );
	int getAge();
	void setSsn( char, int );
	int* getSsn();
	void print();

	protected:
	char* firstName;
	char* lastName;
	int age;

	private:
	int* ssn;

	};

class employee: public person{
	
	public:
	employee();
	~employee();
	void setEmployeeNumber( char, int );
	int* getEmployeeNumber();
	void setTitle( char* );
	char* getTitle();
	void setSalary( int );
	int getSalary();
	void print();
	
	private:
	int* employeeNumber;
	char* title;
	int salary;

	};

class student: public person{

	public:
	student();
	~student();
	void setNsheNumber( char, int );
	int* getNsheNumber();
	void setMajor( char* );
	char* getMajor();
	void setGpa( double );
	double getGpa();
	void print();

	private:
	int* nsheNumber;
	char* major;
	double gpa;

	};
