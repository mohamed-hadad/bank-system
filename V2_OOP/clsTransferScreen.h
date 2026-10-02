#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsValidateInput.h"

using namespace std;

class clsTransferScreen : clsScreen
{
	


public:
	static void ShowTransferScreen()
	{
		_DrawScreenHeader("\t   Transfer Screen");
		string AccNum = "";

		cout << "\n\nPlease Enter Your Account Number You Want Transfer From : ";
		AccNum = clsValidateInput::ReadString();
		while (!clsBankClient::IsClientExist(AccNum))
		{
			cout << "\nAccount Number Doesn't Exist, Please Enter Another one : ";
			AccNum = clsValidateInput::ReadString();
		}

		clsBankClient Client1 = clsBankClient::Find(AccNum);
		cout << "\nYour Account Balance is " << Client1.AccountBalance << '\n';
		if (Client1.AccountBalance == 0)
		{
			cout << "\nSorry! There is NO Balance in Your Account.\n";
			return;
		}
		
		cout << "\n\nPlease Enter Account Number You Want Transfer To : ";
		AccNum = clsValidateInput::ReadString();
		while (!clsBankClient::IsClientExist(AccNum))
		{
			cout << "\nAccount Number Doesn't Exist, Please Enter Another one : ";
			AccNum = clsValidateInput::ReadString();
		}

		clsBankClient Client2 = clsBankClient::Find(AccNum);

		cout << "\nHow Much Money You Want Transfer To " << Client2.AccountNumber << " ? ";
		double Amount = clsValidateInput::ReadWithdraw(Client1);
		if (Amount == 0)
			return;

		cout << "\nAre You Sure Do You Want To Complete This Procedure [Y/N] ? "; 
		char Answer; cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
		{
			if (Client1.Transfer(Amount, Client2))
			{
				cout << "\nDone Succesfully.";
				cout << "\nNow You Account Balance is " << Client1.AccountBalance << '\n';
			}
			else
			{
				cout << "\nTransfer Failed.";
			}
		}
		else
		{
			cout << "\n\nProcedure Cancelled.";
		}
		cin.ignore();
	}
};

