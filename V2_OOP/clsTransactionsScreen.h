#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsValidateInput.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"
#include <iomanip>

using namespace std;

class clsTransactionsScreen : protected clsScreen
{


private:
    enum enTransactionsMenuOptions {
        eDeposit = 1, eWithdraw,
        eShowTotalBalance, eTransfer, eTransferLog, eShowMainMenu
    };

    static enTransactionsMenuOptions ReadTransactionsMenueOption()
    {
        cout << setw(37) << left << "" << "Choose a Choice Between [1, 6] : ";
        short Choice = clsValidateInput::ReadNumBetween(1, 6);
        return static_cast <enTransactionsMenuOptions> (Choice);
    }

    static void _GoBackToTransactionsMenu()
    {
        cout << "\n\nPress Any Key To Go Back To Transactions Menu...";
        Pause();
    }

    static void _PerformTransactionsMenueOption(enTransactionsMenuOptions TransactionsMenuOption)
    {
        system("cls");
        switch (TransactionsMenuOption)
        {
            case enTransactionsMenuOptions::eDeposit:
                clsDepositScreen::ShowDepositScreen();
                _GoBackToTransactionsMenu();
                break;

            case enTransactionsMenuOptions::eWithdraw:
                clsWithdrawScreen::ShowWithdrawScreen();
                _GoBackToTransactionsMenu();
                break;

            case enTransactionsMenuOptions::eShowTotalBalance:
                clsTotalBalancesScreen::ShowTotalBalances();
                _GoBackToTransactionsMenu();
                break;

            case enTransactionsMenuOptions::eTransfer:
                clsTransferScreen::ShowTransferScreen();
                _GoBackToTransactionsMenu();
                break;

            case enTransactionsMenuOptions::eTransferLog:
                clsTransferLogScreen::ShowTransferLogScreen();
                _GoBackToTransactionsMenu();
                break;

            case enTransactionsMenuOptions::eShowMainMenu:
                break;
        }


    }



public:


    static void ShowTransactionsMenu()
    {
        enTransactionsMenuOptions Option;
        do {
            system("cls");
            _DrawScreenHeader("\t  Transactions Screen");
            cout << setw(37) << left << "" << "===========================================\n";
            cout << setw(37) << left << "" << "\t\t  Transactions Menue\n";
            cout << setw(37) << left << "" << "===========================================\n";
            cout << setw(37) << left << "" << "\t[1] Deposit\n";
            cout << setw(37) << left << "" << "\t[2] Withdraw\n";
            cout << setw(37) << left << "" << "\t[3] Total Balances\n";
            cout << setw(37) << left << "" << "\t[4] Transfer\n";
            cout << setw(37) << left << "" << "\t[5] Transfer Log\n";
            cout << setw(37) << left << "" << "\t[6] Main Menu\n";
            cout << setw(37) << left << "" << "===========================================\n";

            Option = ReadTransactionsMenueOption();
            _PerformTransactionsMenueOption(Option);

        } while (Option != enTransactionsMenuOptions::eShowMainMenu);
    }
};

