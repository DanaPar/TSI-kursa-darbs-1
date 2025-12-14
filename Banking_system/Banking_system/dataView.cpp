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

void displayBranches(bool useSearchResults) {
	//ja jaatelo viss saraksts, tad jaielade visi dati
	if (!useSearchResults) {
		loadBranches();
	}
	
	int count = useSearchResults ? searchResultCount : branchCount;

	cout << "\n Total Branches: " << count << endl;
	if (count == 0) {
		cout << (useSearchResults ? "No brances found!" : "No branch has been loaded") << endl;
		return;
	}

	for (int i = 0; i < count; i++) {
		int indexInBranchArray;
		//ja izmantojam atlases
		if (useSearchResults) {
			indexInBranchArray = searchResultIndexes[i];
		}
		else {
			indexInBranchArray = i;
		}

		//pieklust fialiales strukturai caur indexu
		const Branch& currentBranch = branchArray[indexInBranchArray];

		//(i + 1) lietotaja izveles numurs
		cout << (i + 1) << ". " << currentBranch.name << " (ID: " << currentBranch.id << ", Adress: " << currentBranch.address << ")" << endl;
	}
	cout << "--------------------------------" << endl;
}

void displayDepartments(bool useSearchResults) {
	if (!useSearchResults) {
		loadDepartments();
		loadBranches();
	}

	int count = useSearchResults ? searchResultCount : departmentCount;

	cout << "\n Total Departments : " << count << endl;
	if (count == 0) {
		cout << (useSearchResults ? "No departments found!" : "No department has been loaded") << endl;
		return;
	}

	for (int i = 0; i < count; i++) {
		int indexInDepartmentArray;
		if (useSearchResults) {
			indexInDepartmentArray = searchResultIndexes[i];
		}
		else {
			indexInDepartmentArray = i;
		}

		const Department& currentDepartment = departmentArray[indexInDepartmentArray];

		cout << (i + 1) << ". " << currentDepartment.name << " (ID: " << currentDepartment.id << ")";

		string branchName = "Not Found!";
		int branchId = currentDepartment.branch_id;
		for (int j = 0; j < branchCount; j++) {
			if (branchArray[j].id == branchId) {
				branchName = branchArray[j].name;
				break;
			}
		}
		cout << ", Branch: " << branchName << ")" << endl;
	}
	cout << "--------------------------------" << endl;
}

void displayEmployees(bool useSearchResults) {
	loadEmployees();
	cout << "\n Total Employees: " << employeeCount << endl;
	if (employeeCount == 0) {
		cout << "No employee has been found" << endl;
		return;
	}

	for (int i = 0; i < employeeCount; i++) {
		// Konverte enum uz lasamu tekstu
		string accessLevelStr;
		switch (employeeArray[i].access_level) {
		case GUEST: accessLevelStr = "GUEST"; break;
		case BASIC_USER: accessLevelStr = "BASIC_USER"; break;
		case ADMIN: accessLevelStr = "ADMIN"; break;
		case SUPER_ADMIN: accessLevelStr = "SUPER_ADMIN"; break;
		default: accessLevelStr = "Unknown"; break;
		}

		cout << (i + 1) << ". " << employeeArray[i].name << " " << employeeArray[i].surname
			<< " (ID: " << employeeArray[i].id << ", Position: " << employeeArray[i].position
			<< ", Access Level: " << accessLevelStr << ")" << endl;
	}
	cout << "--------------------------------" << endl;
}

void displayClients(bool useSearchResults) {
	loadClients();
	cout << "\n Total Cleints: " << clientCount << endl;
	if (clientCount == 0) {
		cout << "No client has been found" << endl;
		return;
	}

	for (int i = 0; i < clientCount; i++) {
		string clientTypeStr = (clientArray[i].type == PRIVATE) ? "Private" : "Corporate";
		//(i + 1) lietotaja izveles numurs
		cout << (i + 1) << ". " << clientArray[i].name << " " << clientArray[i].surname << " (ID: " << clientArray[i].id << ", Type: " << clientTypeStr << ")" << endl;
	}
	cout << "--------------------------------" << endl;
}

void displayAccounts(bool useSearchResults) {
	loadAccounts();
	cout << "\n Total Accounts: " << accountCount << endl;
	if (accountCount == 0) {
		cout << "No account has been found" << endl;
		return;
	}

	for (int i = 0; i < accountCount; i++) {
		cout << (i + 1) << ". Account Nr: " << accountArray[i].account_number
			<< " (Client ID: " << accountArray[i].owner_id
			<< ", Balance: " << fixed << setprecision(2) << accountArray[i].balance << " EUR)" << endl;
	}
	cout << "--------------------------------" << endl;
}