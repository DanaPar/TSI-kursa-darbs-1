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

//parada datus ka numuretus sarakstus
void displayBranches() {
	loadBranches();
	cout << "\n Total Branches: " << branchCount << endl;
	if (branchCount == 0) {
		cout << "No branch has been loaded" << endl;
		return;
	}

	for (int i = 0; i < branchCount; i++) {
		//(i + 1) lietotaja izveles numurs
		cout << (i + 1) << ". " << branchArray[i].name << " (ID: " << branchArray[i].id << ")" << endl;
	}
	cout << "--------------------------------" << endl;
}

void displayDepartments() {
	loadDepartments();
	loadBranches();
	cout << "\n Total Departments : " << departmentCount << endl;
	if (departmentCount == 0) {
		cout << "No department has been loaded" << endl;
		return;
	}

	for (int i = 0; i < departmentCount; i++) {
		//(i + 1) lietotaja izveles numurs
		cout << (i + 1) << ". " << departmentArray[i].name << " (ID: " << departmentArray[i].id << ")";

		//papildus parada kurai filialei pieder
		string branchName = "Not Found!";
		for (int j = 0; j < branchCount; j++) {
			if (branchArray[j].id == departmentArray[i].branch_id) {
				branchName = branchArray[j].name;
				break;
			}
		}
		cout << ", Branch: " << branchName << ")" << endl;
	}
	cout << "--------------------------------" << endl;
}

void displayEmployees() {
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

void displayClients() {
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

void displayAccounts() {
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