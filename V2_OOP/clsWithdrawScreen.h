#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsValidateInput.h"

class clsWithdrawScreen : protected clsScreen
{
private:

    static string _ReadAccountNumber()
    {
        string AccountNumber = "";
        cout << "\n\t\t\t\tPlease Enter Account Number: ";
        getline(cin >> ws, AccountNumber);
        return AccountNumber;
    }

public:

    static void ShowWithdrawScreen()
    {
        _DrawScreenHeader("\t   Withdraw Screen");

        string AccountNumber = _ReadAccountNumber();


        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
            AccountNumber = _ReadAccountNumber();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        cout << "\nPlease Enter Withdraw Amount: ";
        double Amount = clsValidateInput::ReadWithdraw(Client);
        if (Amount == 0) {
            return;
        }

        cout << "\nAre You Sure You Want To Perform This Transaction [Y/N] ? ";
        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            if (Client.Withdraw(Amount))
            {
                cout << "\nAmount Withdrew Successfully.\n";
                cout << "\nNew Balance is: " << Client.AccountBalance;
            }              
            else           
            {              
                cout << "\nCannot Withdraw, Insuffecient Balance!\n";
                cout << "\nAmout To Withdraw is: " << Amount;
                cout << "\nYour Balance is: " << Client.AccountBalance;
            }
        }
        else
        {
            cout << "\nOperation Was Cancelled.\n";
        }
        cin.ignore();
    }
};

