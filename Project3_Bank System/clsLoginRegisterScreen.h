#pragma once
#include "clsScreen.h"
#include "clsString.h"
#include "clsUser.h";
#include <string>
class clsLoginRegisterScreen : protected clsScreen
{
private:
	static void printLoginRegisterRecordLine(clsUser::stLoginRegisterRecord LoginRegisterRecord)
	{
		cout << setw(8) << left << "" << "| " << setw(30) << left << LoginRegisterRecord.DateTime;
		cout << "| " << setw(20) << left << LoginRegisterRecord.UserName;
		cout << "| " << setw(20) << left << LoginRegisterRecord.Password;
		cout << "| " << setw(20) << left << LoginRegisterRecord.Permissions;
		cout << endl;
	}

public:
	static void ShowLoginRegisterScreen()
	{
		system("cls");
		if (!clsScreen::checkAccessRights(clsUser::pShowLogInRegister))
		{
			return;
		}

		vector <clsUser::stLoginRegisterRecord> vUserLoginRegisterRecord = clsUser::GetLoginRegisterList();
		string Title = "\t Login Register List Screen";
		string SubTitle = "\t       (" + to_string(vUserLoginRegisterRecord.size())+ ") Record(s).";
		
		drawScreenHeader(Title, SubTitle);

		cout << endl;
		cout << setw(8) << left << "" << "___________________________________________________";
		cout << "_________________________________________________\n\n";
		cout << setw(8) << left << "" << "| " << setw(30) << left << "Date/Time";
		cout << "| " << setw(20) << left << "UserName";
		cout << "| " << setw(20) << left << "Password";
		cout << "| " << setw(20) << left << "Permissions";
		cout << "\n";
		cout << setw(8) << left << "" << "________________________________________";
		cout << "____________________________________________________________\n\n";
		
		if (vUserLoginRegisterRecord.size() == 0)
			cout << "\t\t\t\tNo Login Available In The System!";
		else
			for (clsUser::stLoginRegisterRecord LoginRegisterRecord : vUserLoginRegisterRecord)
			{
				printLoginRegisterRecordLine(LoginRegisterRecord);
			}

		cout << "\n";
		cout << setw(8) << left << "" << "________________________________________";
		cout << "____________________________________________________________\n\n";
	
	}
};

