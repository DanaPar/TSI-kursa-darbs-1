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
void displayBranches(bool useSearchResults);
void displayDepartments(bool useSearchResults);
void displayEmployees(bool useSearchResults);
void displayClients(bool useSearchResults);
void displayAccounts(bool useSearchResults);
void displayPayments(bool useSearchResults); //ToDo

//datu k?rtošana
void sortBranchesById(bool ascending);
void sortBranchesByName(bool ascending);

//datu labosanas funckijas
void editBranch();
void editDepartment();
void editEmployee();
void editClient();
void editAccount(); //ToDo
void editPayment(); //ToDo

//meklesanas funkcijas
void searchBranchesById();
void searchBranchesByName();
void searchBranchesByAddress();
void searchDepartmentsById();
void searchDepartmentsByName();
void searchDepartmentsByBranch();
void searchEmployeesById();
void searchEmployeesByPosition();
void searchEmployeesByAccessLevel();

//datu dzesanas funkcijas
void deleteBranches();
void deleteDepartments();
void deleteEmployees();
void deleteClients();
void deleteAccounts();
void deletePayments();

//skaitlu utt generesanas funckijas
int generateBranchId();
int generateDepartmentId();
int generateEmployeeId();
int generateClientId();
string generateAccountNumber();
bool isAccountNumberUnique(const string& accountNumber);
string toLower(const string& str);


#endif

