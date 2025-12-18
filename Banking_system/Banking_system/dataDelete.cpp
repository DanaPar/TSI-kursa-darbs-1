#include "dataTypes.h"
#include "functions.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

void deleteBranches() {
	if (searchResultCount == 0) {
		cout << "--- No branches found matching search criteria. Nothing to delete. ---\n";
		return;
	}

	cout << "\n--- WARNING: BATCH DELETION ---\n";
	cout << "Do you want to delete ALL " << searchResultCount
		<< " branches listed above? (Y/N): ";

    char confirm;
	cin >> confirm;
	cin.ignore();

	if (confirm != 'y' && confirm != 'Y') {
		cout << "Deletion aborted by user.\n";
		searchResultCount = 0; // Clear results even on abort
		return;
	}

	cout << "Deleting branches...\n";
	int successfulDeletions = 0;
    for (int i = branchCount - 1; i >= 0; --i) {
        // Check if the current main array index 'i' is in the list of results to be deleted
        bool shouldDelete = false;
        for (int j = 0; j < searchResultCount; ++j) {
            if (searchResultIndexes[j] == i) {
                shouldDelete = true;
                break;
            }
        }

        if (shouldDelete) {
            // Found a branch to delete at index 'i' in branchArray
            cout << "Deleted Branch ID: " << branchArray[i].id << endl;

            // Shift elements one position to the left (overwriting branchArray[i])
            for (int k = i; k < branchCount - 1; ++k) {
                branchArray[k] = branchArray[k + 1];
            }

            branchCount--;
            successfulDeletions++;
        }
    }
    searchResultCount = 0; // The result list is now entirely invalid
    cout << "\nBatch deletion complete. " << successfulDeletions << " branch(es) deleted.\n";

	// Parraksta visu failu
	ofstream file(branchesDB, ios::trunc);
	if (!file) {
		cout << "Error opening file for writing!" << endl;
		return;
	}

	for (int i = 0; i < branchCount; i++) {
		file << branchArray[i].id << "|" << branchArray[i].name << "|" << branchArray[i].address << endl;
	}
	file.close();
}

void deleteDepartments() {
    if (searchResultCount == 0) {
        return;
    }

    cout << "\n--- WARNING: BATCH DELETION ---\n";
    cout << "Do you want to delete ALL " << searchResultCount
        << " branches listed above? (Y/N): ";

    char confirm;
    cin >> confirm;
    cin.ignore();

    if (confirm != 'y' && confirm != 'Y') {
        cout << "Deletion aborted by user.\n";
        searchResultCount = 0; // Clear results even on abort
        return;
    }

    cout << "Deleting departments...\n";
    int successfulDeletions = 0;
    for (int i = departmentCount - 1; i >= 0; --i) {
        // Check if the current main array index 'i' is in the list of results to be deleted
        bool shouldDelete = false;
        for (int j = 0; j < searchResultCount; ++j) {
            if (searchResultIndexes[j] == i) {
                shouldDelete = true;
                break;
            }
        }

        if (shouldDelete) {
            // Found a branch to delete at index 'i' in branchArray
            cout << "Deleted Department ID: " << departmentArray[i].id << endl;

            // Shift elements one position to the left (overwriting branchArray[i])
            for (int k = i; k < departmentCount - 1; ++k) {
                departmentArray[k] = departmentArray[k + 1];
            }

            departmentCount--;
            successfulDeletions++;
        }
    }
    searchResultCount = 0; // The result list is now entirely invalid
    cout << "\nBatch deletion complete. " << successfulDeletions << " department(s) deleted.\n";

    ofstream file(departmentsDB, ios::trunc);
    if (!file) {
        cout << "Error opening file for writing!" << endl;
        return;
    }

    for (int i = 0; i < departmentCount; i++) {
        file << departmentArray[i].id << "|" << departmentArray[i].name << "|" << departmentArray[i].branch_id << endl;
    }
    file.close();
    cout << "Branch data updated successfully!" << endl;
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

            // --- KASK?DES DZ?ŠANA: Kontu t?r?šana ---
            // Ejam cauri kontu mas?vam un dz?šam tos, kas pieder šim klientam
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

            // --- Klienta dz?šana ---
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