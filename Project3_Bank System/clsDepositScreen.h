#pragma once
#include <iostream>
#include <string>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUtil.h"
#include "clsScreen.h"

class clsDepositScreen : protected clsScreen
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

	static void ShowDepositScreen() 
	{
		drawScreenHeader("\t      Deposit Screen");

		string AccountNumber = readAccountNumber();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nClient with [" << AccountNumber << "] Not Exist";
			AccountNumber = readAccountNumber();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		printClient(Client);

		double DepositAmount = 0;
		cout << "\nPlease enter deposit amount? ";
	    DepositAmount = clsInputValidate::ReadDblNumber();

		char Choice = 'n';
		cout << "\nAre you sure you want to perform this transaction? y/n? ";
		cin >> Choice;

		if ((toupper(Choice)) == 'Y')
		{
			Client.Deposit(DepositAmount);
			cout << "\nAmount Deposited Successfully.\n";
			cout << "\nNew Balance is: " << Client.AccountBalance << endl;
		}
		else
		{
			cout << "\nOperation was cancelled.\n";
		}
	}
};

