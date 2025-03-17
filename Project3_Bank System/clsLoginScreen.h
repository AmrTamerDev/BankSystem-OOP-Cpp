#pragma once
#include "clsMainScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"
#include "clsScreen.h"
#include "Global.h"

using namespace std;

class clsLoginScreen : protected clsScreen
{
private:

	static bool login()
	{
		string UserName, PassWord;
		bool LoginFailed = false;
		short NumberOfTries = 3;
		do
		{

			if (LoginFailed)
			{
				--NumberOfTries;
				cout << "\nInvalid UserName/Password!\n";
				cout << "You have " << NumberOfTries << " Trial(s) to login.\n";
			}

			if (NumberOfTries == 0)
			{
				cout << "\n\nYou are Locked after 3 failed trails\n";
				return false;
			}

			cout << "\nEnter Username? ";
			UserName = clsInputValidate::ReadString();

			cout << "Enter Password? ";
			PassWord = clsInputValidate::ReadString();

			CurrentUser = clsUser::Find(UserName, PassWord);

			LoginFailed = CurrentUser.IsEmpty();
		

		} while (LoginFailed);
		CurrentUser.SaveRegisterLogIn();
		clsMainScreen::ShowMainMenu();
		return true;
	} 

public:

	static bool ShowLoginScreen()
	{
		system("cls");
		drawScreenHeader("\t\tLogin Screen");
		return login();
	}
};

