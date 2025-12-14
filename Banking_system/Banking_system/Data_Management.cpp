#include "DataTypes.h"
#include "Functions.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

//visi faili, kas glaba datus
const string branchesDB = "branchesDB.txt";
const string departmentsDB = "departmentsDB.txt";
const string employeesDB = "employeesDB.txt";
const string clientsDB = "clientsDB.txt";
const string accountsDB = "accountsDB.txt";
const string paymentsDB = "paymentsDB.txt";

//globalie datu glabataji (masivi un skaititaji)
Branch branchArray[MAX_COUNT];
int branchCount = 0;
Department departmentArray[MAX_COUNT];
int departmentCount = 0;
Employee employeeArray[MAX_COUNT];
int employeeCount = 0;
Client clientArray[MAX_COUNT];
int clientCount = 0;
Account accountArray[MAX_COUNT];
int accountCount = 0;
Payment paymentArray[MAX_COUNT];
int paymentCount = 0;

void addBranch() {
	ofstream file(branchesDB, ios::app);
	if (!file) {
		cout << "Could not open file" << endl;
		return;
	}

	Branch branch;

	branch.id = generateBranchId();
	cout << "New Branch ID: " << branch.id << endl;
	cout << "Enter Branch name: ";
	getline(cin, branch.name);
	cout << "Enter Branch address: ";
	getline(cin, branch.address);

	file << branch.id << "|" << branch.name << "|" << branch.address << endl;
	file.close();
	cout << "Branch data added successfully!" << endl;

	//pec filiales pievienosanas ieladejam datus atkal, lai atjauninatu masivu
	loadBranches();
}

