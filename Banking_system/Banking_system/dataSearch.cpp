#include "dataTypes.h"
#include "functions.h"
#include <iostream>
#include <string>
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

void searchClientsByName() {
    loadClients(); // Refresh client data from storage
    string searchInput;
    searchResultCount = 0; // Reset global search result counter

    cout << "Enter Client Name or prefix to search: ";
    getline(cin, searchInput);

    if (searchInput.empty()) {
        cout << "Search name cannot be empty!\n";
        return;
    }

    string lowerSearch = toLower(searchInput);
    size_t searchLength = lowerSearch.length();

    for (int i = 0; i < clientCount; ++i) {
        // Build full name: "Name Surname"
        string firstName = clientArray[i].name;
        string lastName = clientArray[i].surname;
        string fullName = firstName + " " + lastName;

        // Convert to lower case for case-insensitive matching
        string lowerFullName = toLower(fullName);

        // Check if the full name starts with the search string
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
        cout << "--- Search Complete: " << searchResultCount << " Client(s) Found ---\n";
        displayClients(true); // Assuming you have a display function for clients
    }
    else {
        cout << "--- Search Complete: No Clients found matching \"" << searchInput << "\" ---\n";
    }
}

void searchClientsByBranch() {
    loadClients();
    loadBranches(); // Assuming you have a function to load branch data
    string searchBranchName;

    searchResultCount = 0;
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

        // Find the branch details for this client
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
        cout << "--- Search Complete: " << clientsFound << " Client(s) Found ---\n";
        displayClients(true);
    }
    else {
        cout << "--- Search Complete: No Clients Found in Branches starting with " << searchBranchName << " ---\n";
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

void searchEmployeesByBranch() {
    loadEmployees();
    loadDepartments();
    loadBranches();

    string searchBranchName;
    searchResultCount = 0;
    int employeesFound = 0;

    cout << "Enter Branch Name or prefix to search for employees: ";
    getline(cin, searchBranchName);

    if (searchBranchName.empty()) {
        cout << "Search branch name cannot be empty!\n";
        return;
    }

    string lowerSearchName = toLower(searchBranchName);
    size_t searchLength = lowerSearchName.length();

    for (int i = 0; i < employeeCount; ++i) {
        int empDeptId = employeeArray[i].department_id; // Step 1: Get Dept ID
        bool branchMatchFound = false;

        // Step 2: Find the Department to get its branch_id
        for (int j = 0; j < departmentCount; ++j) {
            if (departmentArray[j].id == empDeptId) {
                int deptBranchId = departmentArray[j].branch_id; // Found Branch ID

                // Step 3: Find the Branch to get its name
                for (int k = 0; k < branchCount; ++k) {
                    if (branchArray[k].id == deptBranchId) {
                        string branchName = branchArray[k].name;

                        // Step 4: Compare prefix
                        if (branchName.length() >= searchLength) {
                            string branchPrefix = branchName.substr(0, searchLength);
                            if (toLower(branchPrefix) == lowerSearchName) {
                                branchMatchFound = true;
                            }
                        }
                        break; // Exit branch loop
                    }
                }
                break; // Exit department loop
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
        cout << "--- Search Complete: " << employeesFound << " Employee(s) Found ---\n";
        displayEmployees(true);
    }
    else {
        cout << "--- Search Complete: No Employees Found in Branches starting with " << searchBranchName << " ---\n";
    }
}

void searchEmployeesByName() {
    loadEmployees(); // Refresh data from file
    string searchInput;
    searchResultCount = 0; // Reset global result counter

    cout << "Enter Employee Name (or prefix) to search: ";
    getline(cin, searchInput);

    if (searchInput.empty()) {
        cout << "Search name cannot be empty!\n";
        return;
    }

    string lowerSearch = toLower(searchInput);
    size_t searchLength = lowerSearch.length();

    for (int i = 0; i < employeeCount; ++i) {
        // Construct the full name for a comprehensive search
        string firstName = employeeArray[i].name;
        string lastName = employeeArray[i].surname;
        string fullName = firstName + " " + lastName;

        // Convert full name to lower case for comparison
        string lowerFullName = toLower(fullName);

        // Check if the search string matches the start of the full name
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
        cout << "--- Search Complete: " << searchResultCount << " Employee(s) Found ---\n";
        displayEmployees(true); // Display using the filtered index list
    }
    else {
        cout << "--- Search Complete: No Employees found matching \"" << searchInput << "\" ---\n";
    }
}

void searchEmployeesByDepartment() {
    loadEmployees();
    loadDepartments();
    string searchDeptName;

    searchResultCount = 0; // Reset global search counter
    int employeesFound = 0;

    cout << "Enter Department Name or prefix to search for employees: ";
    getline(cin, searchDeptName);

    if (searchDeptName.empty()) {
        cout << "Search department name cannot be empty!\n";
        return;
    }

    string lowerSearchName = toLower(searchDeptName);
    size_t searchLength = lowerSearchName.length();

    // Iterate through all employees
    for (int i = 0; i < employeeCount; ++i) {
        int empDeptId = employeeArray[i].department_id;
        bool deptMatchFound = false;

        // Find the department details for this specific employee
        for (int j = 0; j < departmentCount; ++j) {
            if (departmentArray[j].id == empDeptId) {
                string deptName = departmentArray[j].name;

                // Check if the department name matches the search prefix
                if (deptName.length() >= searchLength) {
                    string deptPrefix = deptName.substr(0, searchLength);
                    if (toLower(deptPrefix) == lowerSearchName) {
                        deptMatchFound = true;
                    }
                }
                break; // Exit inner loop once the matching department ID is found
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
        cout << "--- Search Complete: " << employeesFound << " Employee(s) Found ---\n";
        displayEmployees(true); // Assuming you have a display function for employees
    }
    else {
        cout << "--- Search Complete: No Employees Found in Departments starting with " << searchDeptName << " ---\n";
    }
}

void searchAccountByOwner() {
    loadAccounts();
    loadClients();
    string searchClientName;

    searchResultCount = 0;
    int clientsFound = 0;

    cout << "Enter Clients Name or prefix to search for accounts: ";
    getline(cin, searchClientName);

    if (searchClientName.empty()) {
        cout << "Search client name cannot be empty!\n";
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
        cout << "--- Search Complete: " << clientsFound << " Account(s) Found ---\n";
        displayAccounts(true);
    }
    else {
        cout << "--- Search Complete: No Accounts Found in Clients starting with " << searchClientName << " ---\n";
    }
}

void searchAccountByNumber() {
    loadAccounts(); // Ensure data is up to date
    string searchNumber;
    searchResultCount = 0; // Reset global result counter

    cout << "Enter Account Number or prefix to search: ";
    getline(cin, searchNumber);

    if (searchNumber.empty()) {
        cout << "Search input cannot be empty!\n";
        return;
    }

    // Convert search input to lower case in case account numbers contain letters
    string lowerSearchNumber = toLower(searchNumber);
    size_t searchLength = lowerSearchNumber.length();

    for (int i = 0; i < accountCount; ++i) {
        // Assuming your account struct has a field named 'account_number'
        string currentAccNum = accountArray[i].account_number;

        // Ensure the account number is long enough to match the search prefix
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
        cout << "--- Search Complete: " << searchResultCount << " Account(s) Found ---\n";
        displayAccounts(true); // Displays the accounts stored in searchResultIndexes
    }
    else {
        cout << "--- Search Complete: No Accounts Found with number starting with " << searchNumber << " ---\n";
    }
}

//void searchAccountByRange();