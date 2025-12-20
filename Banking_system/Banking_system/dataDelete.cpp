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

    int totalEmployees = 0;
    for (int i = 0; i < searchResultCount; i++) {
        int targetBranchId = branchArray[searchResultIndexes[i]].id;

        for (int j = 0; j < departmentCount; j++) {
            if (departmentArray[j].branch_id == targetBranchId) {
                for (int k = 0; k < employeeCount; k++) {
                    if (employeeArray[k].department_id == departmentArray[j].id) {
                        totalEmployees++;
                    }
                }
            }
        }
    }

    if (totalEmployees > 0) {
        cout << "\n--- ERROR: CANNOT DELETE BRANCH(ES) ---\n";
        cout << "There are " << totalEmployees << " employees still assigned to departments in these branches.\n";
        cout << "You must move these employees to other departments or delete them first!\n";
        searchResultCount = 0;
        return;
    }

    int clientsToMove = 0;
    for (int i = 0; i < searchResultCount; i++) {
        int targetBranchId = branchArray[searchResultIndexes[i]].id;
        for (int j = 0; j < clientCount; j++) {
            if (clientArray[j].branch_id == targetBranchId) {
                clientsToMove++;
            }
        }
    }

    int newBranchId = -1;
    if (clientsToMove > 0) {
        cout << "\n--- CLIENT MIGRATION REQUIRED ---\n";
        cout << "There are " << clientsToMove << " clients in these branches.\n";
        displayBranches(false);

        int choice;
        bool valid = false;
        while (!valid) {
            cout << "Enter the corresponding number (1-" << branchCount << ") of the Branch to move these clients to: ";
            cin >> choice;
            if (choice >= 1 && choice <= branchCount) {
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

    int branchesDeleted = 0, deptartmentsDeleted = 0;

    for (int i = branchCount - 1; i >= 0; --i) {
        bool shouldDelete = false;
        for (int j = 0; j < searchResultCount; j++) {
            if (searchResultIndexes[j] == i) shouldDelete = true;
        }

        if (shouldDelete) {
            int targetBranchId = branchArray[i].id;

            for (int i = 0; i < clientCount; i++) {
                if (clientArray[i].branch_id == targetBranchId) {
                    clientArray[i].branch_id = newBranchId;
                }
            }

            for (int i = departmentCount - 1; i >= 0; --i) {
                if (departmentArray[i].branch_id == targetBranchId) {
                    for (int j = i; j < departmentCount - 1; j++) { 
                        departmentArray[j] = departmentArray[j + 1]; 
                    }
                    departmentCount--;
                    deptartmentsDeleted++;
                }
            }

            cout << "Deleted Branch: " << branchArray[i].name << endl;
            for (int k = i; k < branchCount - 1; k++) { 
                branchArray[k] = branchArray[k + 1]; 
            }
            branchCount--;
            branchesDeleted++;
        }
    }

    ofstream branchFile(branchesDB, ios::trunc);
    if (!branchFile) {
        cout << "Error opening file for writing!" << endl;
        return;
    }

    for (int i = 0; i < branchCount; i++) {
        branchFile << branchArray[i].id << "|" << branchArray[i].name << "|" << branchArray[i].address << endl;
    }
    branchFile.close();

    ofstream departmentFile(departmentsDB, ios::trunc);
    if (departmentFile) {
        for (int i = 0; i < departmentCount; i++) {
            departmentFile << departmentArray[i].id << "|" << departmentArray[i].name << "|" << departmentArray[i].branch_id << endl;
        }
        departmentFile.close();
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
    }

    searchResultCount = 0;
    cout << "\nDeletion complete. " << branchesDeleted << " branches and " << deptartmentsDeleted << " departments removed.\n";
}

void deleteDepartments() {
    if (searchResultCount == 0) return;

    loadEmployees();

    int employeesToBeDeletedCount = 0;
    for (int i = 0; i < searchResultCount; i++) {
        int targetDepartmentId = departmentArray[searchResultIndexes[i]].id;
        for (int j = 0; j < employeeCount; j++) {
            if (employeeArray[j].department_id == targetDepartmentId) {
                employeesToBeDeletedCount++;
            }
        }
    }

    cout << "\n--- WARNING: BATCH DELETION ---\n";
    cout << "This action will delete " << searchResultCount << " department(s).\n";
    cout << "CAUTION: " << employeesToBeDeletedCount << " employee(s) associated with these departments will also be PERMANENTLY deleted.\n";
    cout << "Do you want to proceed? (Y/N): ";

    char confirm;
    cin >> confirm;
    cin.ignore();

    if (confirm != 'y' && confirm != 'Y') {
        cout << "Deletion aborted by user.\n";
        searchResultCount = 0;
        return;
    }

    int successfulDepartmentsDeleted = 0;
    int actualEmployeesDeleted = 0;

    for (int i = departmentCount - 1; i >= 0; --i) {
        bool shouldDeleteDepartment = false;
        for (int j = 0; j < searchResultCount; ++j) {
            if (searchResultIndexes[j] == i) {
                shouldDeleteDepartment = true;
                break;
            }
        }

        if (shouldDeleteDepartment) {
            int targetDepartmentId = departmentArray[i].id;

            for (int i = employeeCount - 1; i >= 0; --i) {
                if (employeeArray[i].department_id == targetDepartmentId) {
                    for (int j = i; j < employeeCount - 1; ++j) {
                        employeeArray[j] = employeeArray[j + 1];
                    }
                    employeeCount--;
                    actualEmployeesDeleted++;
                }
            }

            cout << "Deleted Department ID: " << targetDepartmentId << " (" << departmentArray[i].name << ")" << endl;
            for (int j = i; j < departmentCount - 1; ++j) {
                departmentArray[j] = departmentArray[j + 1];
            }
            departmentCount--;
            successfulDepartmentsDeleted++;
        }
    }

    searchResultCount = 0;
    cout << "\nDeletion complete. " << successfulDepartmentsDeleted << "  department(s) and " << actualEmployeesDeleted << "employee(s) removed.\n";

    ofstream departmentFile(departmentsDB, ios::trunc);
    if (departmentFile) {
        for (int i = 0; i < departmentCount; i++) {
            departmentFile << departmentArray[i].id << "|" << departmentArray[i].name << "|" << departmentArray[i].branch_id << endl;
        }
        departmentFile.close();
    }

    ofstream employeeFile(employeesDB, ios::trunc);
    if (employeeFile) {
        for (int i = 0; i < employeeCount; i++) {
            employeeFile << employeeArray[i].id << "|" << employeeArray[i].name << "|" << employeeArray[i].surname << "|"
                << employeeArray[i].department_id << "|" << employeeArray[i].position << "|" << employeeArray[i].access_level << endl;
        }
        employeeFile.close();
    }
}

void deleteEmployees() {
    if (searchResultCount == 0) return;

    cout << "\n--- WARNING: BATCH DELETION ---\n";
    cout << "Do you want to delete ALL " << searchResultCount
        << " employees listed above? (Y/N): ";

    char confirm;
    cin >> confirm;
    cin.ignore();

    if (confirm != 'y' && confirm != 'Y') {
        cout << "Deletion aborted by user.\n";
        searchResultCount = 0;
        return;
    }

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
            cout << "Deleted Employee ID: " << employeeArray[i].id
                << " (" << employeeArray[i].name << " " << employeeArray[i].surname << ")" << endl;

            for (int k = i; k < employeeCount - 1; ++k) {
                employeeArray[k] = employeeArray[k + 1];
            }

            employeeCount--;
            successfulDeletions++;
        }
    }

    searchResultCount = 0;
    cout << "\nDeletion complete. " << successfulDeletions << " employee(s) deleted.\n";

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
}

