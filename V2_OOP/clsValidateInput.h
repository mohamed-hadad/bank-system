#pragma once
#include <iostream>
#include <string>
#include <limits>
#include "clsBankClient.h"
using namespace std;
class clsValidateInput
{


public:

	static void FlushInput() {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

static bool IsNumber(const string& s) {
    if (s.empty()) return false;

    size_t start = (s[0] == '-') ? 1 : 0;
    bool dotSeen = false;
    int digitCount = 0;

    if (start == s.length()) return false;

    for (; start < s.length(); start++) {
        if (s[start] == '.') {
            if (dotSeen) return false;
            dotSeen = true;
        }
        else if (s[start] >= '0' && s[start] <= '9') {
            digitCount++;
            if (digitCount > 15) return false;
        }
        else {
            return false;
        }
    }
    return true;
}

	template <typename T>
	static bool IsNumBetween(T Num, T From, T To) {
		return (Num >= From && Num <= To);
	}

	//Read Methods
	template <typename T>
	static T ReadNum(string ErrorMessage = "Invaild Number, Please Enter another Number: ") {
		string Num = ReadString();
		while (!IsNumber(Num)) {
			FlushInput();
			cout << ErrorMessage;
			Num = ReadString();
		}
		return static_cast <T> (stod(Num));
	}

	template <typename T>
	static T ReadNumBetween(T From, T To, string ErrorMessage = "Invaild Number, Please Enter Another Number Between") {
		T Num = ReadNum<T>();
		while (!IsNumBetween(Num, From, To)) {
			FlushInput();
			cout << ErrorMessage << " [" << From << " to " << To << "] : ";
			Num = ReadNum<T>();
		}
		return Num;
	}


	static string ReadString()
	{
		string  S1 = "";
		getline(cin >> ws, S1);
		return S1;
	}

	// Validate Client Transactions >> Deposit & Withdraw
	static double ReadDeposit() {
		cout << "\nPlease Enter Deposit Amount: ";
		double DepositAmount = ReadNum<double>();
		while (DepositAmount <= 0) {
			cout << "\nInvalid Amount! Please Enter a Positive Value: ";
			DepositAmount = ReadNum<double>();
		}
		return DepositAmount;
	}
	static double ReadWithdraw(const clsBankClient& Client) {

		double WithdrawAmount = ReadNum<double>();
		while (WithdrawAmount <= 0 || WithdrawAmount > Client.AccountBalance) {
			if (Client.AccountBalance == 0) {
				cout << "\nSorry! There is NO Balance in Your Account.\n";
				return 0;
			}
			else if (WithdrawAmount > Client.AccountBalance) {
				cout << "\nAmount Exceeds The Balance, You Can Withdraw Up To: " << Client.AccountBalance;
				cout << "\nPlease Enter Another Withdraw Amount: ";
				WithdrawAmount = ReadNum<double>();
			}
			else {
				cout << "\nInvalid Amount! Please Enter a Positive Value: ";
				WithdrawAmount = ReadNum<double>();
			}
		}
		return WithdrawAmount;
	}

};
