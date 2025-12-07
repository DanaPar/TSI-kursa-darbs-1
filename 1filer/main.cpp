#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
const int MAX_COUNT = 100;
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
	string name;
	string surname;
	int branch_id;
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
Branch branchArray[MAX_COUNT];
int branchCount = 0;
//Globāls masīvs nodaļu glabāšanai
Department departmentArray[MAX_COUNT];
int departmentCount = 0;

//FUNKCIJU DEKLARĀCIJAS
void addBranch();
void addDepartment();
void addEmployee();
void addClient();
void addAccount();
void addPayment();
void loadBranches();
void displayBranches();
void loadDepartments();
void displayDepartments();

int main() {
 	addClient();
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

void addEmployee() {
	loadDepartments();

 	if(departmentCount == 0) {
 		cout << "Nav pievienota neviena nodaļa! Vispirms pievienojiet nodaļu!";
 		return;
 	}

 	ofstream file(employeesDB, ios::app);
 	if (!file) {
 		cout << "Could not open file" << endl;
 		return;
 	}

 	Employee employee;

 	cout << "\nIevadi darbinieka identifikatoru: ";
 	cin >> employee.id;
 	cin.ignore();
 	cout << "Ievadi darbinieka vārdu: ";
 	getline(cin, employee.name);
 	cout << "Ievadi darbinieka uzvārdu: ";
 	getline(cin, employee.surname);
 	cout << "Ievadi darbinieka amatu: ";
 	getline(cin, employee.position);

	//nodaļas izvēle
 	displayDepartments();
 	int option;
 	bool valid_choice = false;
 	while(!valid_choice) {
 		cout << "Izvēlies kurai nodaļai pieder šis darbinieks (izvēlies atbilstošo numuru 1 - " << departmentCount << "): ";
 		cin >> option;

 		if (option >= 1 && option <= departmentCount) {
 			employee.department_id = departmentArray[option - 1].id;
 			valid_choice = true;
 		}
 		else {
 			cout << "Nederīga izvēle, ievadi numuru no 1 līdz " << departmentCount << endl;
 		}
 	}
 	cin.ignore();

	//access level piešķiršana
 	int access_option;
 	valid_choice = false;
 	while(!valid_choice) {
 		cout << "Izvēlies piekļuves līmeni:" << endl
		<< "0: GUEST," << endl
		<< "1: BASIC_USER" << endl
		<< "2: ADMIN" << endl
		<< "3: SUPER_ADMIN" << endl;
 		cin >> access_option;
 		if(access_option >= 0 && access_option <=3) {
 			employee.access_level = static_cast<AccessLevel>(access_option);
 			valid_choice = true;
 		}
 		else {
 			cout << "Nederīga izvēle, ievadi numuru no 0 līdz 3" << endl;
 		}
 	}
	cin.ignore();

 	file << employee.id << "|" << employee.name << "|" << employee.surname << "|" << employee.department_id << "|" << employee.position << "|" << employee.access_level << endl;
	file.close();
 	cout << "Darbinieka dati veiksmīgi pievienoti!";

}

void addClient() {
	loadBranches();
	//nodaļas nevar pastāvēt bez filiāles
	if(branchCount == 0) {
		cout << "Nav pievienota neviena filiāle! Vispirms pievienojiet filiāli!";
		return;
	}

	ofstream file(clientsDB, ios::app);
	if (!file) {
		cout << "Could not open file" << endl;
		return;
	}

	Client client;

	cout << "\nIevadi klienta identifikatoru: ";
	cin >> client.id;
	cin.ignore();
	cout << "Ievadi klienta vārdu: ";
	getline(cin, client.name);
	cout << "Ievadi klienta uzvārdu: ";
	getline(cin, client.surname);

	displayBranches();
	int option;
	bool valid_choice = false;
	while (!valid_choice) {
		cout << "Izvēlies kurai filiālei pieder šis klients (izvēlies atbilstošo numuru 1 - " << branchCount << "): ";
		cin >> option;

		if (option >= 1 && option <= branchCount) {
			client.branch_id = branchArray[option - 1].id;
			valid_choice = true;
		}
		else {
			cout << "Nederīga izvēle, ievadi numuru no 1 līdz " << branchCount << endl;
		}
	}
	cin.ignore();

	int client_type_option;
	valid_choice = false;
	while(!valid_choice) {
		cout << "Izvēlies klienta tipu:" << endl
	   << "0: PRIVATE (Privātpersona)" << endl
	   << "1: CORPORATE (Uzņēmums)" << endl;
		cin >> client_type_option;
		if(client_type_option == 0 || client_type_option == 1) {
			client.type = static_cast<ClientType>(client_type_option);
			valid_choice = true;
		}
		else {
			cout << "Nederīga izvēle, ievadi numuru 0 vai 1" << endl;
		}
	}
	cin.ignore();

	file << client.id << "|" << client.name << "|" << client.surname << "|" << client.branch_id << "|" << client.type << endl;
	file.close();
	cout << "Klienta dati pievienoti veiksmīgi!" << endl;

}
//ielādē filiāles sarakstā
void loadBranches() {
	ifstream file(branchesDB);
 	branchCount = 0;
 	if(!file) {
 		return;
 	}
 	string line;
 	while(getline(file,line) && branchCount < MAX_COUNT) {
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

void loadDepartments() {
	ifstream file(departmentsDB);
 	departmentCount = 0;
 	if(!file) {
 		return;
 	}

 	string line;
 	while(getline(file,line) && departmentCount < MAX_COUNT) {
 		stringstream ss(line);

 		int temp_id;
 		string temp_name;
 		int temp_branch_id;
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

 		if(!(ss >> temp_branch_id)) {
 			continue;
 		}

 		//ja visas daļas veiksmīgi nolasītas:
 		departmentArray[departmentCount].id = temp_id;
 		departmentArray[departmentCount].name = temp_name;
 		departmentArray[departmentCount].branch_id = temp_branch_id;

 		departmentCount++;
 	}
 	file.close();
}

void displayDepartments() {
 	loadDepartments(); //ieladē nodaļas
 	loadBranches(); //ielādē filiāles, aizpildot branchArray (nepieciešams nosaukumiem
 	cout << "\n --- Pieejamās nodaļas: " << departmentCount << endl;
 	if (departmentCount == 0) {
 		cout << "Nav nevienas ielādētas nodaļas" << endl;
 		return;
 	}

 	for (int i = 0; i < departmentCount; i++) {
 		//(i + 1) lietotāja izvēles numurs
 		cout << (i + 1) << ". " << departmentArray[i].name << " (ID: " << departmentArray[i].id << ")";

 		//papildus parāda kurai filiālei pieder
 		string branchName = "Nav atrasts";
 		for (int j = 0; j < branchCount; j++) {
 			if (branchArray[j].id == departmentArray[i].branch_id) {
 				branchName = branchArray[j].name;
 				break;
 			}
 		}
 		cout << ", Filiāle: " << branchName << ")" << endl;
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
