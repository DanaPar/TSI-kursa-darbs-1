#ifndef MENU_H
#define MENU_H

#include "dataTypes.h"

void inputManager(int& option, int min, int max);
void clearScreenWithDelay(int sec);
void runProgram();
MenuState displayMainMenu();
MenuState displayBranchManagement();
MenuState displayDepartmentManagement();
MenuState displayEmployeeManagement();
MenuState displayClientManagement();
MenuState displayAccountManagement();
//MenuState displayPaymentManagement();
MenuState displayBranchSearchMenu();
MenuState displayBranchDeleteMenu();
MenuState displayDepartmentSearchMenu();
MenuState displayDepartmentDeleteMenu();
MenuState displayEmployeeSearchMenu();

#endif
