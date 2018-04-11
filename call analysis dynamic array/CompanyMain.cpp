//Lab 7: Company Employee Information (Dynamic Array)
//Main program
//Vanesssa Mastrosimone
//CSC 2430
//March 2, 2018

#include <iostream>
#include <string>
#include <fstream>
#include "employee.h"
#include "company.h"

using namespace std;

void PrintMenu();
bool IsValidInteger(const string& input);
bool IsValidID(const string& input);

int main()
{
	Company *company = NULL;
	ifstream fin;
	string fileName, maxEmployees;
	int response = 0;
	string input = "";
	bool keepGoing = true;

	while (keepGoing) 
	{
		PrintMenu();
		getline(cin, input);

		if (input == "") 
		{
			cerr << "Invalid input, please try again" << endl;
			keepGoing = true;
		}
		else if (!IsValidInteger(input))
		{
			cerr << "Incorrect choice, please input valid option" << endl;
			keepGoing = true;
		}

		else 
		{
			response = stoi(input);

			//Load a Company File: asks user for the file name containing the employee's information
			if (response == 1) 
			{
				bool load = false;
				cout << "Please specify the maximum number of employees your database can hold: ";
				getline(cin, maxEmployees);
				
				while (!load)
				{
					if (maxEmployees == "")
						cerr << "Invalid input, please try again" << endl;
					else if (!IsValidInteger(maxEmployees))
						cerr << "Incorrect choice, please input a numeric value" << endl;
					else 
					{
						load = true;
						break;
					}
					getline(cin, maxEmployees);
				}
				delete company;
				unsigned int maxNum = stoi(maxEmployees);
				company = new Company(maxNum);
				cout << "Filename: ";
				getline(cin, fileName);
				fin.open(fileName);
				while (fin.fail()) {
					cerr << "Can't open '" << fileName << "'" << endl;
					getline(cin, fileName);
					fin.open(fileName);
				}
				cout << "File loaded, " << company->Read(fin) << " records read" << endl;
				fin.close();
				keepGoing = true;
			}

			//Save Company Data to File: saves the current information in memory to a file. Program asks user for the file name where they want to save it
			else if (response == 2) {

				if (company->GetEmployeeCount() == 0)
					cerr << "Error:  must load a company file before listing employees" << endl;

				else {
					string outputFileName;
					cout << "Save Company Data to: ";
					getline(cin, outputFileName);
					ofstream output(outputFileName); //Open file
					if (!output.is_open())
						cerr << "Can't open " << outputFileName << endl;
					else {
						output << company->Write(output) << endl;
						cout << "Company data saved to " << outputFileName << endl;
					}
					output.close();
				}
			}

			//List all Employees: lists all the employees stored in memory; uses company Write method to display them
			else if (response == 3) {
				if (company->GetEmployeeCount() == 0)
					cerr << "Error:  must load a company file before listing employees" << endl;

				else {
					for (int i = 0; i < company->GetEmployeeCount(); i++) {
						company->Get(i)->Write(cout);
					}
					cout << endl;
				}
			}

			//Search by Name: the user inputs a name, then, using the method FindByName the program displays all employees with that name using ToString method
			else if (response == 4) {

				if (company->GetEmployeeCount() == 0)
					cerr << "Error:  must load a company file before listing employees" << endl;

				else {
					string nameInput;
					cout << "Searching all employees with name: ";
					getline(cin, nameInput);
					for (int i = 0; i < company->GetEmployeeCount(); i++) {
						int pos = company->FindByName(nameInput, i); //Note: FindByName returns an int
						i = pos;
						if (pos == -1) {
							cerr << "No employee found" << endl;
							break;
						}
						cout << company->Get(pos)->ToString() << endl;
					}
				}
			}

			//Search by ID: the user inputs an ID, then, using the method FindById the program displays the employee with that ID using ToString method
			//or that it did find that ID
			else if (response == 5) {

				if (company->GetEmployeeCount() == 0)
					cerr << "Error:  must load a company file before listing employees" << endl;

				else {
					cout << "Search for an employee ID: ";
					string in;
					int ID;
					getline(cin, in);
					if (!IsValidID(in)) {
						cerr << "Not a valid ID" << endl;
					}
					else {
						ID = stoi(in);
						//If the input is not of type unsigned int, allows user to continue trying to enter a valid ID
						while (cin.fail()) {

							cin.clear(); //Turn off failbit
							cin.ignore(255, '\n'); //Get rid of nonnumeric input
							cerr << "Invalid input, please try again" << endl;
							getline(cin, in);
							ID = stoi(in);
						}

						int pos = company->FindById(ID);
						if (pos == -1) {
							cout << "Employee with ID: " << ID << " not found" << endl;
							keepGoing = true;
						}
						else {
							string response;
							cout << "Employee current information: " << endl;
							cout << company->Get(pos)->ToString() << endl;

							cout << "Would you like to give " << company->Get(pos)->GetName() << " a raise?(Y/N): ";
							getline(cin, response);
							bool continuing = true;
							while (continuing) {
								if (response == "y" || response == "Y") {
									double raise;
									cout << "What is the raise: ";
									cin >> raise;
									while (cin.fail()) {
										cin.clear(); //Turn off failbit
										cin.ignore(255, '\n');
										cerr << "Invalid input, please try again" << endl;
										cin >> raise;
									}
									cin.clear(); //Turn off failbit
									cin.ignore(255, '\n');
									company->Get(pos)->Raise(raise);
									continuing = false;
								}
								else if (response == "n" || response == "N") {
									continuing = false;
									keepGoing = true; //Go back to print the menu again
								}
								else {
									cout << "Invalid input, please try again" << endl;
									getline(cin, response);
								}
							}
						}
						cout << endl;
					}
				}
			}

			//Find Employee Boss Information: user inputs an ID, then, using the method FindById the program displays the employee with that ID using ToString method
			//or that it did not find that ID. Once employee is found, gets the manager's ID, and with it searches that ID and gets the rest of the manager's information.
			//Displays the manager information using ToString method
			else if (response == 6) {

				if (company->GetEmployeeCount() == 0)
					cerr << "Error:  must load a company file before listing employees" << endl;

				else {
					cout << "Search for employee ID: ";
					string in;
					int ID;
					getline(cin, in);
					ID = stoi(in);
					//If the input is not of type unsigned int, allows user to continue trying to enter a valid ID
					while (cin.fail()) {
						cin.clear(); //Turn off failbit
						cin.ignore(255, '\n');
						cerr << "Invalid input, please try again" << endl;
					}

					int pos = company->FindById(ID);
					if (pos == -1) {
						cout << "Employee with ID: " << ID << " not found" << endl;
						keepGoing = true;
					}
					else {
						cout << company->Get(pos)->ToString() << endl;
						cout << "Boss information: " << endl;
						int manager = company->Get(pos)->GetManagerId();
						int managerPos = company->FindById(manager);
						if (managerPos == -1)
							cerr << "Employee does not have a manager" << endl;
						else
							cout << company->Get(managerPos)->ToString() << endl
							<< endl;
						keepGoing = true;
					}
				}
			}

			//Add a New Employee: Requests the user to enter the following information about the employee: ID, name, salary, and manager ID
			//Only adds employees if it fits in the array!
			else if (response == 7) {
				int ID = 0;
				string name;
				double salary;
				int managerID;
				if (company->IsFull()) {
					cout << "Cannot add new records, database is full" << endl;
					keepGoing = true;
				}
				else {
					cout << "Input Employee Information" << endl;
					cout << "Employee ID: ";
					string in;
					getline(cin, in);
					while (!IsValidID(in)) {
						cerr << "Not a valid ID" << endl;
						getline(cin, in);
					}
					//Prompts user for an ID until input is a new ID
					while (company->FindById(ID) != -1) {
						cout << "ID already on file, choose a different ID: ";
						getline(cin, in);
					}

					ID = stoi(in);

					cout << "Employee Name: ";
					getline(cin, name);

					cout << "Salary: ";
					string salStr;
					getline(cin, salStr);
					salary = stod(salStr);
					//To handle errors if user inputs a letter instead of a number
					while (cin.fail()) {
						cin.clear(); //Turn off failbit
						cin.ignore(255, '\n'); //Get rid of nonnumeric input
						cout << "Invalid, please enter a numeric amount";
						getline(cin, salStr);
						salary = stod(salStr);
					}

					cout << "Boss ID (0 for none): ";
					string managerIDStr;
					getline(cin, managerIDStr);
					managerID = stoi(managerIDStr);
					//To handle errors if user inputs a letter instead of a number
					while (cin.fail()) {
						cin.clear(); //Turn off failbit
						cin.ignore(255, '\n');
						cout << "Invalid, please enter a numeric amount";
						getline(cin, salStr);
						salary = stod(salStr);
					}

					//If the employee was added successfully
					if (company->AddEmployee(ID, name, salary, managerID)) {
						cout << name << " added successfully" << endl;
						keepGoing = true;
					}
					else {
						cout << "Unable to add employee" << endl;
						keepGoing = true;
					}
				}
			}

			//Delete Employee: deletes an employee with the ID specified by user input. Only deletes the employee if the ID is valid and found, 
			//and if the employee does not have subordinates
			else if (response == 8)
			{
				//Cannot delete an employee from an empty database
				if (company->GetEmployeeCount() == 0)
					cerr << "Error:  must load a company file before listing employees" << endl;
				else
				{
					cout << "----- Preparing to Delete an Employee from Database -----" << endl;
					cout << "Search for employee ID: ";
					string ID;
					getline(cin, ID);
					bool deleteEmployee = false;
					while (!deleteEmployee)
					{
						if (ID == "")
							cerr << "Invalid input, please try again" << endl;
						else if (!IsValidID(ID))
							cerr << "Incorrect choice, please input a numeric value" << endl;
						else
							deleteEmployee = true;
					}

					//Verifies that the ID is actually in the Database, and if it isnt sends an error message
					unsigned int checkID = stoi(ID);
					if (company->FindById(checkID) == -1)
					{
						cerr << "No employee matches ID " << ID << endl;
						keepGoing = true;
					}
					else
					{
						int pos = company->FindById(checkID);
						//Displays employee information
						cout << "Employee Current Information: " << endl;
						cout << company->Get(pos)->ToString() << endl;
						//Asks for confirmation
						cout << "Are you really sure you want to erase the employee from the database (Y/N): ";
						string decision;
						getline(cin, decision);

						bool continuing = true;
						while (continuing)
						{
							if (decision == "y" || decision == "Y")
							{
								//If the employee is not able to be deleted
								if (!company->DeleteEmployee(checkID))
									cerr << "It is not possible to delete employee that has subordinates" << endl;

								else //company->DeleteEmployee(checkID) == true								
									cout << "Employee with ID = " << ID << " successfully deleted from database" << endl;

								continuing = false;
								break;
							}
							else if (decision == "n" || decision == "N")
							{
								continuing = false;
								keepGoing = true; //Go back to print the menu again
								break;
							}
							else
							{
								cout << "Invalid input, please try again" << endl;
								getline(cin, decision);
							}
						}
					}
				}

			}


			//Check if the Database is Full: displays a message indicating if the database is full, or not full.
			else if (response == 9) 
			{
				if (company->IsFull()) 
				{
					cout << "Database is Full" << endl;
					keepGoing = true;
				}
				else 
				{
					cout << "Database is not full, it has " << company->GetEmployeeCount() << " records" << endl;
					keepGoing = true;
				}
			}

			//Exit: exits the program
			else if (response == 0) 
			{
				keepGoing = false;
				exit(1);
			}
			else
			{
				cerr << "Incorrect choice, please input valid option" << endl;
				keepGoing = true;
			}
		}
		cout << endl << endl;
	}
}

void PrintMenu()
{
	cout << "1. Load a Company File" << endl;
	cout << "2. Save Company Data to File" << endl;
	cout << "3. List all Employees" << endl;
	cout << "4. Search by Name" << endl;
	cout << "5. Search by ID" << endl;
	cout << "6. Find Employee Boss Information" << endl;
	cout << "7. Add a New Employee" << endl;
	cout << "8. Delete Employee" << endl;
	cout << "9. Check if the Database is Full" << endl;
	cout << "0. Exit" << endl;
}

bool IsValidInteger(const string& input)
{
	if (input.find_first_not_of("0123456789") == string::npos)
	{
		return true;
	}
	return false;
}




bool IsValidID(const string& input)
{
	if (input.find_first_not_of("0123456789") == string::npos) 
	{
		return true;
	}
	return false;
}