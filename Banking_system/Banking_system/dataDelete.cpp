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