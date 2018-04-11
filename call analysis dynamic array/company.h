#pragma once
//Lab 7: Company Employee Information (Dynamic Array)
//Contains Company class declaration
//Vanesssa Mastrosimone
//CSC 2430
//March 2, 2018


#include <iostream>
#include <string>
using namespace std;


class Company
{
	friend class Employee;
private:
	unsigned int _employeeCapacity;
	Employee** _employees;
	unsigned int _employeeCount;
	int BinarySearch(unsigned int _employeeCapacity);
	void Sort();

public:
	//Constructor: creates the dynamic array of Employee*, with as many elements as specified in _employeeCapacity
	Company(unsigned int);

	bool AddEmployee(unsigned int, const string&, double, unsigned int = 0);
	bool AddEmployee(const Employee&);
	int FindById(unsigned int);
	int FindByName(const string&, unsigned int = 0);
	int Read(istream&);
	int Write(ostream&);
	bool IsFull();
	Employee* Get(unsigned int);
	unsigned int GetEmployeeCount();
	bool DeleteEmployee(unsigned int);

	//Destructor
	~Company();
};