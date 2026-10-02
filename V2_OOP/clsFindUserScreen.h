#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "clsValidateInput.h"

class clsFindUserScreen : protected clsScreen
{

public:

    static void ShowFindUserScreen()
    {

        _DrawScreenHeader("\t    Find User Screen");

        string UserName;
        cout << "\nPlease Enter Username: ";
        UserName = clsValidateInput::ReadString();
        while (!clsUser::IsUserExist(UserName))
        {
            cout << "\nUser is not found, choose another one: ";
            UserName = clsValidateInput::ReadString();
        }

        clsUser User = clsUser::Find(UserName);

        if (!User.IsEmpty())
        {
            cout << "\nUser Found :-)\n";
        }
        else
        {
            cout << "\nUser Was not Found :-(\n";
        }

        _PrintUser(User);

    }

};

