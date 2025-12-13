#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "DataTypes.h"

//Pievienosanas funckijas
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

void searchBranches();

void deleteBranches();

string generateAccountNumber();
bool isAccountNumberUnique(const string& accountNumber);

#endif

