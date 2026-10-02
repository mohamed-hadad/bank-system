#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsClientListScreen.h"
#include "clsValidateInput.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "clsLoginRegisterScreen.h"
#include "clsCurrencyExchangeMainScreen.h"
#include "Global.h"
#include "clsUser.h"
#include <iomanip>



using namespace std;

class clsMainScreen : protected clsScreen
{


private:
    enum enMainMenuOptions {
        eListClients = 1, eAddNewClient, eDeleteClient,
        eUpdateClient, eFindClient, eShowTransactionsMenu,
        eManageUsers,  eLoginRegisterScreen, eCurrencyExchange, eLogout, eExit
    };
    
    static enMainMenuOptions _ReadMainMenuOption()
    {
        cout << setw(37) << left << "" << "Choose a Choice Between [1, 11]: ";
        short Choice = clsValidateInput::ReadNumBetween(1, 11);
        return static_cast <enMainMenuOptions> (Choice);
    }
    static  void _GoBackToMainMenu()
    {
        cout << setw(37) << left << "" << "\nPress any key to go back to Main Menu...\n";
        Pause();
    }
    static void _Logout()
    {
        CurrentUser = clsUser::Find("", "");
    }
    static bool CheckUserPermissions(const enMainMenuOptions& Option) {
        
        if (CurrentUser.Permissions == clsUser::enUserPermissions::eAll)
            return true;

        switch (Option) {
        case enMainMenuOptions::eListClients:          return (CurrentUser.Permissions & clsUser::enUserPermissions::pListClients);
        case enMainMenuOptions::eAddNewClient:         return (CurrentUser.Permissions & clsUser::enUserPermissions::pAddNewClient);
        case enMainMenuOptions::eDeleteClient:         return (CurrentUser.Permissions & clsUser::enUserPermissions::pDeleteClient);
        case enMainMenuOptions::eUpdateClient:         return (CurrentUser.Permissions & clsUser::enUserPermissions::pUpdateClient);
        case enMainMenuOptions::eFindClient:           return (CurrentUser.Permissions & clsUser::enUserPermissions::pFindClient);
        case enMainMenuOptions::eShowTransactionsMenu: return (CurrentUser.Permissions & clsUser::enUserPermissions::pTransactions);
        case enMainMenuOptions::eManageUsers:          return (CurrentUser.Permissions & clsUser::enUserPermissions::pManageUsers);
        case enMainMenuOptions::eLoginRegisterScreen:  return (CurrentUser.Permissions & clsUser::enUserPermissions::pLoginRegister);
        case enMainMenuOptions::eCurrencyExchange:     return true;
        case enMainMenuOptions::eLogout:               return true;
        case enMainMenuOptions::eExit:                 return true;
        default:                                       return false;
        }
    }
    static void _PerfromMainMenuOption(enMainMenuOptions MainMenuOption)
    {
        system("cls");
        if (!CheckUserPermissions(MainMenuOption)) {
            _DrawScreenHeader("    Access Denied,", "    Please Contact Your Admin.");
            _GoBackToMainMenu();
            return;
        }
        switch (MainMenuOption)
        {
        case enMainMenuOptions::eListClients:
        {
            clsClientListScreen::ShowClientsList();
            _GoBackToMainMenu();
            break;
        }
        case enMainMenuOptions::eAddNewClient:
            clsAddNewClientScreen::ShowAddNewClientScreen();
            _GoBackToMainMenu();
            break;

        case enMainMenuOptions::eDeleteClient:
            clsDeleteClientScreen::ShowDeleteClientScreen();
            _GoBackToMainMenu();
            break;

        case enMainMenuOptions::eUpdateClient:
            clsUpdateClientScreen::ShowUpdateClientScreen();
            _GoBackToMainMenu();
            break;

        case enMainMenuOptions::eFindClient:
            clsFindClientScreen::ShowFindClientScreen();
            _GoBackToMainMenu();
            break;

        case enMainMenuOptions::eShowTransactionsMenu:
            clsTransactionsScreen::ShowTransactionsMenu();
            break;

        case enMainMenuOptions::eManageUsers:
            clsManageUsersScreen::ShowManageUsersMenu();
            break;

        case enMainMenuOptions::eLoginRegisterScreen:
            clsLoginRegisterScreen::ShowLoginRegisterScreen();
            _GoBackToMainMenu();
            break;

        case enMainMenuOptions::eCurrencyExchange:
            clsCurrencyExchangeMainScreen::ShowCurrenciesMenu();
            break;

        case enMainMenuOptions::eLogout:
            _Logout();
            break;

        case enMainMenuOptions::eExit:
            break;
        }
    }

public:


    static bool ShowMainMenu()
    {
        enMainMenuOptions Option;
        do {
            system("cls");
            _DrawScreenHeader("\tM a i n   S c r e e n");
            cout << setw(37) << left << "" << "===========================================\n";
            cout << setw(37) << left << "" << "\t\t      Main Menu\n";
            cout << setw(37) << left << "" << "===========================================\n";
            cout << setw(37) << left << "" << "\t[01] Show Client List\n";
            cout << setw(37) << left << "" << "\t[02] Add New Client\n";
            cout << setw(37) << left << "" << "\t[03] Delete Client\n";
            cout << setw(37) << left << "" << "\t[04] Update Client Info\n";
            cout << setw(37) << left << "" << "\t[05] Find Client\n";
            cout << setw(37) << left << "" << "\t[06] Transactions\n";
            cout << setw(37) << left << "" << "\t[07] Manage Users\n";
            cout << setw(37) << left << "" << "\t[08] Login Regiser\n";
            cout << setw(37) << left << "" << "\t[09] Currency Exchange\n";
            cout << setw(37) << left << "" << "\t[10] Logout\n";
            cout << setw(37) << left << "" << "\t[11] Exit\n";
            cout << setw(37) << left << "" << "===========================================\n";

            Option = _ReadMainMenuOption();
            if (Option == enMainMenuOptions::eExit) {
                system("cls");
                return false;
            }
            _PerfromMainMenuOption(Option);
        } while (Option != enMainMenuOptions::eLogout);
        return true;
    }

};

