#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsListUserScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

using namespace std;

class clsManageUsersScreen : protected clsScreen
{
private:

	enum enManageUsersMenuOption
	{
		eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3,
		eUpdateUser = 4, eFindUser = 5, eMainMenu = 6
	};

	static short readManageUsersMenuOption()
	{
		short NumberChoice;

		cout << setw(40) << left << "" << "Choose what do you want to do? [1 to 6]? ";
		NumberChoice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number between 1 to 6? ");

		return NumberChoice;
	}

	static void goBackToManageUsersMenu()
	{
		cout << "\nPress any Key To Go Back To Manage User Menu...\n" << endl;
		system("pause > 0");
		ShowManageUsersMenu();
	}

	static void showListUserScreen()
	{
		//cout << "\nList User Screen Will be here...\n\n";
		clsListUserScreen::ShowUsersList();
	}

	static void showAddNewUserScreen()
	{
		//cout << "\nAdd New User Screen Will be here...\n\n";
		clsAddNewUserScreen::ShowAddNewUserScree();
	}

	static void showDeleteUserScreen()
	{
		//cout << "\nDelete User Screen Will be here...\n\n";
		clsDeleteUserScreen::ShowDeleteUserScreen();
	}

	static void showUpdateUserScreen()
	{
		//cout << "\nUpdate User Screen Will be here...\n\n";
		clsUpdateUserScreen::ShowUpdateUserScreen();
	}

	static void showFindUserScreen()
	{
		//cout << "\nFind User Screen Will be here...\n\n";
		clsFindUserScreen::ShowFindUserScreen();
	}

	static void performManageUsersMenuOption(enManageUsersMenuOption ManageUsersMenuOption)
	{
		switch (ManageUsersMenuOption)
		{
		case enManageUsersMenuOption::eListUsers:
			system("cls");
			showListUserScreen();
			goBackToManageUsersMenu();
			break;
			
		case enManageUsersMenuOption::eAddNewUser:
			system("cls");
			showAddNewUserScreen();
			goBackToManageUsersMenu();
			break;

		case enManageUsersMenuOption::eDeleteUser:
			system("cls");
			showDeleteUserScreen();
			goBackToManageUsersMenu();
			break;

		case enManageUsersMenuOption::eUpdateUser:
			system("cls");
			showUpdateUserScreen();
			goBackToManageUsersMenu();
			break;

		case enManageUsersMenuOption::eFindUser:
			system("cls");
			showFindUserScreen();
			goBackToManageUsersMenu();
			break;

		case enManageUsersMenuOption::eMainMenu:
			break;
		}
	}

public:

	static void ShowManageUsersMenu()
	{
		system("cls");

		if (!clsScreen::checkAccessRights(clsUser::pManageUsers))
		{
			return;
		}

		drawScreenHeader("\t    Manage Users Screen");
		cout << setw(40) << left << "" << "==========================================\n";
		cout << setw(40) << left << "" << "\t    Manage Users Menu\n";
		cout << setw(40) << left << "" << "==========================================\n";
		cout << setw(40) << left << "" << "[1] List Users.\n";
		cout << setw(40) << left << "" << "[2] Add New User.\n";
		cout << setw(40) << left << "" << "[3] Delete User.\n";
		cout << setw(40) << left << "" << "[4] Update User.\n";
		cout << setw(40) << left << "" << "[5] Find User.\n";
		cout << setw(40) << left << "" << "[6] Main Menu.\n";
		cout << setw(40) << left << "" << "==========================================\n";
		performManageUsersMenuOption((enManageUsersMenuOption)readManageUsersMenuOption());
	}
};

