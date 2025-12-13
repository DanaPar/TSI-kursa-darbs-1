#ifndef MENU_H
#define MENU_H

#include "DataTypes.h"

void inputManager(int& option, int min, int max);
void runProgram();
MenuState displayMainMenu();
MenuState displayBranchManagement();
MenuState displayDepartmentManagement();
//MenuState displayEmployeeManagement();
//MenuState displayClientManagement();
//MenuState displayAccountManagement();
//MenuState displayPaymentManagement();

#endif
