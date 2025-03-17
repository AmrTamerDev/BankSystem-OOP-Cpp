#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "clsScreen.h"
#include "Global.h"
#include "clsInputValidate.h"
#include "clsClientListScreen.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "clsLoginRegisterScreen.h"
#include "clsCurrencyExchangeScreen.h"
using namespace std;

class clsMainScreen : protected clsScreen
{
private:
	enum enMainMenuOption 
	{ 
		eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
		eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenu = 6,
		eManageUsers = 7, eLoginRegister = 8, eCurrencyExchange = 9, 
		eExit = 10
	};

	static short readMainMenuOption()
	{
		short NumberChoice;

		cout << setw(40) << left << "" << "Choose what do you want to do? [1 to 10]? ";
		NumberChoice = clsInputValidate::ReadShortNumberBetween(1, 10, "Enter Number between 1 to 10? ");

		return NumberChoice;
	}

	static void goBackToMainMenu()
	{
		cout << setw(40) << left << "" << "\n\tPress any Key To Go Back To Main Menu...\n" << endl;
		system("pause > 0");
		ShowMainMenu();
	}

	static void showAllClientsScreen()
	{
		//cout << "\nClient List Screen Will be here...\n\n";
		clsClientListScreen::ShowClientsList();
	}

	static void showAddNewClientsScreen()
	{
		//cout << "\nAdd New Client Screen Will be here...\n\n";
		clsAddNewClientScreen::ShowAddNewClient();
	}

	static void showDeleteClientScreen()
	{
		//cout << "\nDelete Client Screen Will be here...\n\n";
		clsDeleteClientScreen::ShowDeleteClientScreen();
	}

	static void showUpdateClientScreen()
	{
		//cout << "\nUpdate Client Screen Will be here...\n\n";
		clsUpdateClientScreen::ShowUpdateClientScreen();
	}

	static void showFindClientScreen()
	{
		//cout << "\nFind Client Screen Will be here...\n\n";
		clsFindClientScreen::ShowFindClientScreen();
	}

	static void showTransactionsMenu()
	{
		//cout << "\nTransactions Menu Will be here...\n\n";
		clsTransactionsScreen::ShowTransactionMenu();
	}

	static void showManageUsersMenu()
	{
		//cout << "\nUsers Menu Will be here...\n\n";
		clsManageUsersScreen::ShowManageUsersMenu();
	}

	static void showLoginRegisterScreen()
	{
		clsLoginRegisterScreen::ShowLoginRegisterScreen();
	}
	static void showCurrencyExchangeScreen()
	{
		clsCurrencyExchangeScreen::ShowCurrencyExchangeMenu();
	}

	static void logOut()
	{
		CurrentUser = clsUser::Find("", "");
	}

	/*static void showEndScreen()
	{
		cout << "\nEnd Screen Will be here...\n\n";
	}*/

	static void performMainMenuOption(enMainMenuOption MainMenuOption)
	{
		switch (MainMenuOption)
		{
		case enMainMenuOption::eListClients:
			system("cls");
			showAllClientsScreen();
			goBackToMainMenu();
			break;

		case enMainMenuOption::eAddNewClient:
			system("cls");
			showAddNewClientsScreen();
			goBackToMainMenu();
			break;

		case enMainMenuOption::eDeleteClient:
			system("cls");
			showDeleteClientScreen();
			goBackToMainMenu();
			break;

		case enMainMenuOption::eUpdateClient:
			system("cls");
			showUpdateClientScreen();
			goBackToMainMenu();
			break;

		case enMainMenuOption::eFindClient:
			system("cls");
			showFindClientScreen();
			goBackToMainMenu();
			break;

		case enMainMenuOption::eShowTransactionsMenu:
			system("cls");
			showTransactionsMenu();
			goBackToMainMenu();
			break;

		case enMainMenuOption::eManageUsers:
			system("cls");
			showManageUsersMenu();
			goBackToMainMenu();
			break;
		
		case enMainMenuOption::eLoginRegister:
			system("cls");
			showLoginRegisterScreen();
			goBackToMainMenu();
			break;

		case enMainMenuOption::eCurrencyExchange:
			system("cls");
			showCurrencyExchangeScreen();
			goBackToMainMenu();
			break;

		case enMainMenuOption::eExit:
			system("cls");
			//showEndScreen();
			logOut();
			break;
		}
	}

public:

	
	static void ShowMainMenu()
	{
		system("cls");
		drawScreenHeader("\t\tMain Screen");
		
		cout << "\n" << setw(40) << left << "" << "==========================================\n";
		cout << setw(40) << left << "" << "\t\tMain Menu\n";
		cout << setw(40) << left << "" << "==========================================\n";
		cout << setw(40) << left << "" << "[01] Show Client List.\n";
		cout << setw(40) << left << "" << "[02] Add New Client.\n";
		cout << setw(40) << left << "" << "[03] Delete Client.\n";
		cout << setw(40) << left << "" << "[04] Update Client.\n";
		cout << setw(40) << left << "" << "[05] Find Client.\n";
		cout << setw(40) << left << "" << "[06] Transactions.\n";
		cout << setw(40) << left << "" << "[07] Manage Users.\n";
		cout << setw(40) << left << "" << "[08] Login Register.\n";
		cout << setw(40) << left << "" << "[09] Currency Exchange.\n";
		cout << setw(40) << left << "" << "[10] LogOut.\n";
		cout << setw(40) << left << "" << "==========================================\n";
		performMainMenuOption((enMainMenuOption)readMainMenuOption());
	}
};

