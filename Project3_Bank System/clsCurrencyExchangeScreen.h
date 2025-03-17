#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsFindCurrencyScreen.h"
#include "clsCurrenciesListScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"

class clsCurrencyExchangeScreen : protected clsScreen
{
private:
	enum enCurrencyExchangeMenuOption
	{
		eListCurrencies = 1, eFindCurrency = 2,
		eUpdateCurrencyRate = 3, eCurrencyCalculator = 4,
		eMainMenu = 5
	};

	static void showListCurrenciesScreen()
	{
		//cout << "\nList Currencies List Screen Will Be Here.\n";
		clsListCurrenciesScreen::ShowCurrenciesListScreen();
	}

	static void showFindCurrencyScreen()
	{
		//cout << "\nFind Currency Screen Will Be Here.\n";
		clsFindCurrencyScreen::ShowFindCurrencyScreen();
	}

	static void showUpdateCurrencyRateScreen()
	{
		//cout << "\nUpdate Currency Screen Will Be Here.\n";
		clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
	}

	static void showCurrencyCalculatorScreen()
	{
		//cout << "\nCurrency Calculator Screen Will Be Here.\n";
		clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
	}

	static void goBackToCurrencyMenu()
	{
		cout << "\n\nPress any key to go back to Currencies Menu...\n";
		system("pause > 0");
		ShowCurrencyExchangeMenu();
	}

	static short readCurrencyMenuOption()
	{
		short NumberChoice;

		cout << setw(40) << left << "" << "Choose what do you want to do? [1 to 5]? ";
		NumberChoice = clsInputValidate::ReadShortNumberBetween(1, 5, "Enter Number between 1 to 5? ");

		return NumberChoice;
	}

	static void performCurrencyExchangeMenuOption(enCurrencyExchangeMenuOption CurrencyExchangeMenuOption)
	{
		switch (CurrencyExchangeMenuOption)
		{
		case enCurrencyExchangeMenuOption::eListCurrencies:
			system("cls");
			showListCurrenciesScreen();
			goBackToCurrencyMenu();
			break;

		case enCurrencyExchangeMenuOption::eFindCurrency:
			system("cls");
			showFindCurrencyScreen();
			goBackToCurrencyMenu();
			break;

		case enCurrencyExchangeMenuOption::eUpdateCurrencyRate:
			system("cls");
			showUpdateCurrencyRateScreen();
			goBackToCurrencyMenu();
			break;

		case enCurrencyExchangeMenuOption::eCurrencyCalculator:
			system("cls");
			showCurrencyCalculatorScreen();
			goBackToCurrencyMenu();
			break;

		case enCurrencyExchangeMenuOption::eMainMenu:
			system("cls");
			break;
		}

	}

public:

	static void ShowCurrencyExchangeMenu()
	{
		system("cls");
		drawScreenHeader("\tCurrency Exchange Main Screen");
		cout << "\n" << setw(40) << left << "" << "==========================================\n";
		cout << setw(40) << left << "" << "\t  Currency Exchange Menu\n";
		cout << setw(40) << left << "" << "==========================================\n";
		cout << setw(40) << left << "" << "[1] List Currencies.\n";
		cout << setw(40) << left << "" << "[2] Find Currency.\n";
		cout << setw(40) << left << "" << "[3] Update Rate.\n";
		cout << setw(40) << left << "" << "[4] Currency Calculator.\n";
		cout << setw(40) << left << "" << "[5] Main Menu.\n";
		cout << setw(40) << left << "" << "==========================================\n";
		performCurrencyExchangeMenuOption((enCurrencyExchangeMenuOption)readCurrencyMenuOption());
	}
};

