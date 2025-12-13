#include "DataTypes.h"
#include "Menu.h"
#include "Functions.h"
#include <iostream>
#include <limits>
#include <cstdlib>

#ifdef _WIN32
#define NOMINMAX
#include<windows.h>//for sleep()
#endif



void inputManager(int& option, int min, int max) {
    while (!(cin >> option) || option < min || option > max) {
        cout << "Wrong input! Enter number from " << min << " to " << max << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void clearScreenWithDelay(int sec) {
    int miliseconds = sec * 1000;
    Sleep(miliseconds);
    system("cls");
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
        case STATE_DEPT_MGMT:
            currentState = displayDepartmentManagement();
            break;
        case STATE_EMPLOYEE_MGMT:
        case STATE_CLIENT_MGMT:
        case STATE_ACCOUNT_MGMT:
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
    system("cls");

    switch (option) {
    case 1: return STATE_BRANCH_MGMT;
    case 2: return STATE_DEPT_MGMT;
    case 3:
        cout << "Pagaidam neimplementeta: Klientu parvaldiba. Atgriesanas uz Galveno izvelni.\n";
        return STATE_MAIN_MENU;
    case 4:
        cout << "Pagaidam neimplementeta: Kontu parvaldiba. Atgriesanas uz Galveno izvelni.\n";
        return STATE_MAIN_MENU;
    case 5:
        cout << "Pagaidam neimplementeta: Maksajumu parvaldiba. Atgriesanas uz Galveno izvelni.\n";
        return STATE_MAIN_MENU;
    case 6: return STATE_EXIT;
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
    system("cls");

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
        searchBranches();
        return STATE_BRANCH_MGMT;
    case 4:
        cout << "\n=======================================================\n";
        cout << "                  MENU -> Branches -> Delete\n";
        cout << "=======================================================\n";
        cout << "Neimplementeta dzesanas funkcija\n";
        return STATE_BRANCH_MGMT;
    case 5:
        cout << "\n=======================================================\n";
        cout << "                  MENU -> Branches -> View\n";
        cout << "=======================================================\n";
        displayBranches();
        return STATE_BRANCH_MGMT;
    case 6:
        return STATE_MAIN_MENU;
    }
    return STATE_BRANCH_MGMT;
}

MenuState displayDepartmentManagement() {
    int option;

    cout << "\n=======================================================\n";
    cout << "                  MENU -> Department\n";
    cout << "=======================================================\n";
    cout << "1. Add\n";
    cout << "2. Edit\n";
    cout << "3. Search\n";
    cout << "4. Delete\n";
    cout << "5. View\n";
    cout << "6. Back to Main Menu\n";
    cout << "Your choice: ";

    inputManager(option, 1, 6);
    system("cls");

    switch (option) {
    case 1:
        cout << "Pagaidam neimplementeta: Apskatit visas nodalas (ar filiales nosaukumu nevis ID)\n";
        return STATE_DEPT_MGMT;
    case 2:
        cout << "Pagaidam neimplementeta: Apskatit nodalas pa filialem\n";
        return STATE_DEPT_MGMT;
    case 3:
        cout << "Pagaidam neimplementeta: Pievienot Nodalu\n";
        return STATE_DEPT_MGMT;
    case 4:
        cout << "Pagaidam neimplementeta: Labot datus\n";
        return STATE_DEPT_MGMT;
    case 5:
        cout << "Pagaidam neimplementeta: Dzest datus\n";
        return STATE_DEPT_MGMT;
    case 6:

        return STATE_MAIN_MENU;
    }
    return STATE_DEPT_MGMT;
}