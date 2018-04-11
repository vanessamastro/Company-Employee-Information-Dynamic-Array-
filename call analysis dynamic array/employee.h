#pragma once
//Lab 7: Company Employee Information (Dynamic Array)
//Contains Employee class declaration
//Vanesssa Mastrosimone
//CSC 2430
//March 2, 2018


#include <iostream>
#include <string>
using namespace std;

class Employee
{
private:
	unsigned int _id;
	char *_name; //dynamically allocated to match the size of the name + 1 for zero byte
	double _salary;
	unsigned int _managerId;

public:
	//Constructors
	Employee(unsigned int, const string&, double, unsigned int = 0);
	Employee(const Employee&);

	//Accessors
	unsigned int GetId() const;
	string GetName() const;
	double GetSalary() const;
	unsigned int GetManagerId() const;

	string ToString();
	void Raise(double);
	bool Equals(const Employee&);
	bool Read(istream&);
	void Write(ostream&);

	//Destructor
	~Employee();
};