void deleteClients() {
    if (searchResultCount == 0) return;

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

    int successfulClientsDeleted = 0;
    int successfulAccountsDeleted = 0;

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

            for (int a = accountCount - 1; a >= 0; --a) {
                if (accountArray[a].owner_id == targetClientId) {
                    for (int k = a; k < accountCount - 1; ++k) {
                        accountArray[k] = accountArray[k + 1];
                    }
                    accountCount--;
                    successfulAccountsDeleted++;
                }
            }

            cout << "Deleted Client ID: " << targetClientId
                << " (" << clientArray[i].name << " " << clientArray[i].surname << ")" << endl;

            for (int k = i; k < clientCount - 1; ++k) {
                clientArray[k] = clientArray[k + 1];
            }

            clientCount--;
            successfulClientsDeleted++;
        }
    }

    searchResultCount = 0;
    cout << "\nDeletion complete. " << successfulClientsDeleted << "  client(s) and " << successfulAccountsDeleted << "account(s) removed.\n";

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
    }

    ofstream accountFile(accountsDB, ios::trunc);
    if (accountFile) {
        for (int i = 0; i < accountCount; i++) {
            accountFile << accountArray[i].account_number << "|"
                << accountArray[i].owner_id << "|"
                << accountArray[i].balance << endl;
        }
        accountFile.close();
    }
}

void deleteAccounts() {
    if (searchResultCount == 0) return;

    cout << "\n--- WARNING: BATCH DELETION ---\n";
    cout << "Do you want to delete ALL " << searchResultCount
        << " accounts listed above? (Y/N): ";

    char confirm;
    cin >> confirm;
    cin.ignore();

    if (confirm != 'y' && confirm != 'Y') {
        cout << "Deletion aborted by user.\n";
        searchResultCount = 0;
        return;
    }

    int successfulDeletions = 0;

    for (int i = accountCount - 1; i >= 0; --i) {
        bool shouldDelete = false;
        for (int j = 0; j < searchResultCount; ++j) {
            if (searchResultIndexes[j] == i) {
                shouldDelete = true;
                break;
            }
        }

        if (shouldDelete) {
            cout << "Deleted Account Number: " << accountArray[i].account_number << endl;

            for (int k = i; k < accountCount - 1; ++k) {
                accountArray[k] = accountArray[k + 1];
            }

            accountCount--;
            successfulDeletions++;
        }
    }

    searchResultCount = 0; 
    cout << "\nBatch deletion complete. " << successfulDeletions << " account(s) deleted.\n";

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
}