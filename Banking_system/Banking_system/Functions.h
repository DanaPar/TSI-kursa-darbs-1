#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "dataTypes.h"

//Pievienosanas funckijas
void addBranch();
void addDepartment();
void addEmployee();
void addClient();
void addAccount();
void addPayment(); //ToDo create function

//datu ielades masivos funkcijas
void loadBranches();
void loadDepartments();
void loadEmployees();
void loadClients();
void loadAccounts();
void loadPayments(); //ToDo create

//datu attelosanas funkcijas
void displayBranches();
void displayDepartments();
void displayEmployees();
void displayClients();
void displayAccounts();
void displayPayments(); //ToDo

//datu labosanas funckijas
void editBranch();
void editDepartment();
void editEmployee();
void editClient();
void editAccount(); //ToDo
void editPayment(); //ToDo

//meklesanas funkcijas
void searchBranches();

//datu dzesanas funkcijas
void deleteBranches();

//skaitlu utt generesanas funckijas
int generateBranchId();
int generateDepartmentId();
int generateEmployeeId();
int generateClientId();
string generateAccountNumber();
bool isAccountNumberUnique(const string& accountNumber);

#endif

