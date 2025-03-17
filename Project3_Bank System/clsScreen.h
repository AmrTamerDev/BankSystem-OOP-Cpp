#pragma once
#include <iostream>
#include <string>
#include "clsDate.h"
#include "Global.h"

using namespace std;

class clsScreen
{
protected:

	static void drawScreenHeader(string title, string subTitle = "")
	{
		cout << "\t\t\t\t\t__________________________________________\n";
		cout << "\n\t\t\t\t\t" << title << endl;
		if (subTitle != "")
		{
			cout << "\t\t\t\t\t" << subTitle << endl;
		}
		cout << "\t\t\t\t\t__________________________________________\n";
		
		cout << "\n\t\t\t\t\tUser: " << CurrentUser.UserName << endl;
		cout << "\t\t\t\t\t";
		cout << "Date: " << clsDate::DateToString(clsDate()) << "\n\n";
	}

	static bool checkAccessRights(clsUser::enPermissions Permissions)
	{
		if (!CurrentUser.CheckAccessPermissions(Permissions))
		{
			cout << "\t\t\t\t\t__________________________________________\n";
			cout << "\n\t\t\t\t\t" << "     Access Denied! Contact your Admin." << endl;
			cout << "\t\t\t\t\t__________________________________________\n";
			return false;
		}
		else
		{
			return true;
		}
	}

};

