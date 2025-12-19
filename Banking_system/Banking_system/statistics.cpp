#include "statistics.h"
#include "dataTypes.h"

double getBranchAssets(int branchId) {
	double total = 0;
    for (int i = 0; i < clientCount; i++) {
        if (clientArray[i].branch_id == branchId) {
            for (int j = 0; j < accountCount; j++) {
                if (accountArray[j].owner_id == clientArray[i].id) {
                    total += accountArray[j].balance;
                }
            }
        }
    }
    return total;
}

int getBranchEmployeeCount(int branchId) {
    int count = 0;
    for (int i = 0; i < departmentCount; i++) {
        if (departmentArray[i].branch_id == branchId) {
            for (int j = 0; j < employeeCount; j++) {
                if (employeeArray[j].department_id == departmentArray[i].id) {
                    count++;
                }
            }
        }
    }
    return count;
}

int getBranchClientCount(int branchId) {
    int count = 0;
    for (int i = 0; i < clientCount; i++) {
        if (clientArray[i].branch_id == branchId) count++;
    }
    return count;
}

int getClientCountByType(int branchId, ClientType type) {
    int count = 0;
    for (int i = 0; i < clientCount; i++) {
        if (clientArray[i].branch_id == branchId && clientArray[i].type == type) {
            count++;
        }
    }
    return count;
}

double getAverageBalance(int branchId, ClientType type) {
    double totalBalance = 0.0;
    int count = 0;

    for (int i = 0; i < clientCount; i++) {
        if (clientArray[i].branch_id == branchId && clientArray[i].type == type) {
            int clientId = clientArray[i].id;

            for (int j = 0; j < accountCount; j++) {
                if (accountArray[j].owner_id == clientId) {
                    totalBalance += accountArray[j].balance;
                }
            }
            count++;
        }
    }

    if (count == 0) return 0.0;
    return totalBalance / count;
}