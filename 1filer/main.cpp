#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
const int MAX_BRANCHES = 100;
//tiek definēti visi faili
const string branchesDB = "branchesDB.txt";
const string departmentsDB = "departmentsDB.txt";
const string employeesDB = "employeesDB.txt";
const string clientsDB = "clientsDB.txt";
const string accountsDB = "accountsDB.txt";
const string paymentsDB = "paymentsDB.txt";

//ieliktās datu struktūras
struct Date {
	int day = 0;
	int month = 0;
	int year = 0;
};

enum AccessLevel {
	GUEST = 0,
	BASIC_USER = 1,
	ADMIN = 2,
	SUPER_ADMIN = 3
  };

enum ClientType {
	PRIVATE = 0,
	CORPORATE = 1
  };

//-----objektu struktūras -----//

struct Branch {
	int id;
	string name;
	string address;
};

struct Department {
	int id;
	string name;
	int branch_id;
};

struct Employee {
	int id;
	string name;
	string surname;
	int department_id;
	string position;
	enum AccessLevel access_level;
};

struct Client {
	int id;
	char name[20];
	char surname[20];
	enum ClientType type;;
};

struct Account {
	char account_number[20]; //pēc tam noteiksim vajadzīgo skaitu
	int owner_id;
	double balance;
	char currency[3];
	char type; //ToDO aizvietot ar enumu vai ko tādu
	//account type
};

struct Payment {
	long id;
	float amount;
	char payerAccNr[20];
	char receiverAccNr[20];
	string detailsOfPayment;
	struct Date date;
};

//GLOBĀLIE DATU GLABĀTĀJI (MASĪVI)
//globāls masīvs filiāļu glabāšanai
Branch branchArray[MAX_BRANCHES];
int branchCount = 0;

//FUNKCIJU DEKLARĀCIJAS
void addBranch();
void addDepartment();
void loadBranches();
void displayBranches();

 int main() {
 	addDepartment();
 	// int option = 0;
 	// cout << "\n=============================================" << endl;
 	// cout << "BANKAS INFORMĀCIJAS SISTĒMA" << endl;
 	// cout << "=============================================" << endl;
 	// while (true) {
 	// 	cout << "1. Filiāļu un Nodaļu Pārvaldība" << endl;
 	// 	cout << "2. Darbinieku Pārvaldība" << endl;
 	// 	cout << "3. Klientu Pārvaldība" << endl;
 	// 	cout << "4. Kontu Pārvaldība" << endl;
 	// 	cout << "5. Maksājumu Pārvaldība" << endl;
 	// 	cout << "6. Saglabāt Datus un Iziet" << endl;
 	// 	cout << "Ievadiet izvēli: ";
 	// 	cin >> option;
	 //
 	// 	if (option == 1) {
 	// 		//add();
 	// 	}
 	// 	else if (option == 2) {
 	// 		//view();
 	// 	}
 	// 	else if (option == 3) {
 	// 		//search();
 	// 	}
 	// 	else if (option == 6) {
 	// 		exit(0);
 	// 	}
 	// 	else {
 	// 		cout << "Nepareiza izvēle. Izvēlies variantu no 1 līdz 6\n";
 	// 	}
 	// }
 	return 0;
 }

void addBranch() {
 	loadBranches();
	ofstream file(branchesDB, ios::app);
	if (!file) {
		cout << "Could not open file" << endl;
		return;
	}

	Branch branch;
	cout << "\nIevadi filiāles identifikatoru: ";
	cin >> branch.id;
	cin.ignore();
	cout << "Ievadi filiāles nosaukumu: ";
	getline(cin, branch.name);
 	cout << "Ievadi filiāles adresi: ";
 	getline(cin, branch.address);

	file << branch.id << "|" << branch.name << "|" << branch.address << endl;
	file.close();
	cout << "Filiāles dati pievienoti veiksmīgi!" << endl;

 	//pēc filiāles pievienošanas ielādējam datus atkal, lai atjauninātu masīvu
 	loadBranches();
}

