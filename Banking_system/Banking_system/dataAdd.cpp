#include "dataTypes.h"
#include "functions.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

void addBranch() {
	ofstream file(branchesDB, ios::app);
	if (!file) {
		cout << "Could not open file" << endl;
		return;
	}

	Branch branch;

	branch.id = generateBranchId();
	cout << "New Branch ID: " << branch.id << endl;

	do {
		cout << "Enter Branch name: ";
		getline(cin, branch.name);
		if (branch.name.empty()) {
			cout << "Branch name cant be left blank! Please try again!\n";
		}
	} while (branch.name.empty());

	do {
		cout << "Enter Branch address: ";
		getline(cin, branch.address);
		if (branch.address.empty()) {
			cout << "Branch address cant be left blank! Please try again!\n";
		}
	} while (branch.address.empty());

	file << branch.id << "|" << branch.name << "|" << branch.address << endl;
	file.close();
	cout << "Branch data added successfully!" << endl;
}

void addDepartment() {
	loadBranches();

	if (branchCount == 0) {
		cout << "No Branch has been added! Firstly, add the Branch!";
		return;
	}

	ofstream file(departmentsDB, ios::app);
	if (!file) {
		cout << "Could not open file" << endl;
		return;
	}

	Department department;

	department.id = generateDepartmentId();
	cout << "New Department ID: " << department.id << endl;

	do {
		cout << "Enter Department name: ";
		getline(cin, department.name);
		if (department.name.empty()) {
			cout << "Department name cant be left blank! Please try again!\n";
		}
	} while (department.name.empty());

	displayBranches(false);
	int option;
	bool valid_choice = false;
	while (!valid_choice) {
		cout << "Choose which Branch owns this Department (enter coresponding number 1 - " << branchCount << "): ";
		cin >> option;

		if (option >= 1 && option <= branchCount) {
			department.branch_id = branchArray[option - 1].id;
			valid_choice = true;
		}
		else {
			cout << "Wrong input, enter number from 1 to " << branchCount << endl;
		}
	}
	cin.ignore();

	file << department.id << "|" << department.name << "|" << department.branch_id << endl;
	file.close();
	cout << "Department data added successfully!" << endl;
}

void addEmployee() {
	loadDepartments();

	if (departmentCount == 0) {
		cout << "No Department has been added! Firstly, add the Department!";
		return;
	}

	ofstream file(employeesDB, ios::app);
	if (!file) {
		cout << "Could not open file" << endl;
		return;
	}

	Employee employee;

	employee.id = generateEmployeeId();
	cout << "New Employee ID: " << employee.id << endl;

	do {
		cout << "Enter employee name: ";
		getline(cin, employee.name);
		if (employee.name.empty()) {
			cout << "Employee name cant be left blank! Please try again!\n";
		}
	} while (employee.name.empty());

	do {
		cout << "Enter employee surname: ";
		getline(cin, employee.surname);
		if (employee.surname.empty()) {
			cout << "Employee surnname cant be left blank! Please try again!\n";
		}
	} while (employee.surname.empty());

	do {
		cout << "Enter employee position: ";
		getline(cin, employee.position);
		if (employee.position.empty()) {
			cout << "Employee position cant be left blank! Please try again!\n";
		}
	} while (employee.position.empty());


	displayDepartments(false);
	int option;
	bool valid_choice = false;
	while (!valid_choice) {
		cout << "Choose to which Department belongs this employee (enter coresponding number 1 - " << departmentCount << "): ";
		cin >> option;

		if (option >= 1 && option <= departmentCount) {
			employee.department_id = departmentArray[option - 1].id;
			valid_choice = true;
		}
		else {
			cout << "Wrong input, enter number from 1 to " << departmentCount << endl;
		}
	}
	cin.ignore();

	int access_option;
	valid_choice = false;
	while (!valid_choice) {
		cout << "Choose Access Level:" << endl
			<< "0: GUEST," << endl
			<< "1: BASIC_USER" << endl
			<< "2: ADMIN" << endl
			<< "3: SUPER_ADMIN" << endl;
		cin >> access_option;
		if (access_option >= 0 && access_option <= 3) {
			employee.access_level = static_cast<AccessLevel>(access_option);
			valid_choice = true;
		}
		else {
			cout << "Wrong input, enter number from 0 to 3" << endl;
		}
	}
	cin.ignore();

	file << employee.id << "|" << employee.name << "|" << employee.surname << "|" << employee.department_id << "|" << employee.position << "|" << employee.access_level << endl;
	file.close();
	cout << "Employee data added successfully!";

}

void addClient() {
	loadBranches();
	if (branchCount == 0) {
		cout << "No Branch has been added! Firstly, add the Branch!";
		return;
	}

	ofstream file(clientsDB, ios::app);
	if (!file) {
		cout << "Could not open file" << endl;
		return;
	}

	Client client;

	client.id = generateClientId();
	cout << "New Client ID: " << client.id << endl;

	do {
		cout << "Enter client name: ";
		getline(cin, client.name);
		if (client.name.empty()) {
			cout << "Client name cant be left blank! Please try again!\n";
		}
	} while (client.name.empty());

	do {
		cout << "Enter client surname: ";
		getline(cin, client.surname);
		if (client.surname.empty()) {
			cout << "Client surname cant be left blank! Please try again!\n";
		}
	} while (client.surname.empty());

	displayBranches(false);
	int option;
	bool valid_choice = false;
	while (!valid_choice) {
		cout << "Choose to which Branch belongs this client (enter coresponding number 1 - " << branchCount << "): ";
		cin >> option;

		if (option >= 1 && option <= branchCount) {
			client.branch_id = branchArray[option - 1].id;
			valid_choice = true;
		}
		else {
			cout << "Wrong input, enter number from 1 to " << branchCount << endl;
		}
	}
	cin.ignore();

	int client_type_option;
	valid_choice = false;
	while (!valid_choice) {
		cout << "Choose client type:" << endl
			<< "0: PRIVATE" << endl
			<< "1: CORPORATE" << endl;
		cin >> client_type_option;
		if (client_type_option == 0 || client_type_option == 1) {
			client.type = static_cast<ClientType>(client_type_option);
			valid_choice = true;
		}
		else {
			cout << "Wrong input, enter number from 0 to 1" << endl;
		}
	}
	cin.ignore();

	file << client.id << "|" << client.name << "|" << client.surname << "|" << client.branch_id << "|" << client.type << endl;
	file.close();
	cout << "Client data added successfully!" << endl;
}

void addAccount() {
	loadClients();
	if (clientCount == 0) {
		cout << "No Client has been added! Firstly, add the Client!";
		return;
	}

	ofstream file(accountsDB, ios::app);
	if (!file) {
		cout << "Could not open file" << endl;
		return;
	}

	Account account;

	account.account_number = generateAccountNumber();
	cout << "New account number: " << account.account_number << endl;
	displayClients(false);
	int option;
	bool valid_choice = false;
	while (!valid_choice) {
		cout << "Choose which Client owns this Account (enter coresponding number 1 - " << clientCount << "): ";
		cin >> option;

		if (option >= 1 && option <= clientCount) {
			account.owner_id = clientArray[option - 1].id;
			valid_choice = true;
		}
		else {
			cout << "Wrong input, enter number from 1 to " << clientCount << endl;
		}
	}
	cin.ignore();

	cout << "Enter starting balance: ";
	cin >> account.balance;
	cin.ignore();

	file << account.account_number << "|" << account.owner_id << "|" << account.balance << endl;
	file.close();
	cout << "Account data added successfully!";
}
