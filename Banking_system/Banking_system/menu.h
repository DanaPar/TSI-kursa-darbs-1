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
MenuState displayBranchSearchMenu();
MenuState displayBranchDeleteMenu();
MenuState displayDepartmentSearchMenu();
MenuState displayDepartmentDeleteMenu();
MenuState displayEmployeeSearchMenu();
MenuState displayEmployeeDeleteMenu();
MenuState displayClientSearchMenu();
MenuState displayClientDeleteMenu();
MenuState displayAccountSearchMenu();
MenuState displayAccountDeleteMenu();
MenuState sortBranchesMenu();
MenuState sortDepartmentsMenu();
MenuState sortEmployeesMenu();
MenuState sortClientsMenu();
MenuState sortAccountsMenu();

#endif
