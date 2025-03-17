#pragma once
#include <iostream>
#include <string>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include "clsUtil.h"
using namespace std;

class clsAddNewUserScreen : protected clsScreen
{
private:

	static void readUserNameInfo(clsUser& User)
	{
		cout << "\nEnter FirstName: ";
		User.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter LastName: ";
		User.LastName = clsInputValidate::ReadString();
	
		cout << "\nEnter Email: ";
		User.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone: ";
		User.Phone = clsInputValidate::ReadString();

		cout << "\nEnter Password: ";
		User.Password = clsInputValidate::ReadString();

		User.Permissions = readPermissionsToSet();
	}

	static short readPermissionsToSet()
	{
		int Permissions = 0;

		char Choice = 'n';

		cout << "\nEnter Permissions:";

		cout << "\nDo you want to give full access? y/n? ";
		cin >> Choice;

		if (toupper(Choice) == 'Y')
		{
			return -1;
		}

		cout << "\nShow Client List? y/n? ";
		cin >> Choice;

		if (toupper(Choice) == 'Y')
		{
			Permissions += clsUser::enPermissions::pListClients;
		}

		cout << "\nAdd New Client? y/n? ";
		cin >> Choice;

		if (toupper(Choice) == 'Y')
		{
			Permissions += clsUser::enPermissions::pAddNewClient;
		}

		cout << "\nDelete Client? y/n? ";
		cin >> Choice;

		if (toupper(Choice) == 'Y')
		{
			Permissions += clsUser::enPermissions::pDeleteClient;
		}

		cout << "\nUpdate Client? y/n? ";
		cin >> Choice;

		if (toupper(Choice) == 'Y')
		{
			Permissions += clsUser::enPermissions::pUpdateClient;
		}

		cout << "\nFind Client? y/n? ";
		cin >> Choice;

		if (toupper(Choice) == 'Y')
		{
			Permissions += clsUser::enPermissions::pFindClient;
		}

		cout << "\nTransactions? y/n? ";
		cin >> Choice;

		if (toupper(Choice) == 'Y')
		{
			Permissions += clsUser::enPermissions::pTransaction;
		}

		cout << "\nManage Users? y/n? ";
		cin >> Choice;

		if (toupper(Choice) == 'Y')
		{
			Permissions += clsUser::enPermissions::pManageUsers;
		}

		cout << "\nShow Login Register? y/n? ";
		cin >> Choice;

		if (toupper(Choice) == 'Y')
		{
			Permissions += clsUser::enPermissions::pShowLogInRegister;
		}

		return Permissions;
	}

	static void printUser(clsUser User)
	{
		cout << "\n\t\tUser Card";
		cout << "\n========================================";
		cout << "\nFirst Name     : " << User.FirstName;
		cout << "\nLast Name      : " << User.LastName;
		cout << "\nFull Name      : " << User.GetFullName();
		cout << "\nEmail          : " << User.Email;
		cout << "\nPhone          : " << User.Phone;
		cout << "\nUser Name      : " << User.UserName;
		cout << "\nPassword       : " << User.Password;
		cout << "\nPermissions    : " << User.Permissions;
		cout << "\n========================================\n";
	}

public:

	static void ShowAddNewUserScree()
	{
		drawScreenHeader("\t     Add New User Screen");

		string UserName;

		cout << "\nPlease Enter UserName: ";
		UserName = clsInputValidate::ReadString();

		while (clsUser::IsUserExist(UserName))
		{
			cout << "\nUserName Is Already used, choose another one: ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::GetAddNewUserObject(UserName);

		readUserNameInfo(User);

		clsUser::enSaveResults SaveResults = User.Save();

		switch (SaveResults)
		{
		case clsUser::enSaveResults::svSucceded:
			cout << "\nUser Added Successfully:-)\n";
			printUser(User);
			break;

		case clsUser::enSaveResults::svFailedEmptyObject:
			cout << "\nError User was not saved because It's Empty:-(\n";
			break;

		case clsUser::enSaveResults::svFailedUserExists:
			cout << "\nError User was not saved because UserName is Exists:-(\n";
			break;
		}
	}
};

