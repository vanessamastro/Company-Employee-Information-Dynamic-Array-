//Lab 7: Company Employee Information (Dynamic Array)
//Contains Company class method definitions
//Vanesssa Mastrosimone
//CSC 2430
//March 2, 2018


#include <iostream>
#include <string>
using namespace std;
#include "company.h"
#include "employee.h"

//Constructor for Company: array of Employee* is dynamically allocated to size specified when this is called
Company::Company(unsigned int numEmployees)
{
	_employeeCapacity = numEmployees;	
	_employees = new Employee* [_employeeCapacity];
	_employeeCount = 0;
}

//Adds an employee to the list
//If the employee fits in the array (!IsFull()) then it creates a new Employee with given data 
//And places it in next available position. Returns true if able to add it, false if not
bool Company::AddEmployee(unsigned int id, const string& name, double salary, unsigned int managerID)
{
	//If the employee fits in the array
	if (!IsFull())
	{
		_employees[GetEmployeeCount()] = new Employee(id, name, salary, managerID);
		_employeeCount++;
		return true;
	}
	return false;
}


//Adds the specified employee to the list
//Creates a new Employee using the copy constructor and places it in next available position; returns true if able to add it, false if not
bool Company::AddEmployee(const Employee& employee)
{

	//If the employee fits in the array
	if (!IsFull())
	{
		_employees[GetEmployeeCount()] = new Employee(employee);
		_employeeCount++;
		return true;
	}
	return false; //Unable to add the employee
}


//Uses binary search to find an employee using ID given in parameter
//Returns -1 if the employee is not found; returns position of employee
int Company::FindById(unsigned int key)
{
	int position = BinarySearch(key);
	return position;
}

//Uses linear search starting from the position specified by the second parameter to find the first occurrence of given name in the array
//Returns -1 if employee is not found; returns position of employee
int Company::FindByName(const string& name, unsigned int position)
{
	for (int i = position; i < GetEmployeeCount(); i++)
	{
		if (name == _employees[i]->GetName())
			return i;
	}
	return -1;
}

//Reads an istream and extracts all the employees' data from there, and adds the employees to existing list of employees up to size of the array
//Sorts the array; returns the number of employees read
int Company::Read(istream& fin)
{
	bool failed = false;
	int numRead = 0;
	while (!fin.eof() && !IsFull())
	{
		Employee *worker = new Employee(0, "", 0.0, 0);
		if (!(worker->Read(fin)))
		{
			failed = true;
		}
		else
		{
			if (this->AddEmployee(*worker) == true)
				numRead++;
		}
		delete worker;
		//worker = NULL;
	}
	if (!failed || (fin.eof() && GetEmployeeCount() > 0))
		Sort();
	return numRead;
}

//Writes all the available employees to the ostream, returns the number of employees written
int Company::Write(ostream& output)
{
	int numWritten = 0;
	for (int i = 0; i < GetEmployeeCount(); i++)
	{
		output << _employees[i]->GetId() << " " << _employees[i]->GetName() << " " << _employees[i]->GetSalary() << " " << _employees[i]->GetManagerId() << endl;
		numWritten++;
	}
	return numWritten;
}

//Returns true if the array of employees is full, false otherwise
bool Company::IsFull()
{
	if (GetEmployeeCount() >= _employeeCapacity)
		return true;
	else
		return false;
}

//Returns a pointer to the Employee at the position specified by the parameter
//The referenced object belongs to the object and should not be "deleted" by the client
Employee* Company::Get(unsigned int position)
{
	//If the position is invalid, returns NULL
	if (position >= GetEmployeeCount())
		return NULL;
	else
		return _employees[position];
}

//Returns the number of employees in the Company (_employeeCount)
unsigned int Company::GetEmployeeCount()
{
	return _employeeCount;
}

//Private: sorts the array of employees by ID; you may use any sorting algorithm
void Company::Sort()
{
	for (int i = 0; i < GetEmployeeCount() - 1; i++)
	{
		for (int j = 0; j < GetEmployeeCount() - i - 1; j++)
		{
			if (_employees[j]->GetId() > _employees[j + 1]->GetId())
			{
				Employee *temp = _employees[j];
				_employees[j] = _employees[j + 1];
				_employees[j + 1] = temp;
			}

		}
	}
}

//Private: executes a binary search in the array; parameter incidates the key that is being searched
//Returns position found or -1 if not found
int Company::BinarySearch(unsigned int key)
{
	int first = 0, last = GetEmployeeCount() - 1;
	while (first <= last)
	{
		int mid = (first + last) / 2;
		if (key < _employees[mid]->GetId())
			last = mid - 1;
		else if (key > _employees[mid]->GetId())
			first = mid + 1;
		else //(key == _employees[mid]->GetId())
			return mid;
	}
	return -1;

}

//Deletes the employee using the ID given in the parameter
bool Company::DeleteEmployee(unsigned int ID)
{
	int pos = FindById(ID);

	//Validate ID
	if (pos == -1)
		return false;

	else
	{
		//Validate that the employee to be erased is not a manager, return false if they have subordinates
		for (int i = 0; i < GetEmployeeCount(); i++)
		{
			//Employee has subordinates
			if (Get(i)->GetManagerId() == ID)
				return false;
		}

		//If they are able to be erased, free the allocated memory by that employee
		delete Get(pos);

		_employeeCount--;
		//"Moves up" the other employees
		for (int i = pos; i < GetEmployeeCount(); i++)
		{
			_employees[i] = _employees[i + 1];
			
		}
		
		return true;
	}
}


//Destructor, frees the memory by releasing all the dynamically allocated employees in the array
//After releasing the memory of each employee, this destructor releases the memory allocated for the array
Company::~Company()
{
	
	for (int i = 0; i < _employeeCount; i++)
	{
		//Does NOT delete array elements (employees) that were not dynamically created
		if (_employees[i] != NULL)
		{
			delete _employees[i];
			_employees[i] = NULL;
		}
	}
	
	delete[] _employees;
	_employees = NULL;
	_employeeCount = 0;
}