#include "dataTypes.h"
#include "functions.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void deleteBranches() {
    if (searchResultCount == 0) return;

    loadDepartments();
    loadEmployees();
    loadClients();

    // 1. Check if any Department in the selected Branches has Employees
    int totalEmployeesAffected = 0;
    for (int i = 0; i < searchResultCount; i++) {
        int targetBranchId = branchArray[searchResultIndexes[i]].id;

        for (int d = 0; d < departmentCount; d++) {
            if (departmentArray[d].branch_id == targetBranchId) {
                for (int e = 0; e < employeeCount; e++) {
                    if (employeeArray[e].department_id == departmentArray[d].id) {
                        totalEmployeesAffected++;
                    }
                }
            }
        }
    }

    // 2. If employees exist, block deletion
    if (totalEmployeesAffected > 0) {
        cout << "\n--- ERROR: CANNOT DELETE BRANCH(ES) ---\n";
        cout << "There are " << totalEmployeesAffected << " employees still assigned to departments in these branches.\n";
        cout << "You must move these employees to other departments or delete them first!\n";
        searchResultCount = 0;
        return;
    }

    // 3. Check for Clients and handle migration
    int clientsToMove = 0;
    for (int i = 0; i < searchResultCount; i++) {
        int targetBranchId = branchArray[searchResultIndexes[i]].id;
        for (int c = 0; c < clientCount; c++) {
            if (clientArray[c].branch_id == targetBranchId) {
                clientsToMove++;
            }
        }
    }

    int newBranchId = -1;
    if (clientsToMove > 0) {
        cout << "\n--- CLIENT MIGRATION REQUIRED ---\n";
        cout << "There are " << clientsToMove << " clients in these branches.\n";
        displayBranches(false); // Show all branches for selection

        int choice;
        bool valid = false;
        while (!valid) {
            cout << "Enter the corresponding number (1-" << branchCount << ") of the Branch to move these clients to: ";
            cin >> choice;
            if (choice >= 1 && choice <= branchCount) {
                // Ensure they don't pick a branch that is currently being deleted
                bool beingDeleted = false;
                for (int k = 0; k < searchResultCount; k++) {
                    if (searchResultIndexes[k] == choice - 1) beingDeleted = true;
                }

                if (beingDeleted) {
                    cout << "You cannot move clients to a branch that is also being deleted!\n";
                }
                else {
                    newBranchId = branchArray[choice - 1].id;
                    valid = true;
                }
            }
        }
        cin.ignore();
    }

    // 4. Final Confirmation
    cout << "\n--- WARNING: BRANCH DELETION ---\n";
    cout << "This will delete " << searchResultCount << " branch(es) and all associated departments.\n";
    if (clientsToMove > 0) cout << clientsToMove << " clients will be moved to Branch ID: " << newBranchId << endl;
    cout << "Do you want to proceed? (Y/N): ";

    char confirm;
    cin >> confirm;
    cin.ignore();
    if (confirm != 'y' && confirm != 'Y') {
        cout << "Deletion aborted.\n";
        searchResultCount = 0;
        return;
    }

    // 5. Execution
    int branchesDeleted = 0, deptsDeleted = 0;

    for (int i = branchCount - 1; i >= 0; --i) {
        bool shouldDelete = false;
        for (int j = 0; j < searchResultCount; j++) {
            if (searchResultIndexes[j] == i) shouldDelete = true;
        }

        if (shouldDelete) {
            int targetBranchId = branchArray[i].id;

            // Move Clients
            for (int c = 0; c < clientCount; c++) {
                if (clientArray[c].branch_id == targetBranchId) {
                    clientArray[c].branch_id = newBranchId;
                }
            }

            // Delete Departments
            for (int d = departmentCount - 1; d >= 0; --d) {
                if (departmentArray[d].branch_id == targetBranchId) {
                    for (int k = d; k < departmentCount - 1; k++) departmentArray[k] = departmentArray[k + 1];
                    departmentCount--;
                    deptsDeleted++;
                }
            }

            // Delete Branch
            cout << "Deleted Branch: " << branchArray[i].name << endl;
            for (int k = i; k < branchCount - 1; k++) branchArray[k] = branchArray[k + 1];
            branchCount--;
            branchesDeleted++;
        }
    }

    // 6. Save all updated databases
    ofstream file(branchesDB, ios::trunc);
    if (!file) {
        cout << "Error opening file for writing!" << endl;
        return;
    }

    for (int i = 0; i < branchCount; i++) {
        file << branchArray[i].id << "|" << branchArray[i].name << "|" << branchArray[i].address << endl;
    }
    file.close();

    ofstream deptFile(departmentsDB, ios::trunc);
    if (deptFile) {
        for (int i = 0; i < departmentCount; i++) {
            deptFile << departmentArray[i].id << "|" << departmentArray[i].name << "|" << departmentArray[i].branch_id << endl;
        }
        deptFile.close();
    }

    ofstream clientFile(clientsDB, ios::trunc);
    if (clientFile) {
        for (int i = 0; i < clientCount; i++) {
            clientFile << clientArray[i].id << "|"
                << clientArray[i].name << "|"
                << clientArray[i].surname << "|"
                << clientArray[i].branch_id << "|"
                << clientArray[i].type << endl;
        }
        clientFile.close();
        cout << "Client data updated successfully!" << endl;
    }

    searchResultCount = 0;
    cout << "\nDeletion complete. " << branchesDeleted << " branches and " << deptsDeleted << " departments removed.\n";
}

