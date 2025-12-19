#ifndef STATISTICS_H
#define STATISTICS_H

#include "dataTypes.h"

double getBranchAssets(int branchId);
int getBranchEmployeeCount(int branchId);
int getBranchClientCount(int branchId);
int getClientCountByType(int branchId, ClientType type);
double getAverageBalance(int branchId, ClientType type);


#endif 

