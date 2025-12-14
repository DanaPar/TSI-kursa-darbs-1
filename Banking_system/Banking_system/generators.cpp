#include "dataTypes.h"
#include "functions.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <algorithm>

using namespace std;

int generateBranchId() {
	loadBranches();
	int maxId = 0;
	for (int i = 0; i < branchCount; i++) {
		if (branchArray[i].id > maxId) {
			maxId = branchArray[i].id;
		}
	}
	return maxId + 1;
}

int generateDepartmentId() {
	loadDepartments();
	int maxId = 0;
	for (int i = 0; i < departmentCount; i++) {
		if (departmentArray[i].id > maxId) {
			maxId = departmentArray[i].id;
		}
	}
	return maxId + 1;
}

int generateEmployeeId() {
	loadEmployees();
	int maxId = 0;
	for (int i = 0; i < employeeCount; i++) {
		if (employeeArray[i].id > maxId) {
			maxId = employeeArray[i].id;
		}
	}
	return maxId + 1;
}

int generateClientId() {
	loadClients();
	int maxId = 0;
	for (int i = 0; i < clientCount; i++) {
		if (clientArray[i].id > maxId) {
			maxId = clientArray[i].id;
		}
	}
	return maxId + 1;
}

string generateAccountNumber() {
	static bool seeded = false;
	if (!seeded) {
		srand(time(0));
		seeded = true;
	}
	const string countryCode = "LV";
	const string bankCode = "TSI";
	string newAccountNumber;

	//sakas cikls, kas turpinas lidz numurs ir unikals
	do {
		//genere kontroles skaitli
		int controlDigitsInt = (rand() % 90) + 10;
		string controlDigits = to_string(controlDigitsInt);

		stringstream localAcc;
		for (int i = 0; i < 12; i++) {
			localAcc << (rand() % 10);
		}
		string localAccountNumber = localAcc.str();
		newAccountNumber = countryCode + controlDigits + bankCode + localAccountNumber;
	} while (!isAccountNumberUnique(newAccountNumber));

	return newAccountNumber;
}

bool isAccountNumberUnique(const string& accountNumber) {
	ifstream file(accountsDB);
	//ja failu nevar atvert pienemam ka tas ir tukss un pievienojam pirmo kontu
	if (!file) {
		return true;
	}

	string line;
	while (getline(file, line)) {
		stringstream ss(line);
		string fileAccountNumber;

		// Meginam nolasit konta numuru lidz pirmajam atdalitajam '|'
		if (getline(ss, fileAccountNumber, '|')) {
			if (fileAccountNumber == accountNumber) {
				file.close();
				return false; // Konta numurs NAV unikals (atrasts faila)
			}
		}
	}
	file.close();
	return true;
}

string toLower(const string& str) {
	string lowerStr = str;
	// Uses std::transform and ::tolower (from <algorithm> and <cctype>)
	transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
	return lowerStr;
}