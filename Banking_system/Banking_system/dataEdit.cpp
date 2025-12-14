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

void editBranch() {
	loadBranches();
	if (branchCount == 0) {
		cout << "No branch has been found!" << endl;
		return;
	}
	displayBranches(false);

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
	displayDepartments(false);

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
		displayBranches(false);
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
	displayEmployees(false);

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
		displayDepartments(false);
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
	displayClients(false);

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
		displayBranches(false);
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
