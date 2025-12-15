#include "dataTypes.h"
#include "functions.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>

using namespace std;

void searchBranchesById() {
    loadBranches();
    int searchId;
    //notira ieprieksejos rezultatus
    searchResultCount = 0;
    cout << "Enter Branch ID to search: ";

    while (!(cin >> searchId)) {
        cout << "Invalid input. Please enter a valid integer ID: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();

    for (int i = 0; i < branchCount; ++i) {
        if (branchArray[i].id == searchId) {
            if (searchResultCount < MAX_COUNT) {
                searchResultIndexes[searchResultCount] = i;
                searchResultCount++;
                break;
            }
            else {
                cout << "Warning: Maximum search results limit reached.\n";
                break;
            }
        }
    }

    if (searchResultCount > 0) {
        cout << "--- Search Complete: " << searchResultCount << " Branch(es) Found ---\n";
        displayBranches(true);
    }
    else {
        cout << "--- Search Complete: No Branches Found with ID " << searchId << " ---\n";
    }
}

void searchBranchesByName() {
    loadBranches();
    string searchName;
    //notira ieprieksejos rezultatus
    searchResultCount = 0;

    cout << "Enter Branch Name or prefix to search: ";

    getline(cin, searchName);

    if (searchName.empty()) {
        cout << "Search name cannot be empty!\n";
        return;
    }

    string lowerName = toLower(searchName);
    size_t searchLength = lowerName.length();

    for (int i = 0; i < branchCount; ++i) {
        // Get the current branch name
        string branchName = branchArray[i].name;

        // Check if the branch name is long enough for the comparison
        if (branchName.length() >= searchLength) {

            // 1. Extract the prefix of the branch name matching the search length
            string branchPrefix = branchName.substr(0, searchLength);

            // 2. Convert the branch prefix to lowercase
            string lowerBranchPrefix = toLower(branchPrefix);

            // 3. Compare the two lowercase prefixes
            if (lowerBranchPrefix == lowerName) {
                // Match found (case-insensitive prefix match)

                if (searchResultCount < MAX_COUNT) {
                    searchResultIndexes[searchResultCount] = i;
                    searchResultCount++;
                    // Note: Unlike ID, we don't break here, as multiple branches can start with the same prefix.
                }
                else {
                    cout << "Warning: Maximum search results limit reached.\n";
                    break;
                }
            }
        }
    }

    if (searchResultCount > 0) {
        cout << "--- Search Complete: " << searchResultCount << " Branch(es) Found ---\n";
        displayBranches(true);
    }
    else {
        cout << "--- Search Complete: No Branches Found with Name starting with " << searchName << " ---\n";
    }
}

void searchBranchesByAddress() {
    loadBranches();
    string searchAddress;
    //notira ieprieksejos rezultatus
    searchResultCount = 0;

    cout << "Enter Branch address or prefix to search: ";

    getline(cin, searchAddress);

    if (searchAddress.empty()) {
        cout << "Search address cannot be empty!\n";
        return;
    }

    string lowerAddress = toLower(searchAddress);
    size_t searchLength = lowerAddress.length();

    for (int i = 0; i < branchCount; ++i) {
        // Get the current branch name
        string branchAddress = branchArray[i].address;

        // Check if the branch name is long enough for the comparison
        if (branchAddress.length() >= searchLength) {

            // 1. Extract the prefix of the branch name matching the search length
            string addressPrefix = branchAddress.substr(0, searchLength);

            // 2. Convert the branch prefix to lowercase
            string lowerAddressPrefix = toLower(addressPrefix);

            // 3. Compare the two lowercase prefixes
            if (lowerAddressPrefix == lowerAddress) {
                // Match found (case-insensitive prefix match)

                if (searchResultCount < MAX_COUNT) {
                    searchResultIndexes[searchResultCount] = i;
                    searchResultCount++;
                    // Note: Unlike ID, we don't break here, as multiple branches can start with the same prefix.
                }
                else {
                    cout << "Warning: Maximum search results limit reached.\n";
                    break;
                }
            }
        }
    }

    if (searchResultCount > 0) {
        cout << "--- Search Complete: " << searchResultCount << " Branch(es) Found ---\n";
        displayBranches(true);
    }
    else {
        cout << "--- Search Complete: No Branches Found with address starting with " << searchAddress << " ---\n";
    }
}

void searchDepartmentsById() {
    loadDepartments();
    int searchId;
    //notira ieprieksejos rezultatus
    searchResultCount = 0;
    cout << "Enter Department ID to search: ";

    while (!(cin >> searchId)) {
        cout << "Invalid input. Please enter a valid integer ID: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();

    for (int i = 0; i < departmentCount; ++i) {
        if (departmentArray[i].id == searchId) {
            if (searchResultCount < MAX_COUNT) {
                searchResultIndexes[searchResultCount] = i;
                searchResultCount++;
                break;
            }
            else {
                cout << "Warning: Maximum search results limit reached.\n";
                break;
            }
        }
    }

    if (searchResultCount > 0) {
        cout << "--- Search Complete: " << searchResultCount << " Department(s) Found ---\n";
        displayDepartments(true);
    }
    else {
        cout << "--- Search Complete: No Departments Found with ID " << searchId << " ---\n";
    }
}

void searchDepartmentsByName() {
    loadDepartments();
    string searchName;
  
    searchResultCount = 0;
    cout << "Enter Department Name or prefix to search: ";
    getline(cin, searchName);

    if (searchName.empty()) {
        cout << "Search name cannot be empty!\n";
        return;
    }

    string lowerName = toLower(searchName);
    size_t searchLength = lowerName.length();

    for (int i = 0; i < departmentCount; ++i) {
        // Get the current branch name
        string departmentName = departmentArray[i].name;

        // Check if the branch name is long enough for the comparison
        if (departmentName.length() >= searchLength) {

            // 1. Extract the prefix of the branch name matching the search length
            string departmentPrefix = departmentName.substr(0, searchLength);

            // 2. Convert the branch prefix to lowercase
            string lowerDepartmentPrefix = toLower(departmentPrefix);

            // 3. Compare the two lowercase prefixes
            if (lowerDepartmentPrefix == lowerName) {
                // Match found (case-insensitive prefix match)

                if (searchResultCount < MAX_COUNT) {
                    searchResultIndexes[searchResultCount] = i;
                    searchResultCount++;
                    // Note: Unlike ID, we don't break here, as multiple branches can start with the same prefix.
                }
                else {
                    cout << "Warning: Maximum search results limit reached.\n";
                    break;
                }
            }
        }
    }

    if (searchResultCount > 0) {
        cout << "--- Search Complete: " << searchResultCount << " Department(s) Found ---\n";
        displayDepartments(true);
    }
    else {
        cout << "--- Search Complete: No Departments Found with Name starting with " << searchName << " ---\n";
    }
}

void searchDepartmentsByBranch() {
    loadDepartments(); // Load departments data
    loadBranches();    // Load branches data
    string searchBranchName;

    // Reset previous search results
    searchResultCount = 0;
    int departmentsFound = 0; // Counter for departments found

    cout << "Enter Branch Name or prefix to search for departments in: ";

    // Use getline to capture the full search string (including spaces)
    getline(cin, searchBranchName);

    if (searchBranchName.empty()) {
        cout << "Search branch name cannot be empty!\n";
        return;
    }

    // Convert search term to lowercase for case-insensitive comparison
    string lowerSearchName = toLower(searchBranchName);
    size_t searchLength = lowerSearchName.length();

    // 1. Loop through all departments
    for (int i = 0; i < departmentCount; ++i) {
        int departmentBranchId = departmentArray[i].branch_id; // Get the Branch ID associated with the current department

        // 2. Find the corresponding Branch object using the departmentBranchId
        // This is the key change: we search for the Branch name/prefix inside the department loop.

        bool branchMatchFound = false;

        // Loop through all branches to find the one matching the department's ID
        for (int j = 0; j < branchCount; ++j) {
            if (branchArray[j].id == departmentBranchId) {
                // Found the corresponding branch for this department

                string branchName = branchArray[j].name;

                if (branchName.length() >= searchLength) {
                    string branchPrefix = branchName.substr(0, searchLength);
                    string lowerBranchPrefix = toLower(branchPrefix);

                    // 3. Check for case-insensitive prefix match against the user's search term
                    if (lowerBranchPrefix == lowerSearchName) {
                        branchMatchFound = true;
                        break; // Match found, break out of the inner loop (no need to check other branches)
                    }
                }

                // If the ID matched but the name didn't, or the name was too short, we stop checking other branches
                // since this is the only branch with this ID.
                break;
            }
        }

        // 4. If the corresponding branch's name matched the search criteria, store the department index
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


    // 5. Display results
    if (departmentsFound > 0) {
        cout << "--- Search Complete: " << departmentsFound << " Department(s) Found ---\n";
        displayDepartments(true);
    }
    else {
        cout << "--- Search Complete: No Departments Found in Branch(es) starting with " << searchBranchName << " ---\n";
    }
}

void searchEmployeesById() {
    loadEmployees();
    int searchId;
    //notira ieprieksejos rezultatus
    searchResultCount = 0;
    cout << "Enter Employee ID to search: ";

    while (!(cin >> searchId)) {
        cout << "Invalid input. Please enter a valid integer ID: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();

    for (int i = 0; i < employeeCount; ++i) {
        if (employeeArray[i].id == searchId) {
            if (searchResultCount < MAX_COUNT) {
                searchResultIndexes[searchResultCount] = i;
                searchResultCount++;
                break;
            }
            else {
                cout << "Warning: Maximum search results limit reached.\n";
                break;
            }
        }
    }

    if (searchResultCount > 0) {
        cout << "--- Search Complete: " << searchResultCount << " Employee(s) Found ---\n";
        displayEmployees(true);
    }
    else {
        cout << "--- Search Complete: No Employees Found with ID " << searchId << " ---\n";
    }
}
//void searchEmployeesByPosition();
//void searchEmployeesByAccessLevel();