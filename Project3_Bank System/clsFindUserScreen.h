#pragma once
#include <iostream>
#include <string>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsUser.h"

using namespace std;

class clsFindUserScreen : protected clsScreen
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
	static void ShowFindUserScreen()
	{
		drawScreenHeader("\t      Find User Screen");

		string UserName;

		cout << "\nPlease Enter UserName: ";
		UserName = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\nUserName is Not Found, choose another one: ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::Find(UserName);

		if (!User.IsEmpty())
		{
			cout << "\nUser Found:-)\n";
			printUser(User);	
		}
		else
		{
			cout << "\nClient was not Found :-(\n";
		}

	}
};

