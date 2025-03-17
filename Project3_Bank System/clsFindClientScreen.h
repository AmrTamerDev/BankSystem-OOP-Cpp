#pragma once
#include <iostream>
#include <string>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUtil.h"
using namespace std;

class clsFindClientScreen : protected clsScreen
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

	static void ShowFindClientScreen()
	{
		if (!clsScreen::checkAccessRights(clsUser::pFindClient))
		{
			return;
		}

		drawScreenHeader("\t     Find Client Screen");

		string AccountNumber;

		cout << "\nPlease Enter Account Number: ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number is not found, choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}
		
		clsBankClient Client = clsBankClient::Find(AccountNumber);

		if (!Client.IsEmpty())
		{
			cout << "\nClient Found :-)\n";
			printClient(Client);
		}
		else
		{
			cout << "\nClient was not Found :-(\n";
		}		
	}
};

