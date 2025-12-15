#include "dataTypes.h"
#include "menu.h"
#include "functions.h"
#include <iostream>
#include <limits>
#include <cstdlib> //for system()
#include <chrono>       // Required for std::chrono::milliseconds
#include <thread>       // Required for std::this_thread::sleep_for

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
        case STATE_DEPT_MGMT:
            currentState = displayDepartmentManagement();
            break;
        case STATE_DEPT_SEARCH:
            currentState = displayDepartmentSearchMenu();
            break;
        case STATE_DEPT_DELETE:
            currentState = displayDepartmentDeleteMenu();
            break;
        case STATE_EMPLOYEE_MGMT:
            currentState = displayEmployeeManagement();
            break;
        case STATE_EMPLOYEE_SEARCH:
            currentState = displayEmployeeSearchMenu();
            break;
        case STATE_CLIENT_MGMT:
            currentState = displayClientManagement();
            break;
        case STATE_ACCOUNT_MGMT:
            currentState = displayAccountManagement();
            break;
        case STATE_PAYMENT_MGMT:
            // Neimplementetas izvelnes atgriezas uz sakumu
            currentState = STATE_MAIN_MENU;
            break;
        default:
            currentState = STATE_EXIT;
            break;
        }
    }

    cout << "Data being saved. Program being closed.\n";
}

// ------ MENU DISPLEJA FUNKCIJAS (Atgriez Nakamo Stavokli) ------

MenuState displayMainMenu() {
    int option;

    cout << "\n=======================================================\n";
    cout << "                   MAIN MENU\n";
    cout << "=======================================================\n";
    cout << "Choose coresponding number:\n";
    cout << "1. Branch management\n";
    cout << "2. Department management\n";
    cout << "3. Employee management\n";
    cout << "4. Client management\n";
    cout << "5. Account management\n";
    cout << "6. Payment management\n";
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
    case 6: 
        cout << "Pagaidam neimplementeta: Maksajumu parvaldiba. Atgriesanas uz Galveno izvelni.\n";
        return STATE_MAIN_MENU;
    case 7: return STATE_EXIT;
    }
    return STATE_MAIN_MENU;
}

MenuState displayBranchManagement() {
    int option;

    cout << "\n=======================================================\n";
    cout << "                  MENU -> Branches\n";
    cout << "=======================================================\n";
    cout << "1. Add\n";
    cout << "2. Edit\n";
    cout << "3. Search\n";
    cout << "4. Delete\n";
    cout << "5. View\n";
    cout << "6. Back to Main Menu\n";
    cout << "Your choice: ";

    inputManager(option, 1, 6);
#ifdef _WIN32
    system("cls");      // Windows
#else
    system("clear");    // Mac/Unix
#endif

    switch (option) {
    case 1:
        cout << "\n=======================================================\n";
        cout << "                  MENU -> Branches -> Add\n";
        cout << "=======================================================\n";
        addBranch();
        clearScreenWithDelay(1);
        return STATE_BRANCH_MGMT;
    case 2:
        cout << "\n=======================================================\n";
        cout << "                  MENU -> Branches -> Edit\n";
        cout << "=======================================================\n";
        editBranch();
        clearScreenWithDelay(1);
        return STATE_BRANCH_MGMT;
    case 3:
        cout << "\n=======================================================\n";
        cout << "                  MENU -> Branches -> Search\n";
        cout << "=======================================================\n";
        return STATE_BRANCH_SEARCH;
    case 4:
        cout << "\n=======================================================\n";
        cout << "                  MENU -> Branches -> Delete\n";
        cout << "=======================================================\n";
        return STATE_BRANCH_DELETE;
    case 5:
        cout << "\n=======================================================\n";
        cout << "                  MENU -> Branches -> View\n";
        cout << "=======================================================\n";
        displayBranches(false);
        return STATE_BRANCH_MGMT;
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
        cout << "\n=======================================================\n";
        cout << "         MENU -> Branches -> Search by ID\n";
        cout << "=======================================================\n";
        searchBranchesById(); // Assuming 1 means ID search criterion
        return STATE_BRANCH_SEARCH;
    case 2:
        cout << "\n=======================================================\n";
        cout << "         MENU -> Branches -> Search by Name\n";
        cout << "=======================================================\n";
        searchBranchesByName();
        return STATE_BRANCH_SEARCH;
    case 3:
        cout << "\n=======================================================\n";
        cout << "         MENU -> Branches -> Search by Address\n";
        cout << "=======================================================\n";
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
        cout << "\n=======================================================\n";
        cout << "                  MENU -> Branches -> Delete by ID\n";
        cout << "=======================================================\n";
        searchBranchesById();
        deleteBranches();
        return STATE_BRANCH_DELETE;
    case 2:
        cout << "\n=======================================================\n";
        cout << "                  MENU -> Branches -> Delete by name\n";
        cout << "=======================================================\n";
        searchBranchesByName();
        deleteBranches();
        return STATE_BRANCH_DELETE;
    case 3:
        cout << "\n=======================================================\n";
        cout << "                  MENU -> Branches -> Delete by address\n";
        cout << "=======================================================\n";
        searchBranchesByAddress();
        deleteBranches();
        return STATE_BRANCH_DELETE;
    case 4:
        return STATE_BRANCH_MGMT;
    }
    return STATE_BRANCH_DELETE;
}

