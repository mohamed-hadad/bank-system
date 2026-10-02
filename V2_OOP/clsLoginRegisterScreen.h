#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include "clsScreen.h"
#include "clsUser.h"
using namespace std;

class clsLoginRegisterScreen : protected clsScreen
{

    static void _PrintUserLoginRecordLine(clsUser::stLoginRegisterRecord LoginInfo)
    {

        cout << "\t\t| " << setw(20) << left  << LoginInfo._LoginDateAndTime;
        cout << "\t\t| " << setw(10) << left << LoginInfo._Username;
        cout << "\t\t| " << setw(5) << left << LoginInfo._Permissions;

    }
public:
    static void ShowLoginRegisterScreen() {
        vector <clsUser::stLoginRegisterRecord> vLoginRegister = clsUser::GetLoginRegisterList(LoginRegisterFileName);
        string Title = "\tLogin Register Screen";
        string SubTitle = "\t    (" + to_string(vLoginRegister.size()) + ") Record(s).";
        _DrawScreenHeader(Title, SubTitle);
        cout << setw(8) << left << "" << "\n\t\t_______________________________________________________________________________\n\n";
        cout << "\t\t| " << setw(20) << left << "Login Date And Time";
        cout << "\t\t| " << setw(10) << left << "Username";
        cout << "\t\t| " << setw(5) << left << "Permissions";
        cout << setw(8) << left << "" << "\n\t\t_______________________________________________________________________________\n\n";
        if (vLoginRegister.size() == 0)
            cout << "\t\t\t\t\tNo Logins Available In The System!";
        else
            for (const clsUser::stLoginRegisterRecord& UserLog : vLoginRegister)
            {
                _PrintUserLoginRecordLine(UserLog);
                cout << endl;
            }
        cout << setw(8) << left << "" << "\n\t\t_______________________________________________________________________________\n\n";
	}
};

