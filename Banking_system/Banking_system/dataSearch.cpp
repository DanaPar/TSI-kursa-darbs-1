#include "dataTypes.h"
#include "functions.h"
#include <iostream>
#include <string>
#include <limits>

using namespace std;

void searchBranchesById() {
    loadBranches();
    searchResultCount = 0; 
    int searchId;
    cout << "Enter Branch ID to search: ";

    while (!(cin >> searchId)) {
        cout << "Invalid input. Please enter a valid integer ID: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();

    for (int i = 0; i < branchCount; ++i) {
        if (branchArray[i].id == searchId) {
            searchResultIndexes[searchResultCount] = i;
            searchResultCount++;
        }
    }

    if (searchResultCount > 0) {
        displayBranches(true);
    }
    else {
        cout << "--- Search Complete: No Branches Found with ID " << searchId << " ---\n" << endl;
    }
}

void searchBranchesByName() {
    loadBranches();
    searchResultCount = 0;
    string searchName;
    cout << "Enter Branch Name or prefix to search: ";
    getline(cin, searchName);

    if (searchName.empty()) {
        cout << "Search name cannot be empty!\n" << endl;
        return;
    }

    string lowerName = toLower(searchName);
    size_t searchLength = lowerName.length();

    for (int i = 0; i < branchCount; ++i) {
        string branchName = branchArray[i].name;

        if (branchName.length() >= searchLength) {
            string branchPrefix = branchName.substr(0, searchLength);
            string lowerBranchPrefix = toLower(branchPrefix);
            if (lowerBranchPrefix == lowerName) {
                if (searchResultCount < MAX_COUNT) {
                    searchResultIndexes[searchResultCount] = i;
                    searchResultCount++;
                }
                else {
                    cout << "Warning: Maximum search results limit reached.\n";
                    break;
                }
            }
        }
    }

    if (searchResultCount > 0) {
        displayBranches(true);
    }
    else {
        cout << "--- Search Complete: No Branches Found with Name starting with " << searchName << " ---\n" << endl;
    }
}

void searchBranchesByAddress() {
    loadBranches();
    searchResultCount = 0;
    string searchAddress;
    cout << "Enter Branch address or prefix to search: ";
    getline(cin, searchAddress);

    if (searchAddress.empty()) {
        cout << "Search address cannot be empty!\n" << endl;
        return;
    }

    string lowerAddress = toLower(searchAddress);
    size_t searchLength = lowerAddress.length();

    for (int i = 0; i < branchCount; ++i) {
        string branchAddress = branchArray[i].address;

        if (branchAddress.length() >= searchLength) {
            string addressPrefix = branchAddress.substr(0, searchLength);
            string lowerAddressPrefix = toLower(addressPrefix);

            if (lowerAddressPrefix == lowerAddress) {
                if (searchResultCount < MAX_COUNT) {
                    searchResultIndexes[searchResultCount] = i;
                    searchResultCount++;
                }
                else {
                    cout << "Warning: Maximum search results limit reached.\n";
                    break;
                }
            }
        }
    }

    if (searchResultCount > 0) {
        displayBranches(true);
    }
    else {
        cout << "--- Search Complete: No Branches Found with address starting with " << searchAddress << " ---\n" << endl;
    }
}

void searchDepartmentsById() {
    loadDepartments();
    searchResultCount = 0;
    int searchId;
    cout << "Enter Department ID to search: ";

    while (!(cin >> searchId)) {
        cout << "Invalid input. Please enter a valid integer ID: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();

    for (int i = 0; i < departmentCount; ++i) {
        if (departmentArray[i].id == searchId) {
            searchResultIndexes[searchResultCount] = i;
            searchResultCount++;
        }
    }

    if (searchResultCount > 0) {
        displayDepartments(true);
    }
    else {
        cout << "--- Search Complete: No Departments Found with ID " << searchId << " ---\n" << endl;
    }
}

void searchDepartmentsByName() {
    loadDepartments();
    searchResultCount = 0;
    string searchName;
    cout << "Enter Department Name or prefix to search: ";
    getline(cin, searchName);

    if (searchName.empty()) {
        cout << "Search name cannot be empty!\n" << endl;
        return;
    }

    string lowerName = toLower(searchName);
    size_t searchLength = lowerName.length();

    for (int i = 0; i < departmentCount; ++i) {
        string departmentName = departmentArray[i].name;

        if (departmentName.length() >= searchLength) {
            string departmentPrefix = departmentName.substr(0, searchLength);
            string lowerDepartmentPrefix = toLower(departmentPrefix);

            if (lowerDepartmentPrefix == lowerName) {
                if (searchResultCount < MAX_COUNT) {
                    searchResultIndexes[searchResultCount] = i;
                    searchResultCount++;
                }
                else {
                    cout << "Warning: Maximum search results limit reached.\n";
                    break;
                }
            }
        }
    }

    if (searchResultCount > 0) {
        displayDepartments(true);
    }
    else {
        cout << "--- Search Complete: No Departments Found with Name starting with " << searchName << " ---\n" << endl;
    }
}

void searchDepartmentsByBranch() {
    loadDepartments();
    loadBranches();
    searchResultCount = 0;
    string searchBranchName;
    int departmentsFound = 0;
    cout << "Enter Branch Name or prefix to search for departments in: ";
    getline(cin, searchBranchName);

    if (searchBranchName.empty()) {
        cout << "Search branch name cannot be empty!\n" << endl;
        return;
    }

    string lowerSearchName = toLower(searchBranchName);
    size_t searchLength = lowerSearchName.length();

    for (int i = 0; i < departmentCount; ++i) {
        int departmentBranchId = departmentArray[i].branch_id;

        bool branchMatchFound = false;

        for (int j = 0; j < branchCount; ++j) {
            if (branchArray[j].id == departmentBranchId) {
                string branchName = branchArray[j].name;

                if (branchName.length() >= searchLength) {
                    string branchPrefix = branchName.substr(0, searchLength);
                    string lowerBranchPrefix = toLower(branchPrefix);

                    if (lowerBranchPrefix == lowerSearchName) {
                        branchMatchFound = true;
                        break;
                    }
                }
                break;
            }
        }

        if (branchMatchFound) {
            if (searchResultCount < MAX_COUNT) {
                searchResultIndexes[searchResultCount] = i;
                searchResultCount++;
                departmentsFound++;
            }
            else {
                cout << "Warning: Maximum search results limit reached for departments.\n";
                break;
            }
        }
    }

    if (departmentsFound > 0) {
        displayDepartments(true);
    }
    else {
        cout << "--- Search Complete: No Departments Found in Branch(es) starting with " << searchBranchName << " ---\n" << endl;
    }
}

void searchClientsByName() {
    loadClients();
    searchResultCount = 0;
    string searchInput;
    cout << "Enter Client Name or prefix to search: ";
    getline(cin, searchInput);

    if (searchInput.empty()) {
        cout << "Search name cannot be empty!\n";
        return;
    }

    string lowerSearch = toLower(searchInput);
    size_t searchLength = lowerSearch.length();

    for (int i = 0; i < clientCount; ++i) {
        string firstName = clientArray[i].name;
        string lastName = clientArray[i].surname;
        string fullName = firstName + " " + lastName;
        string lowerFullName = toLower(fullName);

        if (lowerFullName.length() >= searchLength) {
            string namePrefix = lowerFullName.substr(0, searchLength);

            if (namePrefix == lowerSearch) {
                if (searchResultCount < MAX_COUNT) {
                    searchResultIndexes[searchResultCount] = i;
                    searchResultCount++;
                }
                else {
                    cout << "Warning: Maximum search results limit reached.\n";
                    break;
                }
            }
        }
    }

    if (searchResultCount > 0) {
        displayClients(true);
    }
    else {
        cout << "--- Search Complete: No Clients found matching \"" << searchInput << "\" ---\n" <<endl;
    }
}

void searchClientsByBranch() {
    loadClients();
    loadBranches();
    searchResultCount = 0;
    string searchBranchName;
    int clientsFound = 0;
    cout << "Enter Branch Name or prefix to search for clients: ";
    getline(cin, searchBranchName);

    if (searchBranchName.empty()) {
        cout << "Search branch name cannot be empty!\n";
        return;
    }

    string lowerSearchName = toLower(searchBranchName);
    size_t searchLength = lowerSearchName.length();

    for (int i = 0; i < clientCount; ++i) {
        int clientBranchId = clientArray[i].branch_id;
        bool branchMatchFound = false;

        for (int j = 0; j < branchCount; ++j) {
            if (branchArray[j].id == clientBranchId) {
                string branchName = branchArray[j].name;

                if (branchName.length() >= searchLength) {
                    string branchPrefix = branchName.substr(0, searchLength);
                    if (toLower(branchPrefix) == lowerSearchName) {
                        branchMatchFound = true;
                    }
                }
                break;
            }
        }

        if (branchMatchFound) {
            if (searchResultCount < MAX_COUNT) {
                searchResultIndexes[searchResultCount] = i;
                searchResultCount++;
                clientsFound++;
            }
            else {
                cout << "Warning: Maximum search results limit reached.\n";
                break;
            }
        }
    }

    if (clientsFound > 0) {
        displayClients(true);
    }
    else {
        cout << "--- Search Complete: No Clients Found in Branches starting with " << searchBranchName << " ---\n" << endl;
    }
}

void searchEmployeesById() {
    loadEmployees();
    searchResultCount = 0;
    int searchId;
    cout << "Enter Employee ID to search: ";

    while (!(cin >> searchId)) {
        cout << "Invalid input. Please enter a valid integer ID: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();

    for (int i = 0; i < employeeCount; ++i) {
        if (employeeArray[i].id == searchId) {
            searchResultIndexes[searchResultCount] = i;
            searchResultCount++;
        }
    }

    if (searchResultCount > 0) {
        displayEmployees(true);
    }
    else {
        cout << "--- Search Complete: No Employees Found with ID " << searchId << " ---\n" << endl;
    }
}

void searchEmployeesByBranch() {
    loadEmployees();
    loadDepartments();
    loadBranches();
    searchResultCount = 0;
    string searchBranchName;
    int employeesFound = 0;
    cout << "Enter Branch Name or prefix to search for employees: ";
    getline(cin, searchBranchName);

    if (searchBranchName.empty()) {
        cout << "Search branch name cannot be empty!\n" << endl;
        return;
    }

    string lowerSearchName = toLower(searchBranchName);
    size_t searchLength = lowerSearchName.length();

    for (int i = 0; i < employeeCount; ++i) {
        int empDeptId = employeeArray[i].department_id;
        bool branchMatchFound = false;

        for (int j = 0; j < departmentCount; ++j) {
            if (departmentArray[j].id == empDeptId) {
                int deptBranchId = departmentArray[j].branch_id;

                for (int k = 0; k < branchCount; ++k) {
                    if (branchArray[k].id == deptBranchId) {
                        string branchName = branchArray[k].name;

                        if (branchName.length() >= searchLength) {
                            string branchPrefix = branchName.substr(0, searchLength);
                            if (toLower(branchPrefix) == lowerSearchName) {
                                branchMatchFound = true;
                            }
                        }
                        break;
                    }
                }
                break;
            }
        }

        if (branchMatchFound) {
            if (searchResultCount < MAX_COUNT) {
                searchResultIndexes[searchResultCount] = i;
                searchResultCount++;
                employeesFound++;
            }
            else {
                cout << "Warning: Maximum search results limit reached.\n";
                break;
            }
        }
    }

    if (employeesFound > 0) {
        displayEmployees(true);
    }
    else {
        cout << "--- Search Complete: No Employees Found in Branches starting with " << searchBranchName << " ---\n" << endl;
    }
}

void searchEmployeesByName() {
    loadEmployees();
    searchResultCount = 0;
    string searchInput;
    cout << "Enter Employee Name (or prefix) to search: ";
    getline(cin, searchInput);

    if (searchInput.empty()) {
        cout << "Search name cannot be empty!\n" << endl;
        return;
    }

    string lowerSearch = toLower(searchInput);
    size_t searchLength = lowerSearch.length();

    for (int i = 0; i < employeeCount; ++i) {
        string firstName = employeeArray[i].name;
        string lastName = employeeArray[i].surname;
        string fullName = firstName + " " + lastName;
        string lowerFullName = toLower(fullName);

        if (lowerFullName.length() >= searchLength) {
            string namePrefix = lowerFullName.substr(0, searchLength);

            if (namePrefix == lowerSearch) {
                if (searchResultCount < MAX_COUNT) {
                    searchResultIndexes[searchResultCount] = i;
                    searchResultCount++;
                }
                else {
                    cout << "Warning: Maximum search results limit reached.\n";
                    break;
                }
            }
        }
    }

    if (searchResultCount > 0) {
        displayEmployees(true);
    }
    else {
        cout << "--- Search Complete: No Employees found matching \"" << searchInput << "\" ---\n" << endl;
    }
}

void searchEmployeesByDepartment() {
    loadEmployees();
    loadDepartments();
    searchResultCount = 0;
    string searchDeptName;
    int employeesFound = 0;
    cout << "Enter Department Name or prefix to search for employees: ";
    getline(cin, searchDeptName);

    if (searchDeptName.empty()) {
        cout << "Search department name cannot be empty!\n" << endl;
        return;
    }

    string lowerSearchName = toLower(searchDeptName);
    size_t searchLength = lowerSearchName.length();

    for (int i = 0; i < employeeCount; ++i) {
        int empDeptId = employeeArray[i].department_id;
        bool deptMatchFound = false;

        for (int j = 0; j < departmentCount; ++j) {
            if (departmentArray[j].id == empDeptId) {
                string deptName = departmentArray[j].name;

                if (deptName.length() >= searchLength) {
                    string deptPrefix = deptName.substr(0, searchLength);
                    if (toLower(deptPrefix) == lowerSearchName) {
                        deptMatchFound = true;
                    }
                }
                break;
            }
        }

        if (deptMatchFound) {
            if (searchResultCount < MAX_COUNT) {
                searchResultIndexes[searchResultCount] = i;
                searchResultCount++;
                employeesFound++;
            }
            else {
                cout << "Warning: Maximum search results limit reached.\n";
                break;
            }
        }
    }

    if (employeesFound > 0) {
        displayEmployees(true);
    }
    else {
        cout << "--- Search Complete: No Employees Found in Departments starting with " << searchDeptName << " ---\n" << endl;
    }
}

void searchAccountByOwner() {
    loadAccounts();
    loadClients();
    searchResultCount = 0;
    string searchClientName;
    int clientsFound = 0;
    cout << "Enter Clients Name or prefix to search for accounts: ";
    getline(cin, searchClientName);

    if (searchClientName.empty()) {
        cout << "Search client name cannot be empty!\n" << endl;
        return;
    }

    string lowerSearchName = toLower(searchClientName);
    size_t searchLength = lowerSearchName.length();

    for (int i = 0; i < accountCount; ++i) {
        int accountOwnerId = accountArray[i].owner_id;

        bool clientMatchFound = false;

        for (int j = 0; j < clientCount; ++j) {
            if (clientArray[j].id == accountOwnerId) {

                string clientName = clientArray[j].name;
                string clientSurname = clientArray[j].surname;
                string fullName = clientName + " " + clientSurname;

                if (fullName.length() >= searchLength) {
                    string clientPrefix = fullName.substr(0, searchLength);
                    string lowerClientPrefix = toLower(clientPrefix);

                    if (lowerClientPrefix == lowerSearchName) {
                        clientMatchFound = true;
                        break;
                    }
                }
                break;
            }
        }

        if (clientMatchFound) {
            if (searchResultCount < MAX_COUNT) {
                searchResultIndexes[searchResultCount] = i;
                searchResultCount++;
                clientsFound++;
            }
            else {
                cout << "Warning: Maximum search results limit reached for departments.\n";
                break;
            }
        }
    }

    if (clientsFound > 0) {
        displayAccounts(true);
    }
    else {
        cout << "--- Search Complete: No Accounts Found in Clients starting with " << searchClientName << " ---\n" << endl;
    }
}

void searchAccountByNumber() {
    loadAccounts(); 
    searchResultCount = 0;
    string searchNumber;
    cout << "Enter Account Number or prefix to search: ";
    getline(cin, searchNumber);

    if (searchNumber.empty()) {
        cout << "Search input cannot be empty!\n" << endl;
        return;
    }

    string lowerSearchNumber = toLower(searchNumber);
    size_t searchLength = lowerSearchNumber.length();

    for (int i = 0; i < accountCount; ++i) {
        string currentAccNum = accountArray[i].account_number;

        if (currentAccNum.length() >= searchLength) {
            string accPrefix = currentAccNum.substr(0, searchLength);

            if (toLower(accPrefix) == lowerSearchNumber) {
                if (searchResultCount < MAX_COUNT) {
                    searchResultIndexes[searchResultCount] = i;
                    searchResultCount++;
                }
                else {
                    cout << "Warning: Maximum search results limit reached.\n";
                    break;
                }
            }
        }
    }

    if (searchResultCount > 0) {
        displayAccounts(true);
    }
    else {
        cout << "--- Search Complete: No Accounts Found with number starting with " << searchNumber << " ---\n"<< endl;
    }
}

//void searchAccountByRange();