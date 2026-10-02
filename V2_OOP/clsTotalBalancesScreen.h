#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>
#include "clsUtility.h"

class clsTotalBalancesScreen : protected clsScreen
{

private:

    static void PrintClientRecordBalanceLine(clsBankClient Client)
    {
        cout << "\t\t| "     << setw(15) << left << Client.AccountNumber;
        cout << "| "         << setw(40) << left << Client.FullName;
        cout << "| "         << setw(12) << left << Client.AccountBalance;
    }

public:

    static void ShowTotalBalances()
    {

        vector <clsBankClient> vClients = clsBankClient::GetClientsList();

        string Title = "\t  Balances List Screen";
        string SubTitle = "\t     (" + to_string(vClients.size()) + ") Client(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << "\n\t\t_________________________________________________________________________________\n\n";
        cout << "\t\t| "     << setw(15) << left << "Accout Number";
        cout << "| "         << setw(40) << left << "Client Name";
        cout << "| "         << setw(12) << left << "Balance";
        cout << "\n\t\t_________________________________________________________________________________\n\n";

        double TotalBalances = clsBankClient::GetTotalBalances();

        if (vClients.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else

            for (clsBankClient Client : vClients)
            {
                PrintClientRecordBalanceLine(Client);
                cout << endl;
            }

        cout << "\n\t\t_________________________________________________________________________________\n\n";

        cout << setw(8) << left << "" << "\t\t\t\t\tTotal Balances = " << TotalBalances << endl;
        cout << setw(8) << left << "" << "\t\t\t\t\t( " << clsUtility::NumberToText(TotalBalances) << ")";
    }

};

