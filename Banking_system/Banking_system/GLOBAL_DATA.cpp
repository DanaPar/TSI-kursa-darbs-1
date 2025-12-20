#include "dataTypes.h"
#include <string>

const string branchesDB = "DataBase/branchesDB.txt";
const string departmentsDB = "DataBase/departmentsDB.txt";
const string employeesDB = "DataBase/employeesDB.txt";
const string clientsDB = "DataBase/clientsDB.txt";
const string accountsDB = "DataBase/accountsDB.txt";

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

int searchResultIndexes[MAX_COUNT];
int searchResultCount = 0;