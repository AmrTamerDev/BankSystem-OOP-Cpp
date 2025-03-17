#pragma once
#include <iostream>
#include <string>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"
using namespace std;

class clsDeleteUserScreen : protected clsScreen
{
private:

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

	static void ShowDeleteUserScreen()
	{
		drawScreenHeader("\t     Delete User Screen");

		string UserName;

		cout << "\nPlease Enter UserName: ";
		UserName = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\nUserName is Not Found, choose another one: ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::Find(UserName);
		printUser(User);

		char Choice = 'n';

		cout << "\nAre You Sure you want to delete this User y/n? ";
		cin >> Choice;

		if (toupper(Choice) == 'Y')
		{
			if (User.Delete())
			{
				cout << "\nUser Deleted Successfully : -)\n";
				printUser(User);
			}
			else
			{
				cout << "\nError User Was not Deleted :-(\n";
			}
		}
	}
};

