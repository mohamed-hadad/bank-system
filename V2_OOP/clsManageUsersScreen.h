#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsValidateInput.h"
#include "clsListUsersScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"
#include <iomanip>

using namespace std;

class clsManageUsersScreen : protected clsScreen
{

private:
    enum enManageUsersMenuOptions {
        eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3,
        eUpdateUser = 4, eFindUser = 5, eMainMenu = 6
    };

    static enManageUsersMenuOptions ReadManageUsersMenuOption()
    {
        cout << setw(37) << left << "" << "Choose a Choice Between [1, 6] : ";
        short Choice = clsValidateInput::ReadNumBetween(1, 6);
        return static_cast <enManageUsersMenuOptions> (Choice);
    }

    static void _GoBackToManageUsersMenu()
    {
        cout << "\n\nPress any key to go back to Manage Users Menu...";
        Pause();
    }
    static void _PerformManageUsersMenuOption(enManageUsersMenuOptions ManageUsersMenuOption)
    {

        system("cls");
        switch (ManageUsersMenuOption)
        {
        case enManageUsersMenuOptions::eListUsers:
            clsListUsersScreen::ShowUsersList();
            _GoBackToManageUsersMenu();
            break;

        case enManageUsersMenuOptions::eAddNewUser:
            clsAddNewUserScreen::ShowAddNewUserScreen();
            _GoBackToManageUsersMenu();
            break;

        case enManageUsersMenuOptions::eDeleteUser:
            clsDeleteUserScreen::ShowDeleteUserScreen();
            _GoBackToManageUsersMenu();
            break;

        case enManageUsersMenuOptions::eUpdateUser:
            clsUpdateUserScreen::ShowUpdateUserScreen();
            _GoBackToManageUsersMenu();
            break;

        case enManageUsersMenuOptions::eFindUser:
            clsFindUserScreen::ShowFindUserScreen();
            _GoBackToManageUsersMenu();
            break;

        case enManageUsersMenuOptions::eMainMenu:
            break;
        }

    }



public:


    static void ShowManageUsersMenu()
    {
        enManageUsersMenuOptions Option;
        do {
            system("cls");
            _DrawScreenHeader("\t  Manage Users Screen");
            cout << setw(37) << left << "" << "===========================================\n";
            cout << setw(37) << left << "" << "\t\t  Manage Users Menu\n";
            cout << setw(37) << left << "" << "===========================================\n";
            cout << setw(37) << left << "" << "\t[1] List Users\n";
            cout << setw(37) << left << "" << "\t[2] Add New User\n";
            cout << setw(37) << left << "" << "\t[3] Delete User\n";
            cout << setw(37) << left << "" << "\t[4] Update User\n";
            cout << setw(37) << left << "" << "\t[5] Find User\n";
            cout << setw(37) << left << "" << "\t[6] Main Menu\n";
            cout << setw(37) << left << "" << "===========================================\n";

            Option = ReadManageUsersMenuOption();
            _PerformManageUsersMenuOption(Option);
        } while (Option != enManageUsersMenuOptions::eMainMenu);

    }


};