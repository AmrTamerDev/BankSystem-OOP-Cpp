#pragma once
#include <iostream>
#include <string>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsWithDrawScreen : protected clsScreen
{
private:

	static void printClient(clsBankClient Client)
	{
		cout << "\n\t\tClient Card";
		cout << "\n========================================";
		cout << "\nFirst Name     : " << Client.FirstName;
		cout << "\nLast Name      : " << Client.LastName;
		cout << "\nFull Name      : " << Client.GetFullName();
		cout << "\nEmail          : " << Client.Email;
		cout << "\nPhone          : " << Client.Phone;
		cout << "\nAccount Number : " << Client.GetAccountNumber();
		cout << "\nPin Code       : " << Client.PinCode;
		cout << "\nAccount Balance: " << Client.AccountBalance;
		cout << "\n========================================\n";
	}

	static string readAccountNumber()
	{
		cout << "\nPlease Enter AccountNumber: ";
		return clsInputValidate::ReadString();
	}

public:

	static void ShowWithDrawScreen()
	{
		drawScreenHeader("\t    WithDraw Screen");

		string AccountNumber = readAccountNumber();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nClient with [" << AccountNumber << "] Not Exist";
			AccountNumber = readAccountNumber();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);

		printClient(Client);

		double WithDrawAmount = 0;

		cout << "\nPlease Enter WithDraw Amount? ";
		WithDrawAmount = clsInputValidate::ReadDblNumberBetween(1, Client.AccountBalance, "Cannot WithDraw, Insufficient Balance!\n\nPlease Enter WithDraw Amount?");

		char Choice = 'n';
		cout << "\nAre you sure you want to perform this transaction? y/n? ";
		cin >> Choice;

		if (toupper(Choice) == 'Y')
		{
			if (Client.WithDraw(WithDrawAmount))
			{
				cout << "\nAmount WithDraw Successfully.\n";
				cout << "\nNew Balance is: " << Client.AccountBalance << endl;
			}
			else
			{
				cout << "\nCannot WithDraw, Insufficient Balance!\n";
				cout << "\nAmount to WithDraw: " << WithDrawAmount << endl;
				cout << "Your Balance is: " << Client.AccountBalance << endl;
			}
		}
		else
		{
			cout << "\nOperation was cancelled.\n";
		}
	}
};

