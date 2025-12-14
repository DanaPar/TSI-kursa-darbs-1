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

//ielade datus sarakstos
void loadBranches() {
	ifstream file(branchesDB);
	branchCount = 0;
	if (!file) {
		return;
	}
	string line;
	while (getline(file, line) && branchCount < MAX_COUNT) {
		stringstream ss(line);

		int temp_id;
		string temp_name;
		string temp_address;
		char seperator;

		if (!(ss >> temp_id)) {
			//ja neizdodas nolasisana, pariet uz nakamo liniju
			continue;
		}

		if (!(ss >> seperator) || seperator != '|') {
			continue;
		}

		if (!getline(ss, temp_name, '|')) {
			continue;
		}

		if (!getline(ss, temp_address)) {
			continue;
		}

		//ja visas dalas veiksmigi nolasitas:
		branchArray[branchCount].id = temp_id;
		branchArray[branchCount].name = temp_name;
		branchArray[branchCount].address = temp_address;

		branchCount++;
	}
	file.close();
}

void loadDepartments() {
	ifstream file(departmentsDB);
	departmentCount = 0;
	if (!file) {
		return;
	}

	string line;
	while (getline(file, line) && departmentCount < MAX_COUNT) {
		stringstream ss(line);

		int temp_id;
		string temp_name;
		int temp_branch_id;
		char seperator;

		if (!(ss >> temp_id)) {
			continue;
		}

		if (!(ss >> seperator) || seperator != '|') {
			continue;
		}

		if (!getline(ss, temp_name, '|')) {
			continue;
		}

		if (!(ss >> temp_branch_id)) {
			continue;
		}

		departmentArray[departmentCount].id = temp_id;
		departmentArray[departmentCount].name = temp_name;
		departmentArray[departmentCount].branch_id = temp_branch_id;

		departmentCount++;
	}
	file.close();
}

void loadEmployees() {
	ifstream file(employeesDB);
	employeeCount = 0;
	if (!file) {
		return;
	}
	string line;
	while (getline(file, line) && employeeCount < MAX_COUNT) {
		stringstream ss(line);
		int temp_id;
		string temp_name;
		string temp_surname;
		int temp_department_id;
		string temp_position;
		int temp_access_level;
		char seperator;

		if (!(ss >> temp_id) || !(ss >> seperator) || seperator != '|') continue;
		if (!getline(ss, temp_name, '|')) continue;
		if (!getline(ss, temp_surname, '|')) continue;
		if (!(ss >> temp_department_id) || !(ss >> seperator) || seperator != '|') continue;
		if (!getline(ss, temp_position, '|')) continue;
		if (!(ss >> temp_access_level)) continue;

		employeeArray[employeeCount].id = temp_id;
		employeeArray[employeeCount].name = temp_name;
		employeeArray[employeeCount].surname = temp_surname;
		employeeArray[employeeCount].department_id = temp_department_id;
		employeeArray[employeeCount].position = temp_position;
		employeeArray[employeeCount].access_level = static_cast<AccessLevel>(temp_access_level);

		employeeCount++;
	}
	file.close();
}

void loadClients() {
	ifstream file(clientsDB);
	clientCount = 0;
	if (!file) {
		return;
	}
	string line;
	while (getline(file, line) && clientCount < MAX_COUNT) {
		stringstream ss(line);

		int temp_id;
		string temp_name;
		string temp_surname;
		int temp_branch_id;
		int temp_type;
		char seperator;

		if (!(ss >> temp_id) || !(ss >> seperator) || seperator != '|') {
			continue;
		}

		if (!getline(ss, temp_name, '|')) {
			continue;
		}

		if (!getline(ss, temp_surname, '|')) {
			continue;
		}

		if (!(ss >> temp_branch_id) || !(ss >> seperator) || seperator != '|') {
			continue;
		}

		if (!(ss >> temp_type)) {
			continue;
		}

		clientArray[clientCount].id = temp_id;
		clientArray[clientCount].name = temp_name;
		clientArray[clientCount].surname = temp_surname;
		clientArray[clientCount].branch_id = temp_branch_id;
		clientArray[clientCount].type = static_cast<ClientType>(temp_type);

		clientCount++;
	}
	file.close();
}

void loadAccounts() {
	ifstream file(accountsDB);
	accountCount = 0;
	if (!file) {
		return;
	}
	string line;
	while (getline(file, line) && accountCount < MAX_COUNT) {
		stringstream ss(line);
		string temp_acc_nr;
		int temp_owner_id;
		double temp_balance;
		char seperator;

		if (!getline(ss, temp_acc_nr, '|')) continue;
		if (!(ss >> temp_owner_id) || !(ss >> seperator) || seperator != '|') continue;
		if (!(ss >> temp_balance)) continue;

		accountArray[accountCount].account_number = temp_acc_nr;
		accountArray[accountCount].owner_id = temp_owner_id;
		accountArray[accountCount].balance = temp_balance;

		accountCount++;
	}
	file.close();
}