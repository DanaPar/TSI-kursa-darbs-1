#ifndef DATATYPES_H
#define DATATYPES_H
#include <string>
using namespace std;

#define MAX_COUNT 1000

extern const string branchesDB;
extern const string departmentsDB;
extern const string employeesDB;
extern const string clientsDB;
extern const string accountsDB;
extern const string paymentsDB;

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

//-----objektu strukturas -----//

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

extern Branch branchArray[MAX_COUNT];
extern int branchCount;

extern Department departmentArray[MAX_COUNT];
extern int departmentCount;

extern Employee employeeArray[MAX_COUNT];
extern int employeeCount;

extern Client clientArray[MAX_COUNT];
extern int clientCount;

extern Account accountArray[MAX_COUNT];
extern int accountCount;

extern int searchResultIndexes[MAX_COUNT];
extern int searchResultCount;

//menu stavoklu enumeracija
enum MenuState {
	STATE_MAIN_MENU,
	STATE_BRANCH_MGMT,
	STATE_BRANCH_SEARCH,
	STATE_BRANCH_DELETE,
	STATE_DEPT_MGMT,
	STATE_EMPLOYEE_MGMT,
	STATE_CLIENT_MGMT,
	STATE_ACCOUNT_MGMT,
	STATE_PAYMENT_MGMT,
	STATE_EXIT
};

#endif