void deleteDepartments() {
    if (searchResultCount == 0) {
        return;
    }

    // 1. Load employees into memory to count and process them
    loadEmployees();

    // 2. Pre-scan: Count how many employees will be affected
    int empsToBeDeletedCount = 0;
    for (int i = 0; i < searchResultCount; i++) {
        int targetDeptId = departmentArray[searchResultIndexes[i]].id;
        for (int e = 0; e < employeeCount; e++) {
            if (employeeArray[e].department_id == targetDeptId) {
                empsToBeDeletedCount++;
            }
        }
    }

    cout << "\n--- WARNING: BATCH DELETION ---\n";
    cout << "This action will delete " << searchResultCount << " department(s).\n";
    cout << "CAUTION: " << empsToBeDeletedCount << " employee(s) associated with these departments will also be PERMANENTLY deleted.\n";
    cout << "Do you want to proceed? (Y/N): ";

    char confirm;
    cin >> confirm;
    cin.ignore();

    if (confirm != 'y' && confirm != 'Y') {
        cout << "Deletion aborted by user.\n";
        searchResultCount = 0;
        return;
    }

    cout << "Deleting departments and employees...\n";
    int successfulDeptsDeleted = 0;
    int actualEmpsDeleted = 0;

    // Process from end to beginning to maintain array integrity
    for (int i = departmentCount - 1; i >= 0; --i) {
        bool shouldDeleteDept = false;
        for (int j = 0; j < searchResultCount; ++j) {
            if (searchResultIndexes[j] == i) {
                shouldDeleteDept = true;
                break;
            }
        }

        if (shouldDeleteDept) {
            int targetDeptId = departmentArray[i].id;

            // Cascade delete employees
            for (int e = employeeCount - 1; e >= 0; --e) {
                if (employeeArray[e].department_id == targetDeptId) {
                    for (int k = e; k < employeeCount - 1; ++k) {
                        employeeArray[k] = employeeArray[k + 1];
                    }
                    employeeCount--;
                    actualEmpsDeleted++;
                }
            }

            // Delete department
            cout << "Deleted Department ID: " << targetDeptId << " (" << departmentArray[i].name << ")" << endl;
            for (int k = i; k < departmentCount - 1; ++k) {
                departmentArray[k] = departmentArray[k + 1];
            }
            departmentCount--;
            successfulDeptsDeleted++;
        }
    }

    searchResultCount = 0;
    cout << "\nBatch deletion complete.\n";
    cout << successfulDeptsDeleted << " department(s) deleted.\n";
    cout << actualEmpsDeleted << " employee(s) deleted.\n";

    // Save changes to Department file
    ofstream deptFile(departmentsDB, ios::trunc);
    if (deptFile) {
        for (int i = 0; i < departmentCount; i++) {
            deptFile << departmentArray[i].id << "|" << departmentArray[i].name << "|" << departmentArray[i].branch_id << endl;
        }
        deptFile.close();
    }

    // Save changes to Employee file
    ofstream empFile(employeesDB, ios::trunc);
    if (empFile) {
        for (int i = 0; i < employeeCount; i++) {
            empFile << employeeArray[i].id << "|" << employeeArray[i].name << "|" << employeeArray[i].surname << "|"
                << employeeArray[i].department_id << "|" << employeeArray[i].position << "|" << employeeArray[i].access_level << endl;
        }
        empFile.close();
    }
    cout << "Database updated successfully!" << endl;
}

