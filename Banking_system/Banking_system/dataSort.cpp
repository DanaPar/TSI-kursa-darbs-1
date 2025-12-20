#include "functions.h"
#include "dataTypes.h"
#include <string>

using namespace std;

void sortBranchesById(bool ascending) {
    if (branchCount == 0) return;

    searchResultCount = branchCount;
    for (int i = 0; i < branchCount; ++i) {
        searchResultIndexes[i] = i;
    }

    for (int i = 0; i < searchResultCount - 1; i++) {
        int bestIndex = i;
        for (int j = i + 1; j < searchResultCount; j++) {
            int indexA = searchResultIndexes[j];
            int indexB = searchResultIndexes[bestIndex];

            if (isOrderedCorrect(branchArray[indexA].id, branchArray[indexB].id, ascending)) {
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
    if (branchCount == 0) return;

    searchResultCount = branchCount;
    for (int i = 0; i < branchCount; ++i) {
        searchResultIndexes[i] = i;
    }

    for (int i = 0; i < searchResultCount - 1; i++) {
        int bestIndex = i;
        for (int j = i + 1; j < searchResultCount; j++) {
            int indexA = searchResultIndexes[j];
            int indexB = searchResultIndexes[bestIndex];

            if (isOrderedCorrect(branchArray[indexA].name, branchArray[indexB].name, ascending)) {
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
    if (departmentCount == 0) return;

    searchResultCount = departmentCount;
    for (int i = 0; i < departmentCount; ++i) {
        searchResultIndexes[i] = i;
    }

    for (int i = 0; i < searchResultCount - 1; i++) {
        int bestIndex = i;
        for (int j = i + 1; j < searchResultCount; j++) {
            int indexA = searchResultIndexes[j];
            int indexB = searchResultIndexes[bestIndex];

            if (isOrderedCorrect(departmentArray[indexA].name, departmentArray[indexB].name, ascending)) {
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

void sortEmployeesByName(bool ascending) {
    if (employeeCount == 0) return;

    searchResultCount = employeeCount;
    for (int i = 0; i < employeeCount; ++i) {
        searchResultIndexes[i] = i;
    }

    for (int i = 0; i < searchResultCount - 1; i++) {
        int bestIndex = i;
        for (int j = i + 1; j < searchResultCount; j++) {
            int indexA = searchResultIndexes[j];
            int indexB = searchResultIndexes[bestIndex];
            string fullNameA = employeeArray[indexA].name + " " + employeeArray[indexA].surname;
            string fullNameB = employeeArray[indexB].name + " " + employeeArray[indexB].surname;

            if (isOrderedCorrect(fullNameA, fullNameB, ascending)) {
                bestIndex = j;
            }
        }

        if (bestIndex != i) {
            int temp = searchResultIndexes[i];
            searchResultIndexes[i] = searchResultIndexes[bestIndex];
            searchResultIndexes[bestIndex] = temp;
        }
    }
    displayEmployees(true);
}

void sortEmployeesByAccessLevel(bool ascending) {
    if (employeeCount == 0) return;

    searchResultCount = employeeCount;
    for (int i = 0; i < employeeCount; ++i) {
        searchResultIndexes[i] = i;
    }

    for (int i = 0; i < searchResultCount - 1; i++) {
        int bestIndex = i;
        for (int j = i + 1; j < searchResultCount; j++) {
            int indexA = searchResultIndexes[j];
            int indexB = searchResultIndexes[bestIndex];
            int levelA = (int)employeeArray[indexA].access_level;
            int levelB = (int)employeeArray[indexB].access_level;

            if (isOrderedCorrect(levelA, levelB, ascending)) {
                bestIndex = j;
            }
        }

        if (bestIndex != i) {
            int temp = searchResultIndexes[i];
            searchResultIndexes[i] = searchResultIndexes[bestIndex];
            searchResultIndexes[bestIndex] = temp;
        }
    }
    displayEmployees(true);
}

void sortClientsByName(bool ascending) {
    if (clientCount == 0) return;

    searchResultCount = clientCount;
    for (int i = 0; i < clientCount; ++i) {
        searchResultIndexes[i] = i;
    }

    for (int i = 0; i < searchResultCount - 1; i++) {
        int bestIndex = i;
        for (int j = i + 1; j < searchResultCount; j++) {
            int indexA = searchResultIndexes[j];
            int indexB = searchResultIndexes[bestIndex];

            string fullNameA = clientArray[indexA].name + " " + clientArray[indexA].surname;
            string fullNameB = clientArray[indexB].name + " " + clientArray[indexB].surname;

            if (isOrderedCorrect(fullNameA, fullNameB, ascending)) {
                bestIndex = j;
            }
        }

        if (bestIndex != i) {
            int temp = searchResultIndexes[i];
            searchResultIndexes[i] = searchResultIndexes[bestIndex];
            searchResultIndexes[bestIndex] = temp;
        }
    }
    displayClients(true);
}

void sortClientsByType(bool ascending) {
    if (clientCount == 0) {
        return;
    }

    searchResultCount = clientCount;
    for (int i = 0; i < clientCount; ++i) {
        searchResultIndexes[i] = i;
    }

    for (int i = 0; i < searchResultCount - 1; i++) {
        int bestIndex = i;
        for (int j = i + 1; j < searchResultCount; j++) {
            int indexA = searchResultIndexes[j];
            int indexB = searchResultIndexes[bestIndex];

            int typeA = (int)clientArray[indexA].type;
            int typeB = (int)clientArray[indexB].type;

            if (isOrderedCorrect(typeA, typeB, ascending)) {
                bestIndex = j;
            }
        }

        if (bestIndex != i) {
            int temp = searchResultIndexes[i];
            searchResultIndexes[i] = searchResultIndexes[bestIndex];
            searchResultIndexes[bestIndex] = temp;
        }
    }
    displayClients(true);
}

void sortAccountsByBalance(bool ascending) {
    if (accountCount == 0) return;

    searchResultCount = accountCount;
    for (int i = 0; i < accountCount; ++i) {
        searchResultIndexes[i] = i;
    }

    for (int i = 0; i < searchResultCount - 1; i++) {
        int bestIndex = i; 

        for (int j = i + 1; j < searchResultCount; j++) {
            int indexA = searchResultIndexes[j];
            int indexB = searchResultIndexes[bestIndex];

            double balanceA = accountArray[indexA].balance;
            double balanceB = accountArray[indexB].balance;

            if (isOrderedCorrect(balanceA, balanceB, ascending)) {
                bestIndex = j;
            }
        }

        if (bestIndex != i) {
            int temp = searchResultIndexes[i];
            searchResultIndexes[i] = searchResultIndexes[bestIndex];
            searchResultIndexes[bestIndex] = temp;
        }
    }
    displayAccounts(true);
}

void sortAccountsByOwner(bool ascending) {
    if (accountCount == 0) return;

    searchResultCount = accountCount;
    for (int i = 0; i < accountCount; ++i) {
        searchResultIndexes[i] = i;
    }

    for (int i = 0; i < searchResultCount - 1; i++) {
        int bestIndex = i;

        for (int j = i + 1; j < searchResultCount; j++) {
            int accIdA = searchResultIndexes[j];
            int accIdB = searchResultIndexes[bestIndex];

            string nameA = "", nameB = "";

            for (int k = 0; k < clientCount; k++) {
                if (clientArray[k].id == accountArray[accIdA].owner_id) {
                    nameA = clientArray[k].name + " " + clientArray[k].surname;
                    break;
                }
            }

            for (int k = 0; k < clientCount; k++) {
                if (clientArray[k].id == accountArray[accIdB].owner_id) {
                    nameB = clientArray[k].name + " " + clientArray[k].surname;
                    break;
                }
            }

            if (isOrderedCorrect(nameA, nameB, ascending)) {
                bestIndex = j;
            }
        }

        if (bestIndex != i) {
            int temp = searchResultIndexes[i];
            searchResultIndexes[i] = searchResultIndexes[bestIndex];
            searchResultIndexes[bestIndex] = temp;
        }
    }
    displayAccounts(true);
}

bool isOrderedCorrect(const string& a, const string& b, bool ascending) {
    string lowerA = toLower(a);
    string lowerB = toLower(b);
    if (ascending) {
        if (lowerA < lowerB) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        if (lowerA > lowerB) {
            return true;
        }
        else {
            return false;
        }
    }
}

bool isOrderedCorrect(int a, int b, bool ascending) {
    if (ascending) {
        if (a < b) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        if (a > b) {
            return true;
        }
        else {
            return false;
        }
    }
}

bool isOrderedCorrect(double a, double b, bool ascending) {
    if (ascending) {
        if (a < b) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        if (a > b) {
            return true;
        }
        else {
            return false;
        }
    }
}