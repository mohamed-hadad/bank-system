#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsValidateInput.h"

class clsFindClientScreen : protected clsScreen
{

public:

    static void ShowFindClientScreen()
    {

        _DrawScreenHeader("\tFind Client Screen");

        cout << "\nPlease Enter Account Number: ";
        string AccountNumber = clsValidateInput::ReadString();
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsValidateInput::ReadString();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);

        if (!Client1.IsEmpty())
        {
            cout << "\nClient Found :-)\n";
            _PrintClient(Client1);
        }
        else
        {
            cout << "\nClient Was not Found :-(\n";
        }


    }

};

