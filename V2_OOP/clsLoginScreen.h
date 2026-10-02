#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsMainScreen.h"
#include "Global.h"

class clsLoginScreen :protected clsScreen
{

private:

    static void _Login()
    {
        do {
            bool LoginFaild = false;
            short loginCounter = 3;
            string Username, Password;
            do
            {
                loginCounter ;
                system("cls");
                _DrawScreenHeader("\t    Login Screen", "", false);
                if (LoginFaild)
                {
                    if (--loginCounter == 0) {
                        system("cls");
                        cout << "\n\n\t\t\t\t\t    You are Locked after 3 failed trails,";
                        cout << "\n\n\t\t\t\t\t    You can Try Login Later.\n";
                        Pause();
                        return;
                    }
                    cout << "\n\n\t\t\t\t\t    Invlaid Username/Password!";
                    cout << "\n\t\t\t\t\t    You Have " << loginCounter << " Trials to login.";            
                }
                    
                cout << "\n\n\t\t\t\t\t    Enter Username: ";
                Username = clsValidateInput::ReadString();

                cout << "\t\t\t\t\t    Enter Password: ";
                Password = clsValidateInput::ReadString();

                CurrentUser = clsUser::Find(Username, Password);

                LoginFaild = CurrentUser.IsEmpty();

            } while (LoginFaild);

            CurrentUser.RegisterLogin();
        } while (clsMainScreen::ShowMainMenu());
    }

public:


    static void ShowLoginScreen()
    {
        _Login();

    }

};

