#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithDrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"
#include "clsUtil.h"

using namespace std;

class clsTransactionsScreen : protected clsScreen
{
private:
	
	enum enTransactionMenuOption
	{
		eDeposit = 1, eWithDraw = 2, eTotalBalances = 3, eTransfer = 4, eTransferLog = 5, eShowMainMenu = 6
	};

	static short readTransactionsMenuOption()
	{
		short NumberChoice;

		cout << setw(40) << left << "" << "Choose what do you want to do? [1 to 6]? ";
		NumberChoice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number between 1 to 6? ");

		return NumberChoice;
	}

	static void showDepositScreen()
	{
		//cout << "\nDeposit Screen Will be here...\n\n";
		clsDepositScreen::ShowDepositScreen();
	}

	static void showWithDrawScreen()
	{
		//cout << "\nWithDraw Screen Will be here...\n\n";
		clsWithDrawScreen::ShowWithDrawScreen();
	}

	static void showTotalBalancesScreen()
	{
		//cout << "\nTotalBalances Screen Will be here...\n\n";
		clsTotalBalancesScreen::ShowTotalBalances();
	}

	static void showTransferScreen()
	{
		//cout << "\nTransfer Screen Will be here...\n\n";
		clsTransferScreen::ShowTransferScreen();
	}

	static void showTransferLogScreen()
	{
		clsTransferLogScreen::ShowTransferLogScreen();
	}

	static void goBackToTransactionMenu()
	{
		cout << "\n\nPress any Key To Go Back To Transaction Menu...\n" << endl;
		system("pause > 0");
		ShowTransactionMenu();
	}

	static void performTransactionsMenuOption(enTransactionMenuOption TransactionMenuOption)
	{
		switch (TransactionMenuOption)
		{
		case enTransactionMenuOption::eDeposit:
			system("cls");
			showDepositScreen();
			goBackToTransactionMenu();
			break;

		case enTransactionMenuOption::eWithDraw:
			system("cls");
			showWithDrawScreen();
			goBackToTransactionMenu();
			break;

		case enTransactionMenuOption::eTotalBalances:
			system("cls");
			showTotalBalancesScreen();
			goBackToTransactionMenu();
			break;

		case enTransactionMenuOption::eTransfer:
			system("cls");
			showTransferScreen();
			goBackToTransactionMenu();
			break;

		case enTransactionMenuOption::eTransferLog:
			system("cls");
			showTransferLogScreen();
			goBackToTransactionMenu();
			break;

		case enTransactionMenuOption::eShowMainMenu:
			break;
		}
	}

public:

	static void ShowTransactionMenu()
	{
		system("cls");

		if (!clsScreen::checkAccessRights(clsUser::pTransaction))
		{
			return;
		}

		drawScreenHeader("\t     Transaction Screen");
		cout << setw(40) << left << "" << "==========================================\n";
		cout << setw(40) << left << "" << "\t     Transaction Menu\n";
		cout << setw(40) << left << "" << "==========================================\n";
		cout << setw(40) << left << "" << "[1] Deposit.\n";
		cout << setw(40) << left << "" << "[2] Withdraw.\n";
		cout << setw(40) << left << "" << "[3] Total Balances.\n";
		cout << setw(40) << left << "" << "[4] Transfer.\n";
		cout << setw(40) << left << "" << "[5] Transfer Log.\n";
		cout << setw(40) << left << "" << "[6] Main Menu.\n";
		cout << setw(40) << left << "" << "==========================================\n";
		performTransactionsMenuOption((enTransactionMenuOption)readTransactionsMenuOption());
	}
};

