#include "dataTypes.h"
#include "functions.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <algorithm> // for transform

using namespace std;
void displaySearchResults(int type);
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
//void searchBranchByName();
//void searchBranchByAddress();


void displaySearchResults(int type) {
    // Assuming type 1 is for Branches
    if (type == 1) {
        for (int i = 0; i < searchResultCount; ++i) {
            int index = searchResultIndexes[i];
            const Branch& b = branchArray[index];
            cout << "Result #" << (i + 1) << " (Index: " << index << "): ";
            cout << "ID: " << b.id << ", Name: " << b.name << ", Address: " << b.address << "\n";
        }
    }
    // You would add 'else if (type == 2)' for departments, etc.
}