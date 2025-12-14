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