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
MenuState displayBranchStatisticsMenu();
MenuState displayBranchSearchMenu();
MenuState displayDepartmentSearchMenu();
MenuState displayEmployeeSearchMenu();
MenuState displayClientSearchMenu();
MenuState displayAccountSearchMenu();
MenuState displayBranchDeleteMenu();
MenuState displayDepartmentDeleteMenu();
MenuState displayEmployeeDeleteMenu();
MenuState displayClientDeleteMenu();
MenuState displayAccountDeleteMenu();
MenuState sortBranchesMenu();
MenuState sortDepartmentsMenu();
MenuState sortEmployeesMenu();
MenuState sortClientsMenu();
MenuState sortAccountsMenu();

#endif
