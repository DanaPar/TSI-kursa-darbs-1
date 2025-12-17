#include "dataTypes.h"
#include "functions.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

void sortBranchesById(bool ascending) {
    if (branchCount == 0) {
        return;
    }

    searchResultCount = branchCount;
    for (int i = 0; i < branchCount; ++i) {
        searchResultIndexes[i] = i;
    }

    for (int i = 0; i < searchResultCount - 1; i++) {
        int bestIndex = i;
        for (int j = i + 1; j < searchResultCount; j++) {
            int indexA = searchResultIndexes[j];
            int indexB = searchResultIndexes[bestIndex];

            const int& nameA = branchArray[indexA].id;
            const int& nameB = branchArray[indexB].id;

            bool isJBetter = false;

            if (ascending) {
                if (nameA < nameB) {
                    isJBetter = true;
                }
            }
            else {
                if (nameA > nameB) {
                    isJBetter = true;
                }
            }

            if (isJBetter) {
                bestIndex = j;
            }
        }

        if (bestIndex != i) {
            int temp = searchResultIndexes[i];
            searchResultIndexes[i] = searchResultIndexes[bestIndex];
            searchResultIndexes[bestIndex] = temp;
        }
    }
    displayBranches(true);
}

void sortBranchesByName(bool ascending) {
    if (branchCount == 0) {
        return;
    }

    searchResultCount = branchCount;
    for (int i = 0; i < branchCount; ++i) {
        searchResultIndexes[i] = i;
    }

    for (int i = 0; i < searchResultCount - 1; i++) {
        int bestIndex = i;
        for (int j = i + 1; j < searchResultCount; j++) {
            int indexA = searchResultIndexes[j];
            int indexB = searchResultIndexes[bestIndex];

            const string& nameA = branchArray[indexA].name;
            const string& nameB = branchArray[indexB].name;

            bool isJBetter = false;

            if (ascending) {
                if (nameA < nameB) {
                    isJBetter = true;
                }
            }
            else {
                if (nameA > nameB) {
                    isJBetter = true;
                }
            }

            if (isJBetter) {
                bestIndex = j;
            }
        }

        if (bestIndex != i) {
            int temp = searchResultIndexes[i];
            searchResultIndexes[i] = searchResultIndexes[bestIndex];
            searchResultIndexes[bestIndex] = temp;
        }
    }
    displayBranches(true);
}

void sortDepartmentsByName(bool ascending) {
    if (departmentCount == 0) {
        return;
    }

    searchResultCount = departmentCount;
    for (int i = 0; i < departmentCount; ++i) {
        searchResultIndexes[i] = i;
    }

    for (int i = 0; i < searchResultCount - 1; i++) {
        int bestIndex = i;
        for (int j = i + 1; j < searchResultCount; j++) {
            int indexA = searchResultIndexes[j];
            int indexB = searchResultIndexes[bestIndex];

            const string& nameA = departmentArray[indexA].name;
            const string& nameB = departmentArray[indexB].name;

            bool isJBetter = false;

            if (ascending) {
                if (nameA < nameB) {
                    isJBetter = true;
                }
            }
            else {
                if (nameA > nameB) {
                    isJBetter = true;
                }
            }

            if (isJBetter) {
                bestIndex = j;
            }
        }

        if (bestIndex != i) {
            int temp = searchResultIndexes[i];
            searchResultIndexes[i] = searchResultIndexes[bestIndex];
            searchResultIndexes[bestIndex] = temp;
        }
    }
    displayDepartments(true);
}