#pragma once
#include <iostream>
#include <string>
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>
using namespace std;

class clsClientListScreen :protected clsScreen
{

private:
    static void PrintClientRecordLine(clsBankClient Client)
    {

        cout << setw(11) << left << "" << "| " << setw(15) << left << Client.AccountNumber;
        cout << "| " << setw(20) << left << Client.FullName;
        cout << "| " << setw(12) << left << Client.PhoneNumber;
        cout << "| " << setw(20) << left << Client.Email;
        cout << "| " << setw(10) << left << Client.PinCode;
        cout << "| " << setw(12) << left << Client.AccountBalance;

    }

public:


    static void ShowClientsList()
    {


        vector <clsBankClient> vClients = clsBankClient::GetClientsList();
        string Title = "\t  Client List Screen";
        string SubTitle = "\t    (" + to_string(vClients.size()) + ") Client(s).";

        _DrawScreenHeader(Title, SubTitle);


        cout << "\n\t   ________________________________________________________________________________________________\n\n";

        cout << setw(11) << left << "" << "| " << setw(15) << left << "Account Number";
        cout << "| " << left << setw(20) << "Client Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Pin Code" << "| " << left << setw(12) << "Balance";
        cout << "\n\t   ________________________________________________________________________________________________\n\n";

        if (vClients.size() == 0)
            cout << "\t\t\t\t\tNo Clients Available In the System!\n";
        else

            for (clsBankClient Client : vClients)
            {
                PrintClientRecordLine(Client);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t   ________________________________________________________________________________________________\n\n";

    }

};