void addDepartment() {
 	loadBranches();
 	//nodaļas nevar pastāvēt bez filiāles
 	if(branchCount == 0) {
 		cout << "Nav pievienota neviena filiāle! Vispirms pievienojiet filiāli!";
 		return;
 	}

 	ofstream file(departmentsDB, ios::app);
 	if (!file) {
 		cout << "Could not open file" << endl;
 		return;
 	}

 	Department department;

 	cout << "\nIevadi nodaļas identifikatoru: ";
 	cin >> department.id;
 	cin.ignore();
 	cout << "Ievadi nodaļas nosaukumu: ";
 	getline(cin, department.name);

 	displayBranches();
 	int option;
 	bool valid_choice = false;
 	while (!valid_choice) {
 		cout << "Izvēlies kurai filiālei pieder šī nodaļa (izvēlies atbilstošo numuru 1 - " << branchCount << "): ";
 		cin >> option;

 		if (option >= 1 && option <= branchCount) {
 			department.branch_id = branchArray[option - 1].id;
 			valid_choice = true;
 		}
 		else {
 			cout << "Nederīga izvēle, ievadi numuru no 1 līdz " << branchCount << endl;
 		}
 	}
 	cin.ignore();

 	file << department.id << "|" << department.name << "|" << department.branch_id << endl;
	file.close();
	cout << "Nodaļas dati pievienoti veiksmīgi!" << endl;
}

//ielādē filiāles sarakstā
void loadBranches() {
	ifstream file(branchesDB);
 	branchCount = 0;
 	if(!file) {
 		return;
 	}
 	string line;
 	while(getline(file,line) && branchCount < MAX_BRANCHES) {
 		stringstream ss(line);

 		int temp_id;
 		string temp_name;
 		string temp_address;
 		char seperator;

 		if (!(ss >> temp_id)) {
 			//ja neizdodas nolasīšana, pāriet uz nākamo līniju
 			continue;
 		}

 		if (!(ss >> seperator) || seperator != '|') {
 			continue;
 		}

 		if (!getline(ss, temp_name, '|')) {
 			continue;
 		}

 		if(!getline(ss, temp_address)) {
 			continue;
 		}

 		//ja visas daļas veiksmīgi nolasītas:
 		branchArray[branchCount].id = temp_id;
 		branchArray[branchCount].name = temp_name;
 		branchArray[branchCount].address = temp_address;

 		branchCount++;
 	}
 	file.close();
}



//parāda filiāles kā numurētu sarakstu
void displayBranches() {
 	cout << "\n --- Pieejamās filiāles: " << branchCount << endl;
 	if (branchCount == 0) {
 		cout << "Nav nevienas ielādētas filiāles" << endl;
 		return;
 	}

 	for (int i = 0; i < branchCount; i++) {
 		//(i + 1) lietotāja izvēles numurs
 		cout << (i + 1) << ". " << branchArray[i].name << " (ID: " << branchArray[i].id << ")" << endl;
 	}
 	cout << "--------------------------------" << endl;
 }














// void view() {
// 	ifstream file(FILENAME);
// 	if (!file) {
// 		cout << "Could not open file" << endl;
// 		return;
// 	}
//
// 	cout << endl;
// 	cout << left << setw(6) << setfill(' ') << "NR";
// 	cout << left << setw(17) << setfill(' ') << "DEPARTMENT NAME";
// 	cout << left << setw(17) << setfill(' ') << "PATIENTS" << endl;
// 	string line;
// 	while (getline(file, line)) {
// 		stringstream ss(line);
// 		string token;
// 		Department department;
//
// 		if (getline(ss, token, ',')) {
// 			department.depNum = stoi(token);
// 		}
// 		if (getline(ss, token, ',')) {
// 			department.depName = token;
// 		}
// 		if (getline(ss, token)) {
// 			department.patients = stoi(token);
// 		}
//
// 		cout << left << setw(6) << setfill(' ') << department.depNum;
// 		cout << left << setw(17) << setfill(' ') << department.depName;
// 		cout << left << setw(17) << setfill(' ') << department.patients << endl;
// 	}
// 	file.close();
// }

// void search() {
// 	ifstream file(FILENAME);
// 	if (!file) {
// 		cout << "Could not open file" << endl;
// 		return;
// 	}
//
// 	string searchName;
// 	cout << "\nEnter department name to find: ";
// 	cin >> searchName;
// 	cin.ignore();
//
// 	string line;
// 	while (getline(file, line)) {
// 		stringstream ss(line);
// 		string token;
// 		Department department;
//
// 		if (getline(ss, token, ',')) {
// 			department.depNum = stoi(token);
// 		}
// 		if (getline(ss, token, ',')) {
// 			department.depName = token;
// 		}
// 		if (getline(ss, token)) {
// 			department.patients = stoi(token);
// 		}
//
// 		if (department.depName == searchName) {
// 			cout << "Department " << searchName << " has " << department.patients << " patients" << endl;
// 			file.close();
// 			return;
// 		}
// 	}
// 	file.close();
// 	cout << "Department with name " << searchName << " doesnt exist!" << endl;
// }
