// #include <iostream>
// #include <limits>
// #include <cstdlib> // Priekš system("clear")
//
// using namespace std;
//
// // ------ STĀVOKĻU ENUMERĀCIJA ------
// enum MenuState {
//     STATE_MAIN_MENU,
//     STATE_BRANCH_MGMT,
//     STATE_DEPT_MGMT,
//     STATE_EMPLOYEE_MGMT, // Pievienots nākotnes paplašināšanai
//     STATE_CLIENT_MGMT,   // Pievienots nākotnes paplašināšanai
//     STATE_ACCOUNT_MGMT,  // Pievienots nākotnes paplašināšanai
//     STATE_PAYMENT_MGMT,  // Pievienots nākotnes paplašināšanai
//     STATE_EXIT
// };
//
// // Funkciju prototipi (tagad atgriež MenuState)
// void inputManager(int& option, int min, int max);
// void runProgram();
//
// MenuState displayMainMenu();
// MenuState displayBranchManagement();
// MenuState displayDepartmentManagement();
//
// int main() {
//     runProgram();
//     return 0;
// }
//
// // ------ Ievades validācija un notīrīšana ------
// void inputManager(int& option, int min, int max){
//     while(!(cin >> option) ||  option < min || option > max) {
//         cout << "Wrong input! Enter number from " << min << " to " << max << ": ";
//         cin.clear();
//         cin.ignore(numeric_limits<streamsize>::max(),'\n');
//     }
// }
//
// // ------ GALVENĀ PROGRAMMAS CILPA ------
// void runProgram() {
//     MenuState currentState = STATE_MAIN_MENU;
//
//     while (currentState != STATE_EXIT) {
//
//         switch (currentState) {
//             case STATE_MAIN_MENU:
//                 currentState = displayMainMenu();
//                 break;
//             case STATE_BRANCH_MGMT:
//                 currentState = displayBranchManagement();
//                 break;
//             case STATE_DEPT_MGMT:
//                 currentState = displayDepartmentManagement();
//                 break;
//             case STATE_EMPLOYEE_MGMT:
//             case STATE_CLIENT_MGMT:
//             case STATE_ACCOUNT_MGMT:
//             case STATE_PAYMENT_MGMT:
//                 // Neimplementētās izvēlnes atgriežas uz sākumu
//                 currentState = STATE_MAIN_MENU;
//                 break;
//             default:
//                 currentState = STATE_EXIT;
//                 break;
//         }
//     }
//
//     cout << "Data being saved. Program being closed.\n";
// }
//
// // ------ MENU DISPLEJA FUNKCIJAS (Atgriež Nākamo Stāvokli) ------
//
// MenuState displayMainMenu() {
//     int option;
//
//     cout << "\n=======================================================\n";
//     cout << "                   MAIN MENU\n";
//     cout << "=======================================================\n";
//     cout << "Choose coresponding number:\n";
//     cout << "1. Branch management\n";
//     cout << "2. Department management\n";
//     cout << "3. Employee management\n";
//     cout << "4. Client management\n";
//     cout << "5. Account management\n";
//     cout << "6. Payment management\n";
//     cout << "7. Save and exit\n";
//     cout << "Your choice: ";
//
//     inputManager(option, 1, 7);
//     system("clear");
//
//     switch (option) {
//         case 1: return STATE_BRANCH_MGMT;
//         case 2:
//             cout << "Pagaidām neimplementēta: Darbinieku pārvaldība. Atgriešanās uz Galveno izvēlni.\n";
//             return STATE_MAIN_MENU;
//         case 3:
//             cout << "Pagaidām neimplementēta: Klientu pārvaldība. Atgriešanās uz Galveno izvēlni.\n";
//             return STATE_MAIN_MENU;
//         case 4:
//             cout << "Pagaidām neimplementēta: Kontu pārvaldība. Atgriešanās uz Galveno izvēlni.\n";
//             return STATE_MAIN_MENU;
//         case 5:
//             cout << "Pagaidām neimplementēta: Maksājumu pārvaldība. Atgriešanās uz Galveno izvēlni.\n";
//             return STATE_MAIN_MENU;
//         case 6: return STATE_EXIT;
//     }
//     return STATE_MAIN_MENU; // Ja nu kas, atgriežas uz sākumu
// }
//
// MenuState displayBranchManagement() {
//     int option;
//
//     cout << "\n=======================================================\n";
//     cout << "                  MENU -> Branches\n";
//     cout << "=======================================================\n";
//     cout << "1. Add\n";
//     cout << "2. Edit\n";
//     cout << "3. Search\n";
//     cout << "4. Delete\n";
//     cout << "5. View\n";
//     cout << "6. Back to Main Menu\n";
//     cout << "Your choice: ";
//
//     inputManager(option, 1, 6);
//     system("clear");
//
//     switch (option) {
//         case 1:
//             cout << "Neimplementeta apskates funkcija\n";
//             return STATE_BRANCH_MGMT; // Paliek pašreizējā stāvoklī
//         case 2:
//             cout << "Pagaidām neimplementēta: Pievienot filiāles\n";
//             return STATE_BRANCH_MGMT;
//         case 3:
//             cout << "Neimplementeta labošanas funkcija\n";
//             return STATE_BRANCH_MGMT;
//         case 4:
//             cout << "Neimplementeta dzēšanas funkcija\n";
//             return STATE_BRANCH_MGMT;
//         case 5:
//             cout << "Neimplementeta statistikas funkcija\n";
//             return STATE_BRANCH_MGMT;
//         case 6:
//             cout << "Atgriešanās uz Galveno izvēlni.\n";
//             return STATE_MAIN_MENU; // Iet uz sākumu
//     }
//     return STATE_BRANCH_MGMT;
// }
//
// MenuState displayDepartmentManagement() {
//     int option;
//
//     cout << "\n=======================================================\n";
//     cout << "                  MENU -> Department\n";
//     cout << "=======================================================\n";
//     cout << "1. Add\n";
//     cout << "2. Edit\n";
//     cout << "3. Search\n";
//     cout << "4. Delete\n";
//     cout << "5. View\n";
//     cout << "6. Back to Main Menu\n";
//     cout << "Your choice: ";
//
//     inputManager(option, 1, 6);
//     system("clear");
//
//     switch (option) {
//         case 1:
//             cout << "Pagaidām neimplementēta: Apskatīt visas nodaļas (ar filiāles nosaukumu nevis ID)\n";
//             return STATE_DEPT_MGMT;
//         case 2:
//             cout << "Pagaidām neimplementēta: Apskatīt nodaļas pa filiālēm\n";
//             return STATE_DEPT_MGMT;
//         case 3:
//             cout << "Pagaidām neimplementēta: Pievienot Nodaļu\n";
//             return STATE_DEPT_MGMT;
//         case 4:
//             cout << "Pagaidām neimplementēta: Labot datus\n";
//             return STATE_DEPT_MGMT;
//         case 5:
//             cout << "Pagaidām neimplementēta: Dzēst datus\n";
//             return STATE_DEPT_MGMT;
//         case 6:
//             cout << "Atgriešanās uz Galveno izvēlni.\n";
//             return STATE_MAIN_MENU; // Iet uz sākumu
//     }
//     return STATE_DEPT_MGMT;
// }