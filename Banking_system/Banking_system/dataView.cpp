#include "dataTypes.h"
#include "functions.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

void displayBranches(bool useSearchResults) {
	if (!useSearchResults) {
		loadBranches();
	}
	
	int count = useSearchResults ? searchResultCount : branchCount;

	cout << "Total Branches found: " << count << "\n" << endl;
	if (count == 0) {
		cout << (useSearchResults ? "No brances found!" : "No branch has been loaded") << endl;
		return;
	}

	cout << setfill('-') << setw(70) << "" << endl;
	cout << setfill(' ');
	cout << left << setw(5) << "#" << "|"
		<< left << setw(5) << "ID" << "|"
		<< left << setw(25) << "Branch Name" << "|"
		<< left << "Address" << endl;
	cout << setfill('-') << setw(70) << "" << endl;
	cout << setfill(' ');

	for (int i = 0; i < count; i++) {
		int indexInBranchArray;
		if (useSearchResults) {
			indexInBranchArray = searchResultIndexes[i];
		}
		else {
			indexInBranchArray = i;
		}

		const Branch& currentBranch = branchArray[indexInBranchArray];

		cout << left << setw(5) << (i + 1) << "|"
			<<left << setw(5) << currentBranch.id << "|"
			<< left << setw(25) << currentBranch.name << "|"
			<< left << currentBranch.address << endl;
	}
	cout << setfill('-') << setw(70) << "" << endl;
	cout << setfill(' ');
}

void displayDepartments(bool useSearchResults) {
	if (!useSearchResults) {
		loadDepartments();
	}
	loadBranches();

	int count = useSearchResults ? searchResultCount : departmentCount;

	cout << "\n Total Departments found: " << count << "\n" << endl;
	if (count == 0) {
		cout << (useSearchResults ? "No departments found!" : "No department has been loaded") << endl;
		return;
	}
	cout << setfill('-') << setw(70) << "" << endl;
	cout << setfill(' ');
	cout << left << setw(5) << "#" << "|"
		<< left << setw(5) << "ID" << "|"
		<< left << setw(25) << "Department Name" << "|"
		<< left << "Branch" << endl;
	cout << setfill('-') << setw(70) << "" << endl;
	cout << setfill(' ');

	for (int i = 0; i < count; i++) {
		int indexInDepartmentArray;
		if (useSearchResults) {
			indexInDepartmentArray = searchResultIndexes[i];
		}
		else {
			indexInDepartmentArray = i;
		}

		const Department& currentDepartment = departmentArray[indexInDepartmentArray];

		string branchName = "Not Found!";
		int branchId = currentDepartment.branch_id;
		for (int j = 0; j < branchCount; j++) {
			if (branchArray[j].id == branchId) {
				branchName = branchArray[j].name;
				break;
			}
		}
		cout << left << setw(5) << (i + 1) << "|"
			<< left << setw(5) << currentDepartment.id << "|"
			<< left << setw(25) << currentDepartment.name << "|" << left << branchName << endl;
	}
	cout << setfill('-') << setw(70) << "" << endl;
	cout << setfill(' ');
}

void displayEmployees(bool useSearchResults) {
	if (!useSearchResults) {
		loadEmployees();
	}
	loadDepartments();

	int count = useSearchResults ? searchResultCount : employeeCount;

	cout << "\n Total Employees found: " << count << "\n" << endl;
	if (count == 0) {
		cout << (useSearchResults ? "No employees found!" : "No employee has been loaded") << endl;
		return;
	}

	cout << setfill('-') << setw(100) << "" << endl;
	cout << setfill(' ');
	cout << left << setw(5) << "#" << "|"
		<< left << setw(5) << "ID" << "|"
		<< left << setw(15) << "Name" << "|"
		<< left << setw(15) << "Surname" << "|"
		<< left << setw(20) << "Department" << "|"
		<< left << setw(20) << "Position" << "|"
		<< left << "Access Level" << endl;
	cout << setfill('-') << setw(100) << "" << endl;
	cout << setfill(' ');

	for (int i = 0; i < count; i++) {
		int indexInEmployeeArray;
		if (useSearchResults) {
			indexInEmployeeArray = searchResultIndexes[i];
		}
		else {
			indexInEmployeeArray = i;
		}

		const Employee& currentEmployee = employeeArray[indexInEmployeeArray];

		// Konverte enum uz lasamu tekstu
		string accessLevelStr;
		switch (currentEmployee.access_level) {
		case GUEST: accessLevelStr = "GUEST"; break;
		case BASIC_USER: accessLevelStr = "BASIC_USER"; break;
		case ADMIN: accessLevelStr = "ADMIN"; break;
		case SUPER_ADMIN: accessLevelStr = "SUPER_ADMIN"; break;
		default: accessLevelStr = "Unknown"; break;
		}

		string departmentName = "Not Found!";
		int departmentId = currentEmployee.department_id;
		for (int j = 0; j < departmentCount; j++) {
			if (departmentArray[j].id == departmentId) {
				departmentName = departmentArray[j].name;
				break;
			}
		}

		cout << left << setw(5) << (i + 1) << "|"
			<< left << setw(5) << currentEmployee.id << "|"
			<< left << setw(15) << currentEmployee.name << "|"
			<< left << setw(15) << currentEmployee.surname << "|"
			<< left << setw(20) << departmentName << "|"
			<< left << setw(20) << currentEmployee.position << "|"
			<< left << accessLevelStr << endl;
	}
	cout << setfill('-') << setw(100) << "" << endl;
	cout << setfill(' ');
}