void deleteEmployees() {
    if (searchResultCount == 0) {
        return;
    }

    cout << "\n--- WARNING: BATCH DELETION ---\n";
    cout << "Do you want to delete ALL " << searchResultCount
        << " employees listed above? (Y/N): ";

    char confirm;
    cin >> confirm;
    cin.ignore();

    if (confirm != 'y' && confirm != 'Y') {
        cout << "Deletion aborted by user.\n";
        searchResultCount = 0; // Clear results even on abort
        return;
    }

    cout << "Deleting employees...\n";
    int successfulDeletions = 0;
    for (int i = employeeCount - 1; i >= 0; --i) {
        bool shouldDelete = false;
        for (int j = 0; j < searchResultCount; ++j) {
            if (searchResultIndexes[j] == i) {
                shouldDelete = true;
                break;
            }
        }

        if (shouldDelete) {
            // Found an employee to delete at index 'i'
            cout << "Deleted Employee ID: " << employeeArray[i].id
                << " (" << employeeArray[i].name << " " << employeeArray[i].surname << ")" << endl;

            // Shift elements one position to the left
            for (int k = i; k < employeeCount - 1; ++k) {
                employeeArray[k] = employeeArray[k + 1];
            }

            employeeCount--;
            successfulDeletions++;
        }
    }

    searchResultCount = 0;
    cout << "\nBatch deletion complete. " << successfulDeletions << " employee(s) deleted.\n";

    // Update the database file
    ofstream file(employeesDB, ios::trunc);
    if (!file) {
        cout << "Error opening file for writing!" << endl;
        return;
    }

    for (int i = 0; i < employeeCount; i++) {
        file << employeeArray[i].id << "|"
            << employeeArray[i].name << "|"
            << employeeArray[i].surname << "|"
            << employeeArray[i].department_id << "|"
            << employeeArray[i].position << "|"
            << employeeArray[i].access_level << endl;
    }
    file.close();
    cout << "Employee data updated successfully!" << endl;
}

