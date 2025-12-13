#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib> //priekš rand() un srand()
#include <ctime>
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
	string account_number;
	int owner_id;
	double balance;
};

struct Payment {
	long id;
	float amount;
	string payerAccNr;
	string receiverAccNr;
	string detailsOfPayment;
	struct Date date;
};

//GLOBĀLIE DATU GLABĀTĀJI (MASĪVI)

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

//FUNKCIJU DEKLARĀCIJAS
void addBranch();
void addDepartment();
void addEmployee();
void addClient();
void addAccount();
void addPayment(); //ToDo create function

void loadBranches();
void loadDepartments();
void loadEmployees();
void loadClients();
void loadAccounts();
void loadPayments(); //ToDo create

void displayBranches();
void displayDepartments();
void displayEmployees();
void displayClients();
void displayAccounts();
void displayPayments(); //ToDo

void editBranch();
void editDepartment();
void editEmployee();
void editClient();
void editAccount(); //ToDo
void editPayment(); //ToDo

string generateAccountNumber();
bool isAccountNumberUnique(const string& accountNumber);

int main() {
	// while(true) {
	// 	addAccount();
	// }
	editClient();
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

void addAccount() {
	loadClients();
	if(clientCount == 0) {
		cout << "Nav pievienots neviens klients! Vispirms pievienojiet klientu!";
		return;
	}

	ofstream file(accountsDB, ios::app);
	if (!file) {
		cout << "Could not open file" << endl;
		return;
	}

	Account account;

	account.account_number = generateAccountNumber();

	displayClients();
	int option;
	bool valid_choice = false;
	while (!valid_choice) {
		cout << "Izvēlies kuram klientam pieder šis konts (izvēlies atbilstošo numuru 1 - " << clientCount << "): ";
		cin >> option;

		if (option >= 1 && option <= clientCount) {
			account.owner_id = clientArray[option - 1].id;
			valid_choice = true;
		}
		else {
			cout << "Nederīga izvēle, ievadi numuru no 1 līdz " << clientCount << endl;
		}
	}
	cin.ignore();

	cout << "Ievadi starta balansu: ";
	cin >> account.balance;
	cin.ignore();

	file << account.account_number << "|" << account.owner_id << "|" << account.balance << endl;
	file.close();
	cout << "Konta informācija veiksmīgi pievienota!";
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

void loadEmployees() {
	ifstream file(employeesDB);
	employeeCount = 0;
	if(!file) {
		return;
	}
	string line;
	while(getline(file,line) && employeeCount < MAX_COUNT) {
		stringstream ss(line);
		int temp_id;
		string temp_name;
		string temp_surname;
		int temp_department_id;
		string temp_position;
		int temp_access_level;
		char seperator;

		// Ielādes loģika no faila, pārbaudot atdalītājus '|'
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
	if(!file) {
		return;
	}
	string line;
	while(getline(file,line) && clientCount < MAX_COUNT) {
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

		if(!(ss >> temp_type)) {
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
	if(!file) {
		return;
	}
	string line;
	while(getline(file,line) && accountCount < MAX_COUNT) {
		stringstream ss(line);
		string temp_acc_nr;
		int temp_owner_id;
		double temp_balance;
		char seperator;

		// Ielādes loģika no faila, pārbaudot atdalītājus '|'
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
//parāda filiāles kā numurētu sarakstu
void displayBranches() {
	loadBranches();
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

void displayEmployees() {
	loadEmployees();
	cout << "\n --- Pieejamie darbinieki: " << employeeCount << endl;
	if (employeeCount == 0) {
		cout << "Nav neviena darbinieka" << endl;
		return;
	}

	for (int i = 0; i < employeeCount; i++) {
		// Konvertē enum uz lasāmu tekstu
		string accessLevelStr;
		switch(employeeArray[i].access_level) {
			case GUEST: accessLevelStr = "GUEST"; break;
			case BASIC_USER: accessLevelStr = "BASIC_USER"; break;
			case ADMIN: accessLevelStr = "ADMIN"; break;
			case SUPER_ADMIN: accessLevelStr = "SUPER_ADMIN"; break;
			default: accessLevelStr = "Nezināms"; break;
		}

		cout << (i + 1) << ". " << employeeArray[i].name << " " << employeeArray[i].surname
			 << " (ID: " << employeeArray[i].id << ", Amats: " << employeeArray[i].position
			 << ", Piekļuves līmenis: " << accessLevelStr << ")" << endl;
	}
	cout << "--------------------------------" << endl;
}

void displayClients() {
	loadClients();
	cout << "\n --- Pieejamie klienti: " << clientCount << endl;
	if (clientCount == 0) {
		cout << "Nav neviena klienta" << endl;
		return;
	}

	for (int i = 0; i < clientCount; i++) {
		string clientTypeStr = (clientArray[i].type == PRIVATE) ? "Privātpersona" : "Uzņēmums";
		//(i + 1) lietotāja izvēles numurs
		cout << (i + 1) << ". " << clientArray[i].name << " " << clientArray[i].surname << " (ID: " << clientArray[i].id << ", Tips: " << clientTypeStr << ")" << endl;
	}
	cout << "--------------------------------" << endl;
}

void displayAccounts() {
	loadAccounts();
	cout << "\n --- Pieejamie konti: " << accountCount << endl;
	if (accountCount == 0) {
		cout << "Nav neviena konta" << endl;
		return;
	}

	for (int i = 0; i < accountCount; i++) {
		cout << (i + 1) << ". Konts Nr: " << accountArray[i].account_number
			 << " (Klienta ID: " << accountArray[i].owner_id
			 << ", Atlikums: " << fixed << setprecision(2) << accountArray[i].balance << " EUR)" << endl;
	}
	cout << "--------------------------------" << endl;
}

void editBranch() {
	loadBranches();
	if (branchCount == 0) {
		cout << "Nav nevienas filiāles, ko labot!" << endl;
		return;
	}
	displayBranches();

	int option;
	cout << "Ievadiet filiāles numuru, kuru vēlaties labot (1 - " << branchCount << "): ";
	if (!(cin >> option) || option < 1 || option > branchCount) {
		cout << "Nederīga izvēle." << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return;
	}
	cin.ignore();

	Branch& branch = branchArray[option - 1]; // Atsauce uz elementu
	string newName, newAddress;

	cout << "\nLabot Filiāli: " << branch.name << " (ID: " << branch.id << ")" << endl;
	cout << "Ievadiet jauno filiāles nosaukumu (pašreizējais: " << branch.name << "): ";
	getline(cin, newName);
	if(!newName.empty()) {
		branch.name = newName;
	}
	cout << "Ievadiet jauno filiāles adresi (pašreizējā: " << branch.address << "): ";
	getline(cin, newAddress);
	if(!newAddress.empty()) {
		branch.address = newAddress;
	}
	// Pārraksta visu failu
	ofstream file(branchesDB, ios::trunc);
	if (!file) {
		cout << "Kļūda atverot failu rakstīšanai!" << endl;
		return;
	}

	for (int i = 0; i < branchCount; i++) {
		file << branchArray[i].id << "|" << branchArray[i].name << "|" << branchArray[i].address << endl;
	}
	file.close();
	cout << "Filiāles dati veiksmīgi atjaunināti!" << endl;
}

void editDepartment() {
	loadDepartments();
	loadBranches();
	if (departmentCount == 0) {
		cout << "Nav nevienas nodaļas, ko labot!" << endl;
		return;
	}
	displayDepartments();

	int option;
	cout << "Ievadiet nodaļas numuru, kuru vēlaties labot (1 - " << departmentCount << "): ";
	if (!(cin >> option) || option < 1 || option > departmentCount) {
		cout << "Nederīga izvēle." << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return;
	}
	cin.ignore();

	Department& department = departmentArray[option - 1];
	string newName;

	cout << "\nLabot Nodaļu: " << department.name << " (ID: " << department.id << ")" << endl;
	cout << "Ievadiet jauno nodaļas nosaukumu (pašreizējais: " << department.name << "): ";
	getline(cin, newName);
	if(!newName.empty()) {
		department.name = newName;
	}

	// Filiāles izvēles atjaunošana (ja nepieciešams)
	if (branchCount > 0) {
		displayBranches();
		string newBranch;
		cout << "Izvēlies jauno filiāli (1 - " << branchCount << "), vai atstāj tukšu lai paturētu esošo:";
		getline(cin, newBranch);


		if (!newBranch.empty()) {
			int branch_option;

			// Izmantojam stringstream, lai mēģinātu nolasīt int no virknes
			stringstream ss(newBranch);

			// Pārbaude: Vai ss var pilnībā nolasīt skaitli 'branch_option'?
			// Un vai pēc skaitļa nav palikušas vēl kādas rakstzīmes (kas norādītu uz nederīgu ievadi, piemēram, "12a")?
			if (ss >> branch_option && ss.eof()) {

				if (branch_option >= 1 && branch_option <= branchCount) {
					department.branch_id = branchArray[branch_option - 1].id;
					cout << "Filiāle veiksmīgi atjaunināta." << endl;
				} else {
					cout << "Nederīga izvēle (skaitlis ārpus diapazona). Pašreizējā filiāle saglabāta." << endl;
				}
			} else {
				// Konvertēšana neizdevās (ievade nebija skaitlis)
				cout << "Nederīga ievade. Pašreizējā filiāle saglabāta." << endl;
			}
		} else {
			// Tukša ievade
			cout << "Pašreizējā filiāle saglabāta." << endl;
		}
	}

	// Pārraksta visu failu
	ofstream file(departmentsDB, ios::trunc);
	if (!file) {
		cout << "Kļūda atverot failu rakstīšanai!" << endl;
		return;
	}

	for (int i = 0; i < departmentCount; i++) {
		file << departmentArray[i].id << "|" << departmentArray[i].name << "|" << departmentArray[i].branch_id << endl;
	}
	file.close();
	cout << "Nodaļas dati veiksmīgi atjaunināti!" << endl;
}

void editEmployee() {
	loadEmployees();
	loadDepartments();
	if (employeeCount == 0) {
		cout << "Nav neviena darbinieka, ko labot!" << endl;
		return;
	}
	displayEmployees();

	int option;
	cout << "Ievadiet darbinieka numuru, kuru vēlaties labot (1 - " << employeeCount << "): ";
	if (!(cin >> option) || option < 1 || option > employeeCount) {
		cout << "Nederīga izvēle." << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return;
	}
	cin.ignore();

	Employee& employee = employeeArray[option - 1];
	string newName, newSurname, newPosition;

	cout << "\nLabot Darbinieku: " << employee.name << " " << employee.surname << " (ID: " << employee.id << ")" << endl;
	cout << "Ievadiet jauno vārdu (pašreizējais: " << employee.name << "): ";
	getline(cin, newName);
	if(!newName.empty()) {
		employee.name = newName;
	}
	cout << "Ievadiet jauno uzvārdu (pašreizējais: " << employee.surname << "): ";
	getline(cin, newSurname);
	if(!newSurname.empty()) {
		employee.surname = newSurname;
	}
	cout << "Ievadiet jauno amatu (pašreizējais: " << employee.position << "): ";
	getline(cin, newPosition);
	if(!newPosition.empty()) {
		employee.position = newPosition;
	}

	// Nodaļas izvēles atjaunošana
	if (departmentCount > 0) {
		displayDepartments();
		string newDepartment;
		cout << "Izvēlies jauno nodaļu (1 - " << departmentCount << "), vai atstāj tukšu lai paturētu esošo:";
		getline(cin, newDepartment);


		if (!newDepartment.empty()) {
			int department_option;

			stringstream ss(newDepartment);

			if (ss >> department_option && ss.eof()) {

				if (department_option >= 1 && department_option <= branchCount) {
					employee.department_id = departmentArray[department_option - 1].id;
					cout << "Nodaļa veiksmīgi atjaunināta." << endl;
				} else {
					cout << "Nederīga izvēle (skaitlis ārpus diapazona). Pašreizējā nodaļa saglabāta." << endl;
				}
			} else {
				cout << "Nederīga ievade. Pašreizējā nodaļa saglabāta." << endl;
			}
		} else {
			// Tukša ievade
			cout << "Pašreizējā nodaļa saglabāta." << endl;
		}
	}

	// Piekļuves līmeņa atjaunošana
	string newAccessLevel;
	cout << "Izvēlies jauno piekļuves līmeni (pašreizējais: " << employee.access_level << "). Atstāj tukšu, lai paturētu esošo:" << endl
		 << "0: GUEST, 1: BASIC_USER, 2: ADMIN, 3: SUPER_ADMIN" << endl;

	getline(cin, newAccessLevel);

	if (!newAccessLevel.empty()) {
		int access_option;
		stringstream ss(newAccessLevel);

		if (ss >> access_option && ss.eof()) {

			if (access_option >= 0 && access_option <= 3) {
				employee.access_level = static_cast<AccessLevel>(access_option);
				cout << "Piekļuves līmenis veiksmīgi atjaunināts uz: " << access_option << endl;
			} else {
				cout << "Nederīga izvēle (skaitlis ārpus diapazona [0-3]). Pašreizējais līmenis saglabāts." << endl;
			}
		} else {
			cout << "Nederīga ievade. Pašreizējais līmenis saglabāts." << endl;
		}
	} else {
		// Tukša ievade
		cout << "Pašreizējais piekļuves līmenis saglabāts." << endl;
	}

	// Pārraksta visu failu
	ofstream file(employeesDB, ios::trunc);
	if (!file) {
		cout << "Kļūda atverot failu rakstīšanai!" << endl;
		return;
	}

	for (int i = 0; i < employeeCount; i++) {
		file << employeeArray[i].id << "|" << employeeArray[i].name << "|" << employeeArray[i].surname
			 << "|" << employeeArray[i].department_id << "|" << employeeArray[i].position
			 << "|" << employeeArray[i].access_level << endl;
	}
	file.close();
	cout << "Darbinieka dati veiksmīgi atjaunināti!" << endl;
}

void editClient() {
	loadClients();
	loadBranches();
	if (clientCount == 0) {
		cout << "Nav neviena klienta, ko labot!" << endl;
		return;
	}
	displayClients();

	int option;
	cout << "Ievadiet klienta numuru, kuru vēlaties labot (1 - " << clientCount << "): ";
	if (!(cin >> option) || option < 1 || option > clientCount) {
		cout << "Nederīga izvēle." << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return;
	}
	cin.ignore();

	Client& client = clientArray[option - 1];
	string newName, newSurname;

	cout << "\nLabot Klientu: " << client.name << " " << client.surname << " (ID: " << client.id << ")" << endl;
	cout << "Ievadiet jauno vārdu (pašreizējais: " << client.name << "): ";
	getline(cin, newName);
	if(!newName.empty()) {
		client.name = newName;
	}
	cout << "Ievadiet jauno uzvārdu (pašreizējais: " << client.surname << "): ";
	getline(cin, newSurname);
	if(!newSurname.empty()) {
		client.surname = newSurname;
	}

	// Filiāles izvēles atjaunošana
	if (branchCount > 0) {
		displayBranches();
		string newBranch;
		cout << "Izvēlies jauno filiāli (1 - " << branchCount << "), vai atstāj tukšu lai paturētu esošo:";
		getline(cin, newBranch);


		if (!newBranch.empty()) {
			int branch_option;

			stringstream ss(newBranch);

			if (ss >> branch_option && ss.eof()) {

				if (branch_option >= 1 && branch_option <= branchCount) {
					client.branch_id = branchArray[branch_option - 1].id;
					cout << "Filiāle veiksmīgi atjaunināta." << endl;
				} else {
					cout << "Nederīga izvēle (skaitlis ārpus diapazona). Pašreizējā filiāle saglabāta." << endl;
				}
			} else {
				// Konvertēšana neizdevās (ievade nebija skaitlis)
				cout << "Nederīga ievade. Pašreizējā filiāle saglabāta." << endl;
			}
		} else {
			// Tukša ievade
			cout << "Pašreizējā filiāle saglabāta." << endl;
		}
	}

	// Klienta tipa atjaunošana
	string newClientType;
	cout << "Izvēlies jauno klienta tipu (pašreizējais: " << client.type << "):" << endl << "0: PRIVATE (Privātpersona), 1: CORPORATE (Uzņēmums)" << endl;
	getline(cin, newClientType);
	if (!newClientType.empty()) {
		int type_option;
		stringstream ss(newClientType);

		if (ss >> type_option && ss.eof()) {

			if (type_option == 0 || type_option == 1) {
				client.type = static_cast<ClientType>(type_option);
				string typeStr = (type_option == 0) ? "PRIVATE (Privātpersona" : "CORPORATE (Uzņēmums)";
				cout << "Klienta tips veiksmīgi atjaunināts uz: " << typeStr << endl;
			} else {
				cout << "Nederīga izvēle (skaitlis ārpus diapazona [0-1]). Pašreizējais veids saglabāts." << endl;
			}
		} else {
			cout << "Nederīga ievade. Pašreizējais veids saglabāts." << endl;
		}
	} else {
		// Tukša ievade
		cout << "Pašreizējais veids saglabāts." << endl;
	}

	// Pārraksta visu failu
	ofstream file(clientsDB, ios::trunc);
	if (!file) {
		cout << "Kļūda atverot failu rakstīšanai!" << endl;
		return;
	}

	for (int i = 0; i < clientCount; i++) {
		file << clientArray[i].id << "|" << clientArray[i].name << "|" << clientArray[i].surname
			 << "|" << clientArray[i].branch_id << "|" << clientArray[i].type << endl;
	}
	file.close();
	cout << "Klienta dati veiksmīgi atjaunināti!" << endl;
}

string generateAccountNumber() {
	static bool seeded = false;
	if(!seeded) {
		srand(time(0));
		seeded = true;
	}
	const string countryCode = "LV";
	const string bankCode = "TSI";
	string newAccountNumber;

	//sākas cikls, kas turpinas līdz numurs ir unikāls
	do {
		//ģenerē kontroles skaitli
		int controlDigitsInt = (rand() % 90) + 10;
		string controlDigits = to_string(controlDigitsInt);

		stringstream localAcc;
		for (int i = 0; i < 12; i++) {
			localAcc << (rand() % 10);
		}
		string localAccountNumber = localAcc.str();
		newAccountNumber = countryCode + controlDigits + bankCode + localAccountNumber;
	 }
	while (!isAccountNumberUnique(newAccountNumber));

	return newAccountNumber;
}

bool isAccountNumberUnique(const string& accountNumber) {
	ifstream file(accountsDB);
	//ja failu nevar atvērt pieņemam ka tas ir tukšs un pievienojam pirmo kontu
	if (!file) {
		return true;
	}

	string line;
	while (getline(file, line)) {
		stringstream ss(line);
		string fileAccountNumber;

		// Mēģinām nolasīt konta numuru līdz pirmajam atdalītājam '|'
		if (getline(ss, fileAccountNumber, '|')) {
			if (fileAccountNumber == accountNumber) {
				file.close();
				return false; // Konta numurs NAV unikāls (atrasts failā)
			}
		}
	}
	file.close();
	return true;
}
