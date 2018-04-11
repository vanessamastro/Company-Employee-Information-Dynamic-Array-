//Lab 7: Company Employee Information (Dynamic Array)
//Contains Employee class method definitions
//Vanesssa Mastrosimone
//CSC 2430
//March 2, 2018

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstring>
using namespace std;
#include "employee.h"


//Creates an employee using the values passed in; last parameter is boss' ID (default parameter)
Employee::Employee(unsigned int id, const string& name, double salary, unsigned int managerID)
{
	_id = id;
	//If name parameter is empty, initialize name to "***"
	if (name == "")
	{
		string defaultStars = "***";
		_name = new char[defaultStars.length() + 1];
		strcpy(_name, defaultStars.c_str());
	}
	else
	{
		//Allocates enough memory for the string (+ zero byte) and copies the parameter into that space 
		_name = new char[name.length() + 1];
		strcpy(_name, name.c_str());
	}
	_salary = salary;
	_managerId = managerID;
}


//Copy constructor for Employee
Employee::Employee(const Employee& worker)
{
	_id = worker.GetId();
	_name = new char[worker.GetName().length() + 1];
	strcpy(_name, worker.GetName().c_str());
	_salary = worker.GetSalary();
	_managerId = worker.GetManagerId();
}


//Accessor: returns the ID
unsigned int Employee::GetId() const
{
	return _id;
}

//Accessor: returns the name
string Employee::GetName() const
{
	return _name;
}

//Accessor: returns the salary
double Employee::GetSalary() const
{
	return _salary;
}

//Accessor: returns boss' ID
unsigned int Employee::GetManagerId() const
{
	return _managerId;
}

//Returns a string representation of the employee
// Name: NNNNNNNNNN ID: IIIII Salary: SSSSSSS.SS Manager ID: MMMMM
string Employee::ToString()
{
	string stringVersion;
	stringstream ss;
	ss << "Name: " << setw(10) << left << _name << "ID: " << setw(5) << left << _id << "Salary: " << setw(10) << left << _salary << "Manager ID: " << setw(5) << left << _managerId;
	stringVersion = ss.str();
	return stringVersion;
}

//Gives a raise to the employee, adding specified amount to his or her current salary
void Employee::Raise(double increase)
{
	_salary += increase;
}

//Returns true if the employee specified by the parameter has the same ID as current object
bool Employee::Equals(const Employee& worker)
{
	if (worker._id == _id)
		return true;
	else
		return false;
}

//Reads an employee from istream and returns T/F depending on whether read was successful
bool Employee::Read(istream& fin)
{
	if (!fin.eof())
	{
		string name;
		unsigned int id, managerId;
		double salary;

		fin >> id >> name >> salary >> managerId;
		
		delete[] _name;
		_name = NULL;

		_id = id;
		_name = new char[name.length() + 1];
		strcpy(_name, name.c_str());
		_salary = salary;
		_managerId = managerId;

		if (fin.fail())
			return false;
		return true;
	}
	else
		return false;
}

//Writes the information about an employee, separated by spaces, to ostream
void Employee::Write(ostream& fout)
{
	fout << _id << " " << _name << " " << _salary << " " << _managerId << endl;
}

//Destructor, releases the memory allocated for the name
Employee::~Employee()
{
	if (_name != NULL)
	{
		delete[] _name;
		_name = NULL;
	}
}