void displayClients(bool useSearchResults) {
	if (!useSearchResults) {
		loadClients();
	}
	loadBranches();

	int count = useSearchResults ? searchResultCount : clientCount;

	cout << "\n Total Clients found: " << count << "\n" << endl;
	if (count == 0) {
		cout << (useSearchResults ? "No clients found!" : "No client has been loaded") << endl;
		return;
	}

	cout << setfill('-') << setw(100) << "" << endl;
	cout << setfill(' ');
	cout << left << setw(5) << "#" << "|"
		<< left << setw(5) << "ID" << "|"
		<< left << setw(30) << "Name" << "|"
		<< left << setw(15) << "Surname" << "|"
		<< left << setw(20) << "Branch" << "|"
		<< left << "Type" << endl;
	cout << setfill('-') << setw(100) << "" << endl;
	cout << setfill(' ');

	for (int i = 0; i < count; i++) {
		int indexInClientArray;
		if (useSearchResults) {
			indexInClientArray = searchResultIndexes[i];
		}
		else {
			indexInClientArray = i;
		}

		const Client& currentClient = clientArray[indexInClientArray];

		string clientTypeStr = (clientArray[i].type == PRIVATE) ? "Private" : "Corporate";
		string branchName = "Not Found!";
		int branchId = currentClient.branch_id;
		for (int j = 0; j < branchCount; j++) {
			if (branchArray[j].id == branchId) {
				branchName = branchArray[j].name;
				break;
			}
		}
		cout << left << setw(5) << (i + 1) << "|"
		<< left << setw(5) << currentClient.id << "|"
		<< left << setw(30) << currentClient.name << "|"
		<< left << setw(15) << currentClient.surname << "|"
		<< left << setw(20) << branchName << "|"
		<< left << "Type" << endl;
	}
	cout << setfill('-') << setw(100) << "" << endl;
	cout << setfill(' ');
}

void displayAccounts(bool useSearchResults) {
	if (!useSearchResults) {
		loadAccounts();
	}
	loadClients();

	int count = useSearchResults ? searchResultCount : accountCount;

	cout << "\n Total Accounts found: " << count << endl;
	if (count == 0) {
		cout << (useSearchResults ? "No accounts found!" : "No account has been loaded") << endl;
		return;
	}

	cout << setfill('-') << setw(100) << "" << endl;
	cout << setfill(' ');
	cout << left << setw(5) << "#" << "|"
		<< left << setw(30) << "Account" << "|"
		<< left << setw(20) << "Owner" << "|"
		<< left << "Balance" << endl;
	cout << setfill('-') << setw(100) << "" << endl;
	cout << setfill(' ');

	for (int i = 0; i < count; i++) {
		int indexInAccountArray;
		if (useSearchResults) {
			indexInAccountArray = searchResultIndexes[i];
		}
		else {
			indexInAccountArray = i;
		}

		const Account& currentAccount = accountArray[indexInAccountArray];

		string clientName = "Not Found!";
		int clientId = currentAccount.owner_id;
		for (int j = 0; j < clientCount; j++) {
			if (clientArray[j].id == clientId) {
				if (clientArray[j].type == 0) { // 0:PRIVATE
					clientName = clientArray[j].name + " " + clientArray[j].surname;
				} else {
					clientName = clientArray[j].name;
				}
				break;
			}
		}

		cout << left << setw(5) << (i + 1) << "|"
		<< left << setw(30) << currentAccount.account_number << "|"
		<< left << setw(20) << clientName << "|"
		<< left << currentAccount.balance << endl;
	}
	cout << setfill('-') << setw(100) << "" << endl;
	cout << setfill(' ');
}