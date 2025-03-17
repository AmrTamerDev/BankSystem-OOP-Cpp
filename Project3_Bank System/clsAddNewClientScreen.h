#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsUtil.h"
#include "clsScreen.h"
#include "clsBankClient.h"

class clsAddNewClientScreen : protected clsScreen
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

	static void ShowAddNewClient()
	{
		if (!clsScreen::checkAccessRights(clsUser::pAddNewClient))
		{
			return;
		}

		drawScreenHeader("\t    Add New Client Screen");
		string AccountNumber;

		cout << "\nPlease Enter Account Number: ";
		AccountNumber = clsInputValidate::ReadString();

		while (clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number is Already Used, Choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);
		readClientInfo(NewClient);

		clsBankClient::enSaveResult SaveResult;
		SaveResult = NewClient.Save();

		switch (SaveResult)
		{
		case clsBankClient::enSaveResult::svSucceeded:
			cout << "\nAccount Added Successfully :-)\n";
			printClient(NewClient);
			break;

		case clsBankClient::enSaveResult::svFailedEmptyObject:
			cout << "\nError Account is not Saved was because it's empty object :-(\n";
			break;

		case clsBankClient::enSaveResult::svFailedAccountNumberExists:
			cout << "\nError Account is Already Exist can't be saved it again :-(\n";
			break;
		}


	}
};

