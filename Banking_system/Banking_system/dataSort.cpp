#include "functions.h"
#include "dataTypes.h"
#include <string>

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

void sortEmployeesByName(bool ascending) {
    if (employeeCount == 0) {
        return;
    }

    searchResultCount = employeeCount;
    for (int i = 0; i < employeeCount; ++i) {
        searchResultIndexes[i] = i;
    }

    for (int i = 0; i < searchResultCount - 1; i++) {
        int bestIndex = i;
        for (int j = i + 1; j < searchResultCount; j++) {
            int indexA = searchResultIndexes[j];
            int indexB = searchResultIndexes[bestIndex];

            string nameA = employeeArray[indexA].name + " " + employeeArray[indexA].surname;
            string nameB = employeeArray[indexB].name + " " + employeeArray[indexB].surname;

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

    displayEmployees(true);
}

void sortEmployeesByAccessLevel(bool ascending) {
    if (employeeCount == 0) {
        return;
    }

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

            bool isJBetter = false;

            if (ascending) {
                if (levelA < levelB) {
                    isJBetter = true;
                }
            }
            else {
                if (levelA > levelB) {
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
    displayEmployees(true);
}

void sortClientsByName(bool ascending) {
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

            string nameA = clientArray[indexA].name + " " + clientArray[indexA].surname;
            string nameB = clientArray[indexB].name + " " + clientArray[indexB].surname;

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

            bool isJBetter = false;

            if (ascending) {
                if (typeA < typeB) {
                    isJBetter = true;
                }
            }
            else {

                if (typeA > typeB) {
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
    displayClients(true);
}

void sortAccountsByBalance(bool ascending) {
    if (accountCount == 0) {
        return;
    }

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

            bool isJBetter = false;

            if (ascending) {
                if (balanceA < balanceB) {
                    isJBetter = true;
                }
            }
            else {
                if (balanceA > balanceB) {
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
            int accIdxA = searchResultIndexes[j];
            int accIdxB = searchResultIndexes[bestIndex];

            string nameA = "", nameB = "";

            for (int k = 0; k < clientCount; k++) {
                if (clientArray[k].id == accountArray[accIdxA].owner_id) {
                    nameA = clientArray[k].name + " " + clientArray[k].surname;
                    break;
                }
            }

            for (int k = 0; k < clientCount; k++) {
                if (clientArray[k].id == accountArray[accIdxB].owner_id) {
                    nameB = clientArray[k].name + " " + clientArray[k].surname;
                    break;
                }
            }

            bool isJBetter = false;
            if (ascending) {
                if (nameA < nameB) isJBetter = true;
            }
            else {
                if (nameA > nameB) isJBetter = true;
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

    displayAccounts(true);
}