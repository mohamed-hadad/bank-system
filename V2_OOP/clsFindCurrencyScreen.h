#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsValidateInput.h"

class clsFindCurrencyScreen :protected clsScreen
{

private:
    static void _PrintCurrency(clsCurrency Currency)
    {
        cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.Country();
        cout << "\nName       : " << Currency.CurrencyName();
        cout << "\nCode       : " << Currency.CurrencyCode();
        cout << "\nRate(1$) = : " << Currency.Rate();
        cout << "\n_____________________________\n";

    }

    static void _ShowResults(clsCurrency Currency)
    {
        if (!Currency.IsEmpty())
        {
            cout << "\nCurrency Found :-)\n";
            _PrintCurrency(Currency);
        }
        else
        {
            cout << "\nCurrency Was not Found :-(\n";
        }
    }

public:

    static void ShowFindCurrencyScreen()
    {

        _DrawScreenHeader("\t  Find Currency Screen");

        cout << "\nFind By: [1] Code or [2] Country ? ";

        short Answer = clsValidateInput::ReadNumBetween(1, 2);

        if (Answer == 1)
        {
            string CurrencyCode;
            cout << "\nPlease Enter Currency Code: ";
            CurrencyCode = clsValidateInput::ReadString();
            clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
            _ShowResults(Currency);
        }
        else if (Answer == 2)
        {
            string Country;
            cout << "\nPlease Enter Country Name: ";
            Country = clsValidateInput::ReadString();
            clsCurrency Currency = clsCurrency::FindByCountry(Country);
            _ShowResults(Currency);
        }






    }

};

