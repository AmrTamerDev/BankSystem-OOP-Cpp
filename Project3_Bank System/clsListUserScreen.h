#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsUser.h"

using namespace std;

class clsListUserScreen : protected clsScreen
{
private:

	static void printUserRecordLine(clsUser User)
	{
		cout << setw(8) << left << "" << "| " << setw(15) << left << User.UserName;
		cout << "| " << setw(20) << left << User.GetFullName();
		cout << "| " << setw(12) << left << User.Phone;
		cout << "| " << setw(20) << left << User.Email;
		cout << "| " << setw(10) << left << User.Password;
		cout << "| " << setw(12) << left << User.Permissions;
		cout << endl;
	}

public:

	static void ShowUsersList()
	{
		vector <clsUser> vUsers = clsUser::GetUsersList();

		string Title = "\t     User List Screen";
		string SubTitle = "\t       (" + to_string(vUsers.size()) + ") User(s).";

		drawScreenHeader(Title, SubTitle);

		cout << endl;
		cout << setw(8) << left << "" << "___________________________________________________";
		cout << "_________________________________________________\n\n";
		cout << setw(8) << left << "" << "| " << setw(15) << left << "UserName";
		cout << "| " << setw(20) << left << "Full Name";
		cout << "| " << setw(12) << left << "Phone";
		cout << "| " << setw(20) << left << "Email";
		cout << "| " << setw(10) << left << "Password";
		cout << "| " << setw(12) << left << "Permissions";
		cout << "\n";
		cout << setw(8) << left << "" << "________________________________________";
		cout << "____________________________________________________________\n\n";

		if (vUsers.size() == 0)
			cout << "\t\t\t\tNo Users Available In The System!";

		for (clsUser User : vUsers)
		{
			printUserRecordLine(User);
		}

		cout << "\n";
		cout << setw(8) << left << "" << "________________________________________";
		cout << "____________________________________________________________\n\n";
	}
};

