#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "dataTypes.h"

//Pievienosanas funckijas
void addBranch();
void addDepartment();
void addEmployee();
void addClient();
void addAccount();

//datu ielades masivos funkcijas
void loadBranches();
void loadDepartments();
void loadEmployees();
void loadClients();
void loadAccounts();

//datu attelosanas funkcijas
void displayBranches(bool useSearchResults);
void displayDepartments(bool useSearchResults);
void displayEmployees(bool useSearchResults);
void displayClients(bool useSearchResults);
void displayAccounts(bool useSearchResults);

//datu kartosana
void sortBranchesById(bool ascending);
void sortBranchesByName(bool ascending);
void sortDepartmentsByName(bool ascending);
void sortEmployeesByName(bool ascending);
// void sortEmployeesByPosition(bool ascending);
// void sortClientsByName(bool ascending);
// void sortClientsByType(bool ascendig);
// void sortAccountsByBalance(bool ascending);
// void sortAccountsByOwner(bool ascending);

//datu labosanas funckijas
void editBranch();
void editDepartment();
void editEmployee();
void editClient();
void editAccount();

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
void searchAccountByOwner();
void searchAccountByRange();

//datu dzesanas funkcijas
void deleteBranches();
void deleteDepartments();
void deleteEmployees();
void deleteClients();
void deleteAccounts();

//skaitlu utt generesanas funckijas
int generateBranchId();
int generateDepartmentId();
int generateEmployeeId();
int generateClientId();
string generateAccountNumber();
bool isAccountNumberUnique(const string& accountNumber);
string toLower(const string& str);


#endif

