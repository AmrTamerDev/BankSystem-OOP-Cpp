#pragma once
#include <iostream>
#include <string>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUtil.h"
class clsDeleteClientScreen : protected clsScreen
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

public:

	static void ShowDeleteClientScreen()
	{
		if (!clsScreen::checkAccessRights(clsUser::pDeleteClient))
		{
			return;
		}

		drawScreenHeader("\t    Delete Client Screen");
		string AccountNumber;

		cout << "\nPlease Enter Account Number: ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccountNumber is Not found, choose another one right: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient DeleteClient = clsBankClient::Find(AccountNumber);
		printClient(DeleteClient);

		char ReadOption;

		cout << "\nAre you sure you want to delete this client y/n? ";
		cin >> ReadOption;

		if ((toupper(ReadOption)) == 'Y')
		{
			if (DeleteClient.Delete())
			{
				cout << "\nClient Deleted Successfully :-)\n";
				printClient(DeleteClient);
			}
			else
			{
				cout << "\nError Client Was not Deleted :-(\n";
			}
		}

	}
};