MenuState displayDepartmentManagement() {
    int option;

    cout << "\n=======================================================\n";
    cout << "                  MENU -> Departments\n";
    cout << "=======================================================\n";
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
        cout << "\n=======================================================\n";
        cout << "                  MENU -> Departments -> Add\n";
        cout << "=======================================================\n";
        addDepartment();
        clearScreenWithDelay(1);
        return STATE_DEPT_MGMT;
    case 2:
        cout << "\n=======================================================\n";
        cout << "                  MENU -> Departments -> Edit\n";
        cout << "=======================================================\n";
        editDepartment();
        clearScreenWithDelay(1);
        return STATE_DEPT_MGMT;
    case 3:
        cout << "\n=======================================================\n";
        cout << "                  MENU -> Departments -> Search\n";
        cout << "=======================================================\n";
        return STATE_DEPT_SEARCH;
    case 4:
        cout << "\n=======================================================\n";
        cout << "                  MENU -> Departments -> Delete\n";
        cout << "=======================================================\n";
        return STATE_DEPT_DELETE;
    case 5:
        cout << "\n=======================================================\n";
        cout << "                  MENU -> Departments -> View\n";
        cout << "=======================================================\n";
        displayDepartments(false);
        return STATE_DEPT_MGMT;
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
        cout << "\n=======================================================\n";
        cout << "         MENU -> Departments -> Search by ID\n";
        cout << "=======================================================\n";
        searchDepartmentsById();
        return STATE_DEPT_SEARCH;
    case 2:
        cout << "\n=======================================================\n";
        cout << "         MENU -> Departments -> Search by Name\n";
        cout << "=======================================================\n";
        searchDepartmentsByName();
        return STATE_DEPT_SEARCH;
    case 3:
        cout << "\n=======================================================\n";
        cout << "         MENU -> Departments -> Search by Branch\n";
        cout << "=======================================================\n";
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
        cout << "\n=======================================================\n";
        cout << "         MENU -> Departments -> Delete by ID\n";
        cout << "=======================================================\n";
        searchDepartmentsById();
        deleteDepartments();
        return STATE_DEPT_DELETE;
    case 2:
        cout << "\n=======================================================\n";
        cout << "         MENU -> Departments -> Delete by Name\n";
        cout << "=======================================================\n";
        searchDepartmentsByName();
        deleteDepartments();
        return STATE_DEPT_DELETE;
    case 3:
        cout << "\n=======================================================\n";
        cout << "         MENU -> Departments -> Delete by Branch\n";
        cout << "=======================================================\n";
        searchDepartmentsByBranch();
        deleteDepartments();
        return STATE_DEPT_DELETE;
    case 4:
        return STATE_DEPT_MGMT;
    }
    return STATE_DEPT_DELETE;
}

MenuState displayEmployeeManagement() {
    int option;

    cout << "\n=======================================================\n";
    cout << "                  MENU -> Employees\n";
    cout << "=======================================================\n";
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
        cout << "\n=======================================================\n";
        cout << "                  MENU -> Employees -> Add\n";
        cout << "=======================================================\n";
        addEmployee();
        clearScreenWithDelay(2);
        return STATE_EMPLOYEE_MGMT;
    case 2:
        cout << "\n=======================================================\n";
        cout << "                  MENU -> Employees -> Edit\n";
        cout << "=======================================================\n";
        editEmployee();
        clearScreenWithDelay(1);
        return STATE_EMPLOYEE_MGMT;
    case 3:
        cout << "\n=======================================================\n";
        cout << "                  MENU -> Employees -> Search\n";
        cout << "=======================================================\n";
        return STATE_EMPLOYEE_SEARCH;
    case 4:
        cout << "\n=======================================================\n";
        cout << "                  MENU -> Employees -> Delete\n";
        cout << "=======================================================\n";
        cout << "Pagaidam neimplementeta: dzest darbinieku\n";
        return STATE_EMPLOYEE_MGMT;
    case 5:
        cout << "\n=======================================================\n";
        cout << "                  MENU -> Employees -> View\n";
        cout << "=======================================================\n";
        displayEmployees(false);
        return STATE_EMPLOYEE_MGMT;
    case 6:

        return STATE_MAIN_MENU;
    }
    return STATE_EMPLOYEE_MGMT;
}