void deleteClients() {
    if (searchResultCount == 0) {
        return;
    }

    // 1. Iel?d?jam kontus atmi??, lai var?tu tos apstr?d?t
    loadAccounts();

    cout << "\n--- WARNING: BATCH DELETION ---\n";
    cout << "Deleting clients will ALSO PERMANENTLY DELETE all their associated bank accounts.\n";
    cout << "Do you want to delete ALL " << searchResultCount
        << " clients and their accounts? (Y/N): ";

    char confirm;
    cin >> confirm;
    cin.ignore();

    if (confirm != 'y' && confirm != 'Y') {
        cout << "Deletion aborted by user.\n";
        searchResultCount = 0;
        return;
    }

    cout << "Deleting clients and accounts...\n";
    int successfulClientsDeleted = 0;
    int successfulAccountsDeleted = 0;

    // Ejam cauri klientu mas?vam no beig?m uz s?kumu
    for (int i = clientCount - 1; i >= 0; --i) {
        bool shouldDeleteClient = false;
        for (int j = 0; j < searchResultCount; ++j) {
            if (searchResultIndexes[j] == i) {
                shouldDeleteClient = true;
                break;
            }
        }

        if (shouldDeleteClient) {
            int targetClientId = clientArray[i].id;

            // --- KASK?DES DZ?�ANA: Kontu t?r?�ana ---
            // Ejam cauri kontu mas?vam un dz?�am tos, kas pieder �im klientam
            for (int a = accountCount - 1; a >= 0; --a) {
                if (accountArray[a].owner_id == targetClientId) {
                    // Nob?d?m kontu mas?vu
                    for (int k = a; k < accountCount - 1; ++k) {
                        accountArray[k] = accountArray[k + 1];
                    }
                    accountCount--;
                    successfulAccountsDeleted++;
                }
            }

            // --- Klienta dz?�ana ---
            cout << "Deleted Client ID: " << targetClientId
                << " (" << clientArray[i].name << " " << clientArray[i].surname << ")" << endl;

            // Nob?d?m klientu mas?vu
            for (int k = i; k < clientCount - 1; ++k) {
                clientArray[k] = clientArray[k + 1];
            }

            clientCount--;
            successfulClientsDeleted++;
        }
    }

    searchResultCount = 0;
    cout << "\nBatch deletion complete.\n";
    cout << successfulClientsDeleted << " client(s) deleted.\n";
    cout << successfulAccountsDeleted << " account(s) deleted.\n";

    // 2. Atjaunojam klientu failu
    ofstream clientFile(clientsDB, ios::trunc);
    if (clientFile) {
        for (int i = 0; i < clientCount; i++) {
            clientFile << clientArray[i].id << "|"
                << clientArray[i].name << "|"
                << clientArray[i].surname << "|"
                << clientArray[i].branch_id << "|"
                << clientArray[i].type << endl;
        }
        clientFile.close();
        cout << "Client data updated successfully!" << endl;
    }

    // 3. Atjaunojam kontu failu
    ofstream accountFile(accountsDB, ios::trunc);
    if (accountFile) {
        for (int i = 0; i < accountCount; i++) {
            accountFile << accountArray[i].account_number << "|"
                << accountArray[i].owner_id << "|"
                << accountArray[i].balance << endl;
        }
        accountFile.close();
        cout << "Account data updated successfully!" << endl;
    }
}

void deleteAccounts() {
    if (searchResultCount == 0) {
        return;
    }

    cout << "\n--- WARNING: BATCH DELETION ---\n";
    cout << "Do you want to delete ALL " << searchResultCount
        << " accounts listed above? (Y/N): ";

    char confirm;
    cin >> confirm;
    cin.ignore();

    if (confirm != 'y' && confirm != 'Y') {
        cout << "Deletion aborted by user.\n";
        searchResultCount = 0; // Clear results even on abort
        return;
    }

    cout << "Deleting accounts...\n";
    int successfulDeletions = 0;

    // Ejam cauri galvenajam mas?vam no beig?m uz s?kumu
    for (int i = accountCount - 1; i >= 0; --i) {
        bool shouldDelete = false;
        for (int j = 0; j < searchResultCount; ++j) {
            if (searchResultIndexes[j] == i) {
                shouldDelete = true;
                break;
            }
        }

        if (shouldDelete) {
            // Found an account to delete at index 'i' in accountArray
            cout << "Deleted Account Number: " << accountArray[i].account_number << endl;

            // Shift elements one position to the left
            for (int k = i; k < accountCount - 1; ++k) {
                accountArray[k] = accountArray[k + 1];
            }

            accountCount--;
            successfulDeletions++;
        }
    }

    searchResultCount = 0; // The result list is now entirely invalid
    cout << "\nBatch deletion complete. " << successfulDeletions << " account(s) deleted.\n";

    // P?rrakst?m failu ar jaunajiem datiem
    ofstream file(accountsDB, ios::trunc);
    if (!file) {
        cout << "Error opening file for writing!" << endl;
        return;
    }

    for (int i = 0; i < accountCount; i++) {
        file << accountArray[i].account_number << "|"
            << accountArray[i].owner_id << "|"
            << accountArray[i].balance << endl;
    }
    file.close();
    cout << "Account data updated successfully!" << endl;
}