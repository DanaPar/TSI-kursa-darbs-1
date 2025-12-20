#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "dataTypes.h"

void addBranch();
void addDepartment();
void addEmployee();
void addClient();
void addAccount();

void loadBranches();
void loadDepartments();
void loadEmployees();
void loadClients();
void loadAccounts();

void displayBranches(bool useSearchResults);
void displayDepartments(bool useSearchResults);
void displayEmployees(bool useSearchResults);
void displayClients(bool useSearchResults);
void displayAccounts(bool useSearchResults);
void displayBranchStatistics();

void editBranch();
void editDepartment();
void editEmployee();
void editClient();
void editAccount();

void sortBranchesById(bool ascending);
void sortBranchesByName(bool ascending);
void sortDepartmentsByName(bool ascending);
void sortEmployeesByName(bool ascending);
void sortEmployeesByAccessLevel(bool ascending);
void sortClientsByName(bool ascending);
void sortClientsByType(bool ascendig);
void sortAccountsByBalance(bool ascending);
void sortAccountsByOwner(bool ascending);
bool isOrderedCorrect(const string& a, const string& b, bool ascending);
bool isOrderedCorrect(int a, int b, bool ascending);
bool isOrderedCorrect(double a, double b, bool ascending);

void searchBranchesById();
void searchBranchesByName();
void searchBranchesByAddress();
void searchDepartmentsById();
void searchDepartmentsByName();
void searchDepartmentsByBranch();
void searchClientsByName();
void searchClientsByBranch();
void searchEmployeesById();
void searchEmployeesByName();
void searchEmployeesByDepartment();
void searchEmployeesByBranch();
void searchAccountByNumber();
void searchAccountByOwner();
void searchAccountByBalance();

void deleteBranches();
void deleteDepartments();
void deleteEmployees();
void deleteClients();
void deleteAccounts();

int generateBranchId();
int generateDepartmentId();
int generateEmployeeId();
int generateClientId();
string generateAccountNumber();
bool isAccountNumberUnique(const string& accountNumber);
string toLower(const string& str);

#endif

