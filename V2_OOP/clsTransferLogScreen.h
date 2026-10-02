#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include "clsScreen.h"
#include "clsUser.h"
using namespace std;

class clsTransferLogScreen : protected clsScreen
{
    static void _PrintTransferLogRecordLine(clsBankClient::stTransferLog TransferRecord)
    {

        cout << "\t| " << setw(25) << left << TransferRecord._DateAndTime;
        cout << "| " << setw(15) << left << TransferRecord._SenderAccNum;
        cout << "| " << setw(15) << left << TransferRecord._ReceiverAccNum;
        cout << "| " << setw(15) << left << TransferRecord._Amount;
        cout << "| " << setw(15) << left << TransferRecord._Username;

    }
public:
    static void ShowTransferLogScreen() {
        vector <clsBankClient::stTransferLog> vTransferLog = clsBankClient::GetTransferLogList(TransferLogFileName);
        string Title = "\tTransfer Log Screen";
        string SubTitle = "\t    (" + to_string(vTransferLog.size()) + ") Record(s).";
        _DrawScreenHeader(Title, SubTitle);
        cout << setw(8) << left << "" << "\n\t____________________________________________________________________________________________\n\n";
        cout << "\t| " << setw(25) << left << "Date - Time";
        cout << "| " << setw(15) << left << "Sender";
        cout << "| " << setw(15) << left << "Receiver";
        cout << "| " << setw(15) << left << "Amount";
        cout << "| " << setw(15) << left << "Username";
        cout << setw(8) << left << "" << "\n\t____________________________________________________________________________________________\n\n";
        if (vTransferLog.size() == 0)
            cout << "\t\t\t\t\tNo Transfers Available In The System!";
        else
            for (const clsBankClient::stTransferLog& TransferLog : vTransferLog)
            {
                _PrintTransferLogRecordLine(TransferLog);
                cout << endl;
            }
        cout << setw(8) << left << "" << "\n\t____________________________________________________________________________________________\n\n";
    }
};


