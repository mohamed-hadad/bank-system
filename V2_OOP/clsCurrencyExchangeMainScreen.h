#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"
#include "clsValidateInput.h"
#include <iomanip>

using namespace std;

class clsCurrencyExchangeMainScreen : protected clsScreen
{

private:
    enum enCurrenciesMainMenuOptions {
        eListCurrencies = 1, eFindCurrency, eUpdateCurrencyRate,
        eCurrencyCalculator, eMainMenu
    };

    static enCurrenciesMainMenuOptions ReadCurrenciesMainMenueOptions()
    {
        cout << setw(37) << left << "" << "Choose a Choice Between [1, 5] : ";
        short Choice = clsValidateInput::ReadNumBetween(1, 5);
        return static_cast <enCurrenciesMainMenuOptions> (Choice);
    }

    static void _GoBackToCurrenciesMenu()
    {
        cout << "\n\nPress any key to go back to Currencies Menu...";
        Pause();
    }

    static void _PerformCurrenciesMainMenueOptions(enCurrenciesMainMenuOptions CurrenciesMainMenueOptions)
    {

        system("cls");
        switch (CurrenciesMainMenueOptions)
        {
        case enCurrenciesMainMenuOptions::eListCurrencies:
            clsCurrenciesListScreen::ShowCurrenciesListScreen();
            _GoBackToCurrenciesMenu();
            break;

        case enCurrenciesMainMenuOptions::eFindCurrency:
            clsFindCurrencyScreen::ShowFindCurrencyScreen();
            _GoBackToCurrenciesMenu();
            break;

        case enCurrenciesMainMenuOptions::eUpdateCurrencyRate:
            clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
            _GoBackToCurrenciesMenu();
            break;

        case enCurrenciesMainMenuOptions::eCurrencyCalculator:
            clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
            _GoBackToCurrenciesMenu();
            break;

        case enCurrenciesMainMenuOptions::eMainMenu:
            break;
        }

    }

public:

    static void ShowCurrenciesMenu()
    {
        enCurrenciesMainMenuOptions Option;
        do {
            system("cls");
            _DrawScreenHeader("   Currancy Exhange Main Screen");

            cout << setw(37) << left << "" << "===========================================\n";
            cout << setw(37) << left << "" << "\t\tCurrency Exhange Menu\n";
            cout << setw(37) << left << "" << "===========================================\n";
            cout << setw(37) << left << "" << "\t[1] List Currencies\n";
            cout << setw(37) << left << "" << "\t[2] Find Currency\n";
            cout << setw(37) << left << "" << "\t[3] Update Rate\n";
            cout << setw(37) << left << "" << "\t[4] Currency Calculator\n";
            cout << setw(37) << left << "" << "\t[5] Main Menu\n";
            cout << setw(37) << left << "" << "===========================================\n";
            Option = ReadCurrenciesMainMenueOptions();
            _PerformCurrenciesMainMenueOptions(Option);
        } while (Option != enCurrenciesMainMenuOptions::eMainMenu);
    }

};