MenuState displayEmployeeSearchMenu() {
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
        cout << "\n=======================================================\n";
        cout << "         MENU -> Employees -> Search by ID\n";
        cout << "=======================================================\n";
        searchEmployeesById();
        return STATE_EMPLOYEE_SEARCH;
    case 2:
        cout << "\n=======================================================\n";
        cout << "         MENU -> Employees -> Search by Name\n";
        cout << "=======================================================\n";
        searchDepartmentsByName();
        return STATE_EMPLOYEE_SEARCH;
    case 3:
        cout << "\n=======================================================\n";
        cout << "         MENU -> Employees -> Search by Access Level\n";
        cout << "=======================================================\n";
        searchDepartmentsByBranch();
        return STATE_EMPLOYEE_SEARCH;
    case 4:
        return STATE_EMPLOYEE_MGMT;
    }
    return STATE_EMPLOYEE_SEARCH;
}

MenuState displayClientManagement() {
    int option;

    cout << "\n=======================================================\n";
    cout << "                  MENU -> Clients\n";
    cout << "=======================================================\n";
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
        cout << "\n=======================================================\n";
        cout << "                  MENU -> Clients -> Add\n";
        cout << "=======================================================\n";
        addClient();
        clearScreenWithDelay(1);
        return STATE_CLIENT_MGMT;
    case 2:
        cout << "\n=======================================================\n";
        cout << "                  MENU -> Clients -> Edit\n";
        cout << "=======================================================\n";
        editClient();
        clearScreenWithDelay(1);
        return STATE_CLIENT_MGMT;
    case 3:
        cout << "\n=======================================================\n";
        cout << "                  MENU -> Clients -> Search\n";
        cout << "=======================================================\n";
        cout << "Pagaidam neimplementeta: meklet klientu\n";
        return STATE_CLIENT_MGMT;
    case 4:
        cout << "\n=======================================================\n";
        cout << "                  MENU -> Clients -> Delete\n";
        cout << "=======================================================\n";
        cout << "Pagaidam neimplementeta: dzest klientu\n";
        return STATE_CLIENT_MGMT;
    case 5:
        cout << "\n=======================================================\n";
        cout << "                  MENU -> Clients -> View\n";
        cout << "=======================================================\n";
        displayClients(false);
        return STATE_CLIENT_MGMT;
    case 6:

        return STATE_MAIN_MENU;
    }
    return STATE_CLIENT_MGMT;
}

MenuState displayAccountManagement() {
    int option;

    cout << "\n=======================================================\n";
    cout << "                  MENU -> Accounts\n";
    cout << "=======================================================\n";
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
        cout << "\n=======================================================\n";
        cout << "                  MENU -> Accounts -> Add\n";
        cout << "=======================================================\n";
        addAccount();
        clearScreenWithDelay(1);
        return STATE_ACCOUNT_MGMT;
    case 2:
        cout << "\n=======================================================\n";
        cout << "                  MENU -> Accounts -> Edit\n";
        cout << "=======================================================\n";
        cout << "Pagaidam neimplementeta: Labot kontu\n";
        return STATE_ACCOUNT_MGMT;
    case 3:
        cout << "\n=======================================================\n";
        cout << "                  MENU -> Accounts -> Search\n";
        cout << "=======================================================\n";
        cout << "Pagaidam neimplementeta: Meklet kontu\n";
        return STATE_ACCOUNT_MGMT;
    case 4:
        cout << "\n=======================================================\n";
        cout << "                  MENU -> Accounts -> Delete\n";
        cout << "=======================================================\n";
        cout << "Pagaidam neimplementeta: dzest kontu\n";
        return STATE_ACCOUNT_MGMT;
    case 5:
        cout << "\n=======================================================\n";
        cout << "                  MENU -> Accounts -> View\n";
        cout << "=======================================================\n";
        displayAccounts(false);
        return STATE_ACCOUNT_MGMT;
    case 6:

        return STATE_MAIN_MENU;
    }
    return STATE_ACCOUNT_MGMT;
}