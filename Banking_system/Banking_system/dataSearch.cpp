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
