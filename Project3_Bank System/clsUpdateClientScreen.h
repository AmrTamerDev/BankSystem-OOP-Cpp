#pragma once
#include <iostream>
#include <string>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUtil.h"

class clsUpdateClientScreen : protected clsScreen
{
private:

	static void readClientInfo(clsBankClient& Client)
	{
		cout << "\nEnter FirstName: ";
		Client.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter LastName: ";
		Client.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email: ";
		Client.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone: ";
		Client.Phone = clsInputValidate::ReadString();

		cout << "\nEnter PinCode: ";
		Client.PinCode = clsInputValidate::ReadString();

		cout << "\nEnter Account Balance: ";
		Client.AccountBalance = clsInputValidate::ReadDblNumber();
	}

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
	static void ShowUpdateClientScreen()
	{
		if (!clsScreen::checkAccessRights(clsUser::pUpdateClient))
		{
			return;
		}

		drawScreenHeader("\t   Update Client Screen");
		string AccountNumber;

		cout << "\nPlease Enter client Account Number: ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number is not found, choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		//Client.Print();
		printClient(Client);

		char Choice = 'n';

		cout << "\nAre you sure you want to update this client y/n? ";
		cin >> Choice;

		if (toupper(Choice))
		{
			cout << "\n\t\tUpdate Client Info:";
			cout << "\n========================================";
			readClientInfo(Client);

			clsBankClient::enSaveResult SaveResult;

			SaveResult = Client.Save();

			switch (SaveResult)
			{
			case clsBankClient::enSaveResult::svSucceeded:
				cout << "\nAccount Update Successfully :-)\n";
				//Client.Print();
				break;

			case clsBankClient::enSaveResult::svFailedEmptyObject:
				cout << "\nError Account was not saved because It's Empty :-(\n";
				break;
			}
		}
	}
};

