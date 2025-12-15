#include "dataTypes.h"

#include <string>
#include <fstream>

using namespace std;

//visi faili, kas glaba datus
const string branchesDB = "DataBase/branchesDB.txt";
const string departmentsDB = "DataBase/departmentsDB.txt";
const string employeesDB = "DataBase/employeesDB.txt";
const string clientsDB = "DataBase/clientsDB.txt";
const string accountsDB = "DataBase/accountsDB.txt";
const string paymentsDB = "DataBase/paymentsDB.txt";

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

int searchResultIndexes[MAX_COUNT];
int searchResultCount = 0;