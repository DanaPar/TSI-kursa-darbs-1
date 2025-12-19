#include "dataTypes.h"
#include "menu.h"
#include "functions.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <chrono>
#include <thread>

using namespace std;


void inputManager(int& option, int min, int max) {
    while (!(cin >> option) || option < min || option > max) {
        cout << "Wrong input! Enter number from " << min << " to " << max << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();
}

void clearScreenWithDelay(int sec) {
    this_thread::sleep_for(chrono::seconds(sec));
#ifdef _WIN32
    system("cls");      // Windows
#else
    system("clear");    // Mac/Unix
#endif
}

// ------ GALVENA PROGRAMMAS CILPA ------
void runProgram() {
    MenuState currentState = STATE_MAIN_MENU;

    while (currentState != STATE_EXIT) {

        switch (currentState) {
        case STATE_MAIN_MENU:
            currentState = displayMainMenu();
            break;
        case STATE_BRANCH_MGMT:
            currentState = displayBranchManagement();
            break;
        case STATE_BRANCH_SEARCH:
            currentState = displayBranchSearchMenu();
            break;
        case STATE_BRANCH_DELETE:
            currentState = displayBranchDeleteMenu();
            break;
        case STATE_BRANCH_SORT:
            currentState = sortBranchesMenu();
            break;
        case STATE_DEPT_MGMT:
            currentState = displayDepartmentManagement();
            break;
        case STATE_DEPT_SEARCH:
            currentState = displayDepartmentSearchMenu();
            break;
        case STATE_DEPT_DELETE:
            currentState = displayDepartmentDeleteMenu();
            break;
        case STATE_DEPT_SORT:
            currentState = sortDepartmentsMenu();
            break;
        case STATE_EMPLOYEE_MGMT:
            currentState = displayEmployeeManagement();
            break;
        case STATE_EMPLOYEE_SEARCH:
            currentState = displayEmployeeSearchMenu();
            break;
        case STATE_EMPLOYEE_DELETE:
            currentState = displayEmployeeDeleteMenu();
            break;
        case STATE_EMPLOYEE_SORT:
            currentState = sortEmployeesMenu();
            break;
        case STATE_CLIENT_MGMT:
            currentState = displayClientManagement();
            break;
        case STATE_CLIENT_SEARCH:
            currentState = displayClientSearchMenu();
            break;
        case STATE_CLIENT_DELETE:
            currentState = displayClientDeleteMenu();
            break;
        case STATE_CLIENT_SORT:
            currentState = sortClientsMenu();
            break;
        case STATE_ACCOUNT_MGMT:
            currentState = displayAccountManagement();
            break;
        case STATE_ACCOUNT_SEARCH:
            currentState = displayAccountSearchMenu();
            break;
        case STATE_ACCOUNT_DELETE:
            currentState = displayAccountDeleteMenu();
            break;
        case STATE_ACCOUNT_SORT:
            currentState = sortAccountsMenu();
            break;
        case STATE_STATISTICS_MGMT:
            currentState = displayBranchStatisticsMenu();
            break;
        default:
            currentState = STATE_EXIT;
            break;
        }
    }

    cout << "Data being saved. Program being closed.\n";
}

MenuState displayMainMenu() {
    int option;

    cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
    cout << "                   MAIN MENU\n";
    cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
    cout << "Choose coresponding number:\n";
    cout << "1. Branch management\n";
    cout << "2. Department management\n";
    cout << "3. Employee management\n";
    cout << "4. Client management\n";
    cout << "5. Account management\n";
    cout << "6. Branch Statistics\n";
    cout << "7. Save and exit\n";
    cout << "Your choice: ";

    inputManager(option, 1, 7);
    clearScreenWithDelay(0);

    switch (option) {
    case 1: return STATE_BRANCH_MGMT;
    case 2: return STATE_DEPT_MGMT;
    case 3: return STATE_EMPLOYEE_MGMT;
    case 4: return STATE_CLIENT_MGMT;
    case 5: return STATE_ACCOUNT_MGMT;
    case 6:  return STATE_STATISTICS_MGMT;
    case 7: return STATE_EXIT;
    }
    return STATE_MAIN_MENU;
}

MenuState displayBranchManagement() {
    int option;

    cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
    cout << "                  MENU -> Branches\n";
    cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
    cout << "1. Add\n";
    cout << "2. Edit\n";
    cout << "3. Search\n";
    cout << "4. Delete\n";
    cout << "5. View\n";
    cout << "6. Back to Main Menu\n";
    cout << "Your choice: ";

    inputManager(option, 1, 6);
    clearScreenWithDelay(0);

    switch (option) {
    case 1:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "                  MENU -> Branches -> Add\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << setfill(' ');
        addBranch();
        clearScreenWithDelay(1);
        return STATE_BRANCH_MGMT;
    case 2:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "                  MENU -> Branches -> Edit\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        editBranch();
        clearScreenWithDelay(1);
        return STATE_BRANCH_MGMT;
    case 3:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "                  MENU -> Branches -> Search\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        return STATE_BRANCH_SEARCH;
    case 4:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "                  MENU -> Branches -> Delete\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        return STATE_BRANCH_DELETE;
    case 5:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "                  MENU -> Branches -> View\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        displayBranches(false);
        return STATE_BRANCH_SORT;
    case 6:
        return STATE_MAIN_MENU;
    }
    return STATE_BRANCH_MGMT;
}

MenuState displayBranchSearchMenu() {
    int option;

    cout << "1. Search by ID\n";
    cout << "2. Search by Name\n";
    cout << "3. Search by Address\n";
    cout << "4. Back to Branch Management Menu\n";
    cout << "Your choice: ";

    inputManager(option, 1, 4);
    clearScreenWithDelay(0);

    switch (option) {
    case 1:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "         MENU -> Branches -> Search by ID\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        searchBranchesById();
        return STATE_BRANCH_SEARCH;
    case 2:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "         MENU -> Branches -> Search by Name\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        searchBranchesByName();
        return STATE_BRANCH_SEARCH;
    case 3:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "         MENU -> Branches -> Search by Address\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        searchBranchesByAddress();
        return STATE_BRANCH_SEARCH;
    case 4:
        return STATE_BRANCH_MGMT;
    }
    return STATE_BRANCH_SEARCH;
}

MenuState displayBranchDeleteMenu() {
    int option;

    cout << "1. Delete by ID\n";
    cout << "2. Delete by Name\n";
    cout << "3. Delete by Address\n";
    cout << "4. Back to Branch Management Menu\n";
    cout << "Your choice: ";

    inputManager(option, 1, 4);
    clearScreenWithDelay(0);

    switch (option) {
    case 1:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "                  MENU -> Branches -> Delete by ID\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        searchBranchesById();
        deleteBranches();
        return STATE_BRANCH_DELETE;
    case 2:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "                  MENU -> Branches -> Delete by name\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        searchBranchesByName();
        deleteBranches();
        return STATE_BRANCH_DELETE;
    case 3:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "                  MENU -> Branches -> Delete by address\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        searchBranchesByAddress();
        deleteBranches();
        return STATE_BRANCH_DELETE;
    case 4:
        return STATE_BRANCH_MGMT;
    }
    return STATE_BRANCH_DELETE;
}

MenuState sortBranchesMenu() {
    int option;

    cout << "1. Sort by Id\n";
    cout << "2. Sort by Name\n";
    cout << "3. Back to Branch Management Menu\n";
    cout << "Your choice: ";

    inputManager(option, 1, 3);
 
    switch (option) {
    case 1:
        cout << "1. Sort ascending order\n";
        cout << "2. Sort descending order\n";
        cout << "3. Back to Branch Management Menu\n";
        cout << "Your choice: ";
        inputManager(option, 1, 3);
        clearScreenWithDelay(0);
        switch (option) {
        case 1: 
            cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
            cout << "                  MENU -> Branches -> View -> Sort by Id(ascending)\n";
            cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
            sortBranchesById(true);
            break;
        case 2:
            cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
            cout << "                  MENU -> Branches -> View -> Sort by Id(descending)\n";
            cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
            sortBranchesById(false);
            break;
        case 3: 
            clearScreenWithDelay(0); 
            return STATE_BRANCH_MGMT;
        }
        return STATE_BRANCH_SORT;
        case 2:
        cout << "1. Sort ascending order\n";
        cout << "2. Sort descending order\n";
        cout << "3. Back to Branch Management Menu\n";
        cout << "Your choice: ";
        inputManager(option, 1, 3);
        clearScreenWithDelay(0);
        switch (option) {
        case 1:
            cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
            cout << "                  MENU -> Branches -> View -> Sort by Name(ascending)\n";
            cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
            sortBranchesByName(true);
            break;
        case 2: 
            cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
            cout << "                  MENU -> Branches -> View -> Sort by Name(descending)\n";
            cout << setfill('=') << setw(115) << "" << setfill(' ') << endl; 
            sortBranchesByName(false);
            break;
        case 3: 
            clearScreenWithDelay(0);
            return STATE_BRANCH_MGMT;
        }
        return STATE_BRANCH_SORT;
    case 3:
        clearScreenWithDelay(0);
        return STATE_BRANCH_MGMT;
    }
    return STATE_BRANCH_SORT;
}

MenuState displayDepartmentManagement() {
    int option;

    cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
    cout << "                  MENU -> Departments\n";
    cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
    cout << "1. Add\n";
    cout << "2. Edit\n";
    cout << "3. Search\n";
    cout << "4. Delete\n";
    cout << "5. View\n";
    cout << "6. Back to Main Menu\n";
    cout << "Your choice: ";

    inputManager(option, 1, 6);
    clearScreenWithDelay(0);

    switch (option) {
    case 1:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "                  MENU -> Departments -> Add\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        addDepartment();
        clearScreenWithDelay(1);
        return STATE_DEPT_MGMT;
    case 2:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "                  MENU -> Departments -> Edit\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        editDepartment();
        clearScreenWithDelay(1);
        return STATE_DEPT_MGMT;
    case 3:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "                  MENU -> Departments -> Search\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        return STATE_DEPT_SEARCH;
    case 4:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "                  MENU -> Departments -> Delete\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        return STATE_DEPT_DELETE;
    case 5:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "                  MENU -> Departments -> View\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        displayDepartments(false);
        return STATE_DEPT_SORT;
    case 6:

        return STATE_MAIN_MENU;
    }
    return STATE_DEPT_MGMT;
}

MenuState displayDepartmentSearchMenu() {
    int option;

    cout << "1. Search by ID\n";
    cout << "2. Search by Name\n";
    cout << "3. Search by Branch\n";
    cout << "4. Back to Department Management Menu\n";
    cout << "Your choice: ";

    inputManager(option, 1, 4);
    clearScreenWithDelay(0);

    switch (option) {
    case 1:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "         MENU -> Departments -> Search by ID\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        searchDepartmentsById();
        return STATE_DEPT_SEARCH;
    case 2:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "         MENU -> Departments -> Search by Name\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        searchDepartmentsByName();
        return STATE_DEPT_SEARCH;
    case 3:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "         MENU -> Departments -> Search by Branch\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        searchDepartmentsByBranch();
        return STATE_DEPT_SEARCH;
    case 4:
        return STATE_DEPT_MGMT;
    }
    return STATE_DEPT_SEARCH;
}

MenuState displayDepartmentDeleteMenu() {
    int option;

    cout << "1. Delete by ID\n";
    cout << "2. Delete by Name\n";
    cout << "3. Delete by Branch\n";
    cout << "4. Back to Department Management Menu\n";
    cout << "Your choice: ";

    inputManager(option, 1, 4);
    clearScreenWithDelay(0);

    switch (option) {
    case 1:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "         MENU -> Departments -> Delete by ID\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        searchDepartmentsById();
        deleteDepartments();
        return STATE_DEPT_DELETE;
    case 2:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "         MENU -> Departments -> Delete by Name\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        searchDepartmentsByName();
        deleteDepartments();
        return STATE_DEPT_DELETE;
    case 3:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "         MENU -> Departments -> Delete by Branch\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        searchDepartmentsByBranch();
        deleteDepartments();
        return STATE_DEPT_DELETE;
    case 4:
        return STATE_DEPT_MGMT;
    }
    return STATE_DEPT_DELETE;
}

MenuState sortDepartmentsMenu() {
    int option;

    cout << "1. Sort by Name\n";
    cout << "2. Back to Department Management Menu\n";
    cout << "Your choice: ";

    inputManager(option, 1, 2);

    switch (option) {
        case 1:
        cout << "1. Sort ascending order\n";
        cout << "2. Sort descending order\n";
        cout << "3. Back to Department Management Menu\n";
        cout << "Your choice: ";
        inputManager(option, 1, 3);
        clearScreenWithDelay(0);
        switch (option) {
        case 1:
            cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
            cout << "                  MENU -> Branches -> View -> Sort by Name(ascending)\n";
            cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
            sortDepartmentsByName(true);
            break;
        case 2:
            cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
            cout << "                  MENU -> Branches -> View -> Sort by Name(descending)\n";
            cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
            sortDepartmentsByName(false);
            break;
        case 3:
            clearScreenWithDelay(0);
            return STATE_DEPT_MGMT;
        }
        return STATE_DEPT_SORT;
        case 2:
        clearScreenWithDelay(0);
        return STATE_DEPT_MGMT;
    }
    return STATE_DEPT_SORT;
}

MenuState displayEmployeeManagement() {
    int option;

    cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
    cout << "                  MENU -> Employees\n";
    cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
    cout << "1. Add\n";
    cout << "2. Edit\n";
    cout << "3. Search\n";
    cout << "4. Delete\n";
    cout << "5. View\n";
    cout << "6. Back to Main Menu\n";
    cout << "Your choice: ";

    inputManager(option, 1, 6);
    clearScreenWithDelay(0);

    switch (option) {
    case 1:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "                  MENU -> Employees -> Add\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        addEmployee();
        clearScreenWithDelay(2);
        return STATE_EMPLOYEE_MGMT;
    case 2:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "                  MENU -> Employees -> Edit\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        editEmployee();
        clearScreenWithDelay(1);
        return STATE_EMPLOYEE_MGMT;
    case 3:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "                  MENU -> Employees -> Search\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        return STATE_EMPLOYEE_SEARCH;
    case 4:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "                  MENU -> Employees -> Delete\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        return STATE_EMPLOYEE_DELETE;
    case 5:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "                  MENU -> Employees -> View\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        displayEmployees(false);
        return STATE_EMPLOYEE_SORT;
    case 6:

        return STATE_MAIN_MENU;
    }
    return STATE_EMPLOYEE_MGMT;
}

MenuState displayEmployeeSearchMenu() {
    int option;

    cout << "1. Search by ID\n";
    cout << "2. Search by Name\n";
    cout << "3. Search by Department\n";
    cout << "4. Search by Branch\n";
    cout << "5. Back to Employee Management Menu\n";
    cout << "Your choice: ";

    inputManager(option, 1, 5);
    clearScreenWithDelay(0);

    switch (option) {
    case 1:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "         MENU -> Employees -> Search by ID\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        searchEmployeesById();
        return STATE_EMPLOYEE_SEARCH;
    case 2:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "         MENU -> Employees -> Search by Name\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        searchEmployeesByName();
        return STATE_EMPLOYEE_SEARCH;
    case 3:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "         MENU -> Employees -> Search by Department\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        searchEmployeesByDepartment();
        return STATE_EMPLOYEE_SEARCH;
    case 4:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "         MENU -> Employees -> Search by Branch\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        searchEmployeesByBranch();
        return STATE_EMPLOYEE_SEARCH;
    case 5:
        return STATE_EMPLOYEE_MGMT;
    }
    return STATE_EMPLOYEE_SEARCH;
}

MenuState displayEmployeeDeleteMenu() {
    int option;

    cout << "1. Delete by ID\n";
    cout << "2. Delete by Name\n";
    cout << "3. Delete by Department\n";
    cout << "4. Delete By Branch\n";
    cout << "5. Back to Employee Management Menu\n";
    cout << "Your choice: ";

    inputManager(option, 1, 5);
    clearScreenWithDelay(0);

    switch (option) {
    case 1:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "         MENU -> Employees -> Delete by ID\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        searchEmployeesById();
        deleteEmployees();
        return STATE_EMPLOYEE_DELETE;
    case 2:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "         MENU -> Employees -> Delete by Name\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        searchEmployeesByName();
        deleteEmployees();
        return STATE_EMPLOYEE_DELETE;
    case 3:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "         MENU -> Employees -> Delete by Department\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        searchEmployeesByDepartment();
        deleteEmployees();
        return STATE_EMPLOYEE_DELETE;
    case 4:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "         MENU -> Employees -> Delete by Branch\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        searchEmployeesByBranch();
        deleteEmployees();
        return STATE_EMPLOYEE_DELETE;
    case 5:
        return STATE_EMPLOYEE_MGMT;
    }
    return STATE_EMPLOYEE_DELETE;
}

MenuState sortEmployeesMenu() {
    int option;

    cout << "1. Sort by Name\n";
    cout << "2. Sort by Access Level\n";
    cout << "3. Back to Employee Management Menu\n";
    cout << "Your choice: ";

    inputManager(option, 1, 3);

    switch (option) {
    case 1:
        cout << "1. Sort ascending order\n";
        cout << "2. Sort descending order\n";
        cout << "3. Back to Employee Management Menu\n";
        cout << "Your choice: ";
        inputManager(option, 1, 3);
        clearScreenWithDelay(0);
        switch (option) {
        case 1:
            cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
            cout << "                  MENU -> Employees -> View -> Sort by Name(ascending)\n";
            cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
            sortEmployeesByName(true);
            break;
        case 2:
            cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
            cout << "                  MENU -> Employees -> View -> Sort by Name(descending)\n";
            cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
            sortEmployeesByName(false);
            break;
        case 3:
            clearScreenWithDelay(0);
            return STATE_EMPLOYEE_MGMT;
        }
        return STATE_EMPLOYEE_SORT;
        case 2:
        cout << "1. Sort ascending order\n";
        cout << "2. Sort descending order\n";
        cout << "3. Back to Branch Management Menu\n";
        cout << "Your choice: ";
        inputManager(option, 1, 3);
        clearScreenWithDelay(0);
        switch (option) {
        case 1:
            cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
            cout << "                  MENU -> Branches -> View -> Sort by Access Level(ascending)\n";
            cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
            sortEmployeesByAccessLevel(true);
            break;
        case 2:
            cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
            cout << "                  MENU -> Branches -> View -> Sort by Access level(descending)\n";
            cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
            sortEmployeesByAccessLevel(false);
            break;
        case 3:
            clearScreenWithDelay(0);
            return STATE_EMPLOYEE_MGMT;
        }
        return STATE_EMPLOYEE_SORT;
    case 3:
        clearScreenWithDelay(0);
        return STATE_EMPLOYEE_MGMT;
    }
    return STATE_EMPLOYEE_SORT;
}

MenuState displayClientManagement() {
    int option;

    cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
    cout << "                  MENU -> Clients\n";
    cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
    cout << "1. Add\n";
    cout << "2. Edit\n";
    cout << "3. Search\n";
    cout << "4. Delete\n";
    cout << "5. View\n";
    cout << "6. Back to Main Menu\n";
    cout << "Your choice: ";

    inputManager(option, 1, 6);
    clearScreenWithDelay(0);

    switch (option) {
    case 1:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "                  MENU -> Clients -> Add\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        addClient();
        clearScreenWithDelay(1);
        return STATE_CLIENT_MGMT;
    case 2:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "                  MENU -> Clients -> Edit\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        editClient();
        clearScreenWithDelay(1);
        return STATE_CLIENT_MGMT;
    case 3:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "                  MENU -> Clients -> Search\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        return STATE_CLIENT_SEARCH;
    case 4:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "                  MENU -> Clients -> Delete\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        return STATE_CLIENT_DELETE;
    case 5:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "                  MENU -> Clients -> View\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        displayClients(false);
        return STATE_CLIENT_SORT;
    case 6:

        return STATE_MAIN_MENU;
    }
    return STATE_CLIENT_MGMT;
}

MenuState displayClientSearchMenu() {
    int option;

    cout << "1. Search by Name\n";
    cout << "2. Search by Branch\n";
    cout << "3. Back to Employee Management Menu\n";
    cout << "Your choice: ";

    inputManager(option, 1, 3);
    clearScreenWithDelay(0);

    switch (option) {
    case 1:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "         MENU -> Clients -> Search by Name\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        searchClientsByName();
        return STATE_CLIENT_SEARCH;
    case 2:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "         MENU -> Clients -> Search by Branch\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        searchClientsByBranch();
        return STATE_CLIENT_SEARCH;
    case 3:
        return STATE_CLIENT_MGMT;
    }
    return STATE_CLIENT_SEARCH;
}

MenuState displayClientDeleteMenu() {
    int option;

    cout << "1. Delete by Name\n";
    cout << "2. Delete by Branch\n";
    cout << "3. Back to Client Management Menu\n";
    cout << "Your choice: ";

    inputManager(option, 1, 3);
    clearScreenWithDelay(0);

    switch (option) {
    case 1:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "         MENU -> Clients -> Delete by Name\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        searchClientsByName();
        deleteClients();
        return STATE_CLIENT_DELETE;
    case 2:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "         MENU -> Clients -> Delete by Branch\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        searchClientsByBranch();
        deleteClients();
        return STATE_CLIENT_DELETE;
    case 3:
        return STATE_CLIENT_MGMT;
    }
    return STATE_CLIENT_DELETE;
}

MenuState sortClientsMenu() {
    int option;

    cout << "1. Sort by Name\n";
    cout << "2. Sort by Type\n";
    cout << "3. Back to Clients Management Menu\n";
    cout << "Your choice: ";

    inputManager(option, 1, 3);

    switch (option) {
    case 1:
        cout << "1. Sort ascending order\n";
        cout << "2. Sort descending order\n";
        cout << "3. Back to Clients Management Menu\n";
        cout << "Your choice: ";
        inputManager(option, 1, 3);
        clearScreenWithDelay(0);
        switch (option) {
        case 1:
            cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
            cout << "                  MENU -> Clients -> View -> Sort by Name(ascending)\n";
            cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
            sortClientsByName(true);
            break;
        case 2:
            cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
            cout << "                  MENU -> Clients -> View -> Sort by Name(descending)\n";
            cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
            sortClientsByName(false);
            break;
        case 3:
            clearScreenWithDelay(0);
            return STATE_CLIENT_MGMT;
        }
        return STATE_CLIENT_SORT;
    case 2:
        cout << "1. Sort ascending order\n";
        cout << "2. Sort descending order\n";
        cout << "3. Back to Branch Management Menu\n";
        cout << "Your choice: ";
        inputManager(option, 1, 3);
        clearScreenWithDelay(0);
        switch (option) {
        case 1:
            cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
            cout << "                  MENU -> Clients -> View -> Sort by Type(corporate firs)\n";
            cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
            sortClientsByType(true);
            break;
        case 2:
            cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
            cout << "                  MENU -> Clients -> View -> Sort by Type(private first)\n";
            cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
            sortClientsByType(false);
            break;
        case 3:
            clearScreenWithDelay(0);
            return STATE_CLIENT_MGMT;
        }
        return STATE_CLIENT_SORT;
    case 3:
        clearScreenWithDelay(0);
        return STATE_CLIENT_MGMT;
    }
    return STATE_CLIENT_SORT;
}

MenuState displayAccountManagement() {
    int option;

    cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
    cout << "                  MENU -> Accounts\n";
    cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
    cout << "1. Add\n";
    cout << "2. Edit\n";
    cout << "3. Search\n";
    cout << "4. Delete\n";
    cout << "5. View\n";
    cout << "6. Back to Main Menu\n";
    cout << "Your choice: ";

    inputManager(option, 1, 6);
    clearScreenWithDelay(0);

    switch (option) {
    case 1:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "                  MENU -> Accounts -> Add\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        addAccount();
        clearScreenWithDelay(1);
        return STATE_ACCOUNT_MGMT;
    case 2:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "                  MENU -> Accounts -> Edit\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        editAccount();
        clearScreenWithDelay(1);
        return STATE_ACCOUNT_MGMT;
    case 3:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "                  MENU -> Accounts -> Search\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        return STATE_ACCOUNT_SEARCH;
    case 4:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "                  MENU -> Accounts -> Delete\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "Pagaidam neimplementeta: dzest kontu\n";
        return STATE_ACCOUNT_DELETE;
    case 5:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "                  MENU -> Accounts -> View\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        displayAccounts(false);
        return STATE_ACCOUNT_SORT;
    case 6:
        return STATE_MAIN_MENU;
    }
    return STATE_ACCOUNT_MGMT;
}

MenuState displayAccountSearchMenu() {
    int option;

    cout << "1. Search by account Number\n";
    cout << "2. Search by owner Name\n";
    cout << "3. Search by Balance\n";
    cout << "4. Back to Account Management Menu\n";
    cout << "Your choice: ";

    inputManager(option, 1, 4);
    clearScreenWithDelay(0);

    switch (option) {
    case 1:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "         MENU -> Accounts -> Search by account Number\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        searchAccountByNumber();
        return STATE_ACCOUNT_SEARCH;
    case 2:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "         MENU -> Accounts -> Search by owner Name\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        searchAccountByOwner();
        return STATE_ACCOUNT_SEARCH;
    case 3:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "         MENU -> Accounts -> Search by Balance\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "no implementation for now";
        return STATE_ACCOUNT_SEARCH;
    case 4:
        return STATE_ACCOUNT_MGMT;
    }
    return STATE_ACCOUNT_SEARCH;
}

MenuState displayAccountDeleteMenu() {
    int option;

    cout << "1. Delete by account Number\n";
    cout << "2. Delete by Owner\n";
    cout << "3. Back to Account Management Menu\n";
    cout << "Your choice: ";

    inputManager(option, 1, 3);
    clearScreenWithDelay(0);

    switch (option) {
    case 1:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "                  MENU -> Accounts -> Delete by account Number\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        searchAccountByNumber();
        deleteBranches();
        return STATE_ACCOUNT_DELETE;
    case 2:
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        cout << "                  MENU -> Branches -> Delete by Owner\n";
        cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
        searchAccountByOwner();
        deleteAccounts();
        return STATE_ACCOUNT_DELETE;
    case 3:
        return STATE_ACCOUNT_MGMT;
    }
    return STATE_ACCOUNT_DELETE;
}

MenuState sortAccountsMenu() {
    int option;

    cout << "1. Sort by Balance\n";
    cout << "2. Sort by Owner\n";
    cout << "3. Back to Accounts Management Menu\n";
    cout << "Your choice: ";

    inputManager(option, 1, 3);

    switch (option) {
    case 1:
        cout << "1. Sort ascending order\n";
        cout << "2. Sort descending order\n";
        cout << "3. Back to Accounts Management Menu\n";
        cout << "Your choice: ";
        inputManager(option, 1, 3);
        clearScreenWithDelay(0);
        switch (option) {
        case 1:
            cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
            cout << "                  MENU -> Accounts -> View -> Sort by Balance(ascending)\n";
            cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
            sortAccountsByBalance(true);
            break;
        case 2:
            cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
            cout << "                  MENU -> Accounts -> View -> Sort by Balance(descending)\n";
            cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
            sortAccountsByBalance(false);
            break;
        case 3:
            clearScreenWithDelay(0);
            return STATE_ACCOUNT_MGMT;
        }
        return STATE_ACCOUNT_SORT;
    case 2:
        cout << "1. Sort ascending order\n";
        cout << "2. Sort descending order\n";
        cout << "3. Back to Accounts Management Menu\n";
        cout << "Your choice: ";
        inputManager(option, 1, 3);
        clearScreenWithDelay(0);
        switch (option) {
        case 1:
            cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
            cout << "                  MENU -> Accounts -> View -> Sort by Owner(ascending)\n";
            cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
            sortAccountsByOwner(true);
            break;
        case 2:
            cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
            cout << "                  MENU -> Accounts -> View -> Sort by Owner(descending)\n";
            cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
            sortAccountsByOwner(false);
            break;
        case 3:
            clearScreenWithDelay(0);
            return STATE_ACCOUNT_MGMT;
        }
        return STATE_ACCOUNT_SORT;
    case 3:
        clearScreenWithDelay(0);
        return STATE_ACCOUNT_MGMT;
    }
    return STATE_ACCOUNT_SORT;
}

MenuState displayBranchStatisticsMenu() {
    int option;

    cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
    cout << "                  MENU -> Branch Statistics\n";
    cout << setfill('=') << setw(115) << "" << setfill(' ') << endl;
    displayBranchStatistics();
    cout << "1. Back to Main Menu\n";
    cout << "Your choice: ";

    inputManager(option, 1, 1);
    clearScreenWithDelay(0);
    if (option == 1){
        return STATE_MAIN_MENU;
    }
    
    return STATE_MAIN_MENU;
}