#pragma once
#include <iostream>
#include "Global.h"
#include "clsBankClient.h"
#include "clsDate.h"
#include "clsUser.h"
using namespace std;

class clsScreen
{
protected:
    static void _PrintClient(const clsBankClient& Client)
    {
        cout << "\nClient Card:";
        cout << "\n__________________________________";
        cout << "\nFirstName      : " << Client.FirstName;
        cout << "\nLastName       : " << Client.LastName;
        cout << "\nFullName       : " << Client.FullName;
        cout << "\nEmail          : " << Client.Email;
        cout << "\nPhoneNumber    : " << Client.PhoneNumber;
        cout << "\nAccountNumber  : " << Client.AccountNumber;
        cout << "\nBalance        : " << Client.AccountBalance;
        cout << "\n__________________________________\n";

    }
    static void _PrintUser(const clsUser& User)
    {
        cout << "\nUser Card:";
        cout << "\n__________________________________";
        cout << "\nFirstName   : " << User.FirstName;
        cout << "\nLastName    : " << User.LastName;
        cout << "\nFull Name   : " << User.FullName;
        cout << "\nEmail       : " << User.Email;
        cout << "\nPhoneNumber : " << User.PhoneNumber;
        cout << "\nUsername    : " << User.Username;
        cout << "\nPermissions : " << User.Permissions;
        cout << "\n__________________________________\n";

    }
    static void _DrawScreenHeader(string Title, string SubTitle = "", bool ShowUsernameAndDate = true)
    {
        system("cls");
        cout << "\t\t\t\t\t    -----------------------------";
        cout << "\n\t\t\t\t\t  " << Title;
        if(SubTitle != "")
            cout << "\n\t\t\t\t\t  " << SubTitle;
        cout << "\n\t\t\t\t\t    -----------------------------";
        if (ShowUsernameAndDate) {
            cout << "\n\t\t\t\t\t     User: " << CurrentUser.Username;
            clsDate Date = clsDate();
            cout << "\n\t\t\t\t\t     Date: " << Date.FormatDate() << "\n\n";
        }

    }

public:
    static void Pause() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
};