void addDepartment() {
	loadBranches();
	//nodalas nevar pastavet bez filiales
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
	cout << "Enter Department name: ";
	getline(cin, department.name);

	displayBranches();
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
	cout << "Enter employee name: ";
	getline(cin, employee.name);
	cout << "Enter employee surname: ";
	getline(cin, employee.surname);
	cout << "Enter employee position: ";
	getline(cin, employee.position);

	displayDepartments();
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
	cout << "Enter client name: ";
	getline(cin, client.name);
	cout << "Enter client surname: ";
	getline(cin, client.surname);

	displayBranches();
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
	displayClients();
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

void editBranch() {
	loadBranches();
	if (branchCount == 0) {
		cout << "No branch has been found!" << endl;
		return;
	}
	displayBranches();

	int option;
	cout << "Enter number of branch to edit (1 - " << branchCount << "): ";
	if (!(cin >> option) || option < 1 || option > branchCount) {
		cout << "Wrong input!" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return;
	}
	cin.ignore();

	Branch& branch = branchArray[option - 1]; // Atsauce uz elementu
	string newName, newAddress;

	cout << "\nEdit Branch: " << branch.name << " (ID: " << branch.id << ")" << endl;
	cout << "Enter new name of the Branch (current: " << branch.name << "): ";
	getline(cin, newName);
	if (!newName.empty()) {
		branch.name = newName;
	}
	cout << "Enter new address of the Branch (current: " << branch.address << "): ";
	getline(cin, newAddress);
	if (!newAddress.empty()) {
		branch.address = newAddress;
	}
	// Parraksta visu failu
	ofstream file(branchesDB, ios::trunc);
	if (!file) {
		cout << "Error opening file for writing!" << endl;
		return;
	}

	for (int i = 0; i < branchCount; i++) {
		file << branchArray[i].id << "|" << branchArray[i].name << "|" << branchArray[i].address << endl;
	}
	file.close();
	cout << "Branch data updated successfully!" << endl;
}

void editDepartment() {
	loadDepartments();
	loadBranches();
	if (departmentCount == 0) {
		cout << "No department has been found!" << endl;
		return;
	}
	displayDepartments();

	int option;
	cout << "Enter number of Department to edit (1 - " << departmentCount << "): ";
	if (!(cin >> option) || option < 1 || option > departmentCount) {
		cout << "Wrong input!" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return;
	}
	cin.ignore();

	Department& department = departmentArray[option - 1];
	string newName;

	cout << "\nEdit Department: " << department.name << " (ID: " << department.id << ")" << endl;
	cout << "Enter new name of the Department (current: " << department.name << "): ";
	getline(cin, newName);
	if (!newName.empty()) {
		department.name = newName;
	}

	// Filiales izveles atjaunosana (ja nepieciesams)
	if (branchCount > 0) {
		displayBranches();
		string newBranch;
		cout << "Choose new Branch (1 - " << branchCount << "), or leave blank to keep current one:";
		getline(cin, newBranch);


		if (!newBranch.empty()) {
			int branch_option;

			// Izmantojam stringstream, lai meginatu nolasit int no virknes
			stringstream ss(newBranch);

			// Parbaude, vai ss var pilniba nolasit skaitli 'branch_option'?
			// Un vai pec skaitla nav palikusas vel kadas rakstzimes (kas noraditu uz nederigu ievadi, piemeram, "12a")?
			if (ss >> branch_option && ss.eof()) {

				if (branch_option >= 1 && branch_option <= branchCount) {
					department.branch_id = branchArray[branch_option - 1].id;
				}
				else {
					cout << "Wrong input (number oustide range). Current branch saved." << endl;
				}
			}
			else {
				// Konvertesana neizdevas (ievade nebija skaitlis)
				cout << "Wrong input! Current branch saved." << endl;
			}
		}
		else {
			// Tuksa ievade
			cout << "Current branch saved!" << endl;
		}
	}

	// Parraksta visu failu
	ofstream file(departmentsDB, ios::trunc);
	if (!file) {
		cout << "Error opening file for writing!" << endl;
		return;
	}

	for (int i = 0; i < departmentCount; i++) {
		file << departmentArray[i].id << "|" << departmentArray[i].name << "|" << departmentArray[i].branch_id << endl;
	}
	file.close();
	cout << "Branch data updated successfully!" << endl;
}

void editEmployee() {
	loadEmployees();
	loadDepartments();
	if (employeeCount == 0) {
		cout << "No employee has been found!" << endl;
		return;
	}
	displayEmployees();

	int option;
	cout << "Enter number of Employee to edit (1 - " << employeeCount << "): ";
	if (!(cin >> option) || option < 1 || option > employeeCount) {
		cout << "Wrong input!" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return;
	}
	cin.ignore();

	Employee& employee = employeeArray[option - 1];
	string newName, newSurname, newPosition;

	cout << "\nEdit Employee: " << employee.name << " " << employee.surname << " (ID: " << employee.id << ")" << endl;
	cout << "Enter new name (current: " << employee.name << "): ";
	getline(cin, newName);
	if (!newName.empty()) {
		employee.name = newName;
	}
	cout << "Enter new surname (current: " << employee.surname << "): ";
	getline(cin, newSurname);
	if (!newSurname.empty()) {
		employee.surname = newSurname;
	}
	cout << "Enter new position (current: " << employee.position << "): ";
	getline(cin, newPosition);
	if (!newPosition.empty()) {
		employee.position = newPosition;
	}

	// Nodalas izveles atjaunosana
	if (departmentCount > 0) {
		displayDepartments();
		string newDepartment;
		cout << "Choose new department (1 - " << departmentCount << "), or leave blank to keep current one:";
		getline(cin, newDepartment);


		if (!newDepartment.empty()) {
			int department_option;

			stringstream ss(newDepartment);

			if (ss >> department_option && ss.eof()) {

				if (department_option >= 1 && department_option <= branchCount) {
					employee.department_id = departmentArray[department_option - 1].id;
				}
				else {
					cout << "Wrong input (number oustide range). Current department saved." << endl;
				}
			}
			else {
				cout << "Wrong input! Current department saved." << endl;
			}
		}
		else {
			// Tuksa ievade
			cout << "Current department saved" << endl;
		}
	}

	// Piekluves limena atjaunosana
	string newAccessLevel;
	cout << "Choose new Access Level (current: " << employee.access_level << ") or leave blank to keep current one:" << endl
		<< "0: GUEST, 1: BASIC_USER, 2: ADMIN, 3: SUPER_ADMIN" << endl;

	getline(cin, newAccessLevel);

	if (!newAccessLevel.empty()) {
		int access_option;
		stringstream ss(newAccessLevel);

		if (ss >> access_option && ss.eof()) {

			if (access_option >= 0 && access_option <= 3) {
				employee.access_level = static_cast<AccessLevel>(access_option);
			}
			else {
				cout << "Wrong input (number oustide range [0-3]). Current Access Level saved." << endl;
			}
		}
		else {
			cout << "Wrong input! Current Access Level saved." << endl;
		}
	}
	else {
		// Tuksa ievade
		cout << "Current Access level saved!" << endl;
	}

	// Parraksta visu failu
	ofstream file(employeesDB, ios::trunc);
	if (!file) {
		cout << "Error opening file for writing!" << endl;
		return;
	}

	for (int i = 0; i < employeeCount; i++) {
		file << employeeArray[i].id << "|" << employeeArray[i].name << "|" << employeeArray[i].surname
			<< "|" << employeeArray[i].department_id << "|" << employeeArray[i].position
			<< "|" << employeeArray[i].access_level << endl;
	}
	file.close();
	cout << "Employee data updated successfully!" << endl;
}

void editClient() {
	loadClients();
	loadBranches();
	if (clientCount == 0) {
		cout << "No client has been found!" << endl;
		return;
	}
	displayClients();

	int option;
	cout << "Enter number of Client to edit (1 - " << clientCount << "): ";
	if (!(cin >> option) || option < 1 || option > clientCount) {
		cout << "Wrong input!" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return;
	}
	cin.ignore();

	Client& client = clientArray[option - 1];
	string newName, newSurname;

	cout << "\nEdit Client: " << client.name << " " << client.surname << " (ID: " << client.id << ")" << endl;
	cout << "Enter new name (current: " << client.name << "): ";
	getline(cin, newName);
	if (!newName.empty()) {
		client.name = newName;
	}
	cout << "Enter new surname (current: " << client.surname << "): ";
	getline(cin, newSurname);
	if (!newSurname.empty()) {
		client.surname = newSurname;
	}

	// Filiales izveles atjaunosana
	if (branchCount > 0) {
		displayBranches();
		string newBranch;
		cout << "Choose new Branch (1 - " << branchCount << "), or leave blank to keep current one:";
		getline(cin, newBranch);


		if (!newBranch.empty()) {
			int branch_option;

			stringstream ss(newBranch);

			if (ss >> branch_option && ss.eof()) {

				if (branch_option >= 1 && branch_option <= branchCount) {
					client.branch_id = branchArray[branch_option - 1].id;
				}
				else {
					cout << "Wrong input (number oustide range). Current branch saved." << endl;
				}
			}
			else {
				// Konvertesana neizdevas (ievade nebija skaitlis)
				cout << "Wrong input! Current branch saved." << endl;
			}
		}
		else {
			// Tuksa ievade
			cout << "Current branch saved." << endl;
		}
	}

	// Klienta tipa atjaunošana
	string newClientType;
	cout << "Choose new client type (current: " << client.type << "):" << endl << "0: PRIVATE, 1: CORPORATE, or leave blank to keep current one:" << endl;
	getline(cin, newClientType);
	if (!newClientType.empty()) {
		int type_option;
		stringstream ss(newClientType);

		if (ss >> type_option && ss.eof()) {

			if (type_option == 0 || type_option == 1) {
				client.type = static_cast<ClientType>(type_option);
				string typeStr = (type_option == 0) ? "PRIVATE" : "CORPORATE";
			}
			else {
				cout << "Wrong input (number oustide range [0-1]). Current type saved" << endl;
			}
		}
		else {
			cout << "Wrong input! Current type saved." << endl;
		}
	}
	else {
		// Tuksa ievade
		cout << "Current type saved." << endl;
	}

	// Parraksta visu failu
	ofstream file(clientsDB, ios::trunc);
	if (!file) {
		cout << "Error opening file for writing!" << endl;
		return;
	}

	for (int i = 0; i < clientCount; i++) {
		file << clientArray[i].id << "|" << clientArray[i].name << "|" << clientArray[i].surname
			<< "|" << clientArray[i].branch_id << "|" << clientArray[i].type << endl;
	}
	file.close();
	cout << "Client data updated successfully!" << endl;
}

void searchBranches() {
	ifstream file(branchesDB);
	if (!file) {
		cout << "Could not open file" << endl;
		return;
	}

	string searchName;
	cout << "\nEnter branch name to find: ";
	cin >> searchName;
	cin.ignore();

	string line;
	while (getline(file, line)) {
		stringstream ss(line);
		string token;
		Branch branch;

		if (getline(ss, token, '|')) {
			branch.id = stoi(token);
		}
		if (getline(ss, token, '|')) {
			branch.name = token;
		}
		if (getline(ss, token)) {
			branch.address = token;
		}

		if (branch.name == searchName) {
			cout << "Branch " << searchName << " has adress: " << branch.address << endl;
			file.close();
			return;
		}
	}
	file.close();
	cout << "Branch with name " << searchName << " doesnt exist!" << endl;
}

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
