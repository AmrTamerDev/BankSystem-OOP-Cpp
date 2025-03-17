#pragma once
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsUser.h"

class clsTransferScreen : protected clsScreen
{
private:
	static void printClient(clsBankClient Client, string Person = "")
	{

		cout << "\n\t  Client Card " + Person;
		cout << "\n========================================";
		cout << "\nFull Name      : " << Client.GetFullName();
		cout << "\nAccount Number : " << Client.GetAccountNumber();
		cout << "\nAccount Balance: " << Client.AccountBalance;
		cout << "\n========================================\n";
	}

	static string readAccountNumber(string Operation = "")
	{
		string AccountNumber;
		cout << "\nPlease Enter Account Number to Transfer " << Operation << ": ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccountNumber is Not found, choose another one right to Transfer From: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		return AccountNumber;
	}

public:
	static void ShowTransferScreen()
	{
		drawScreenHeader("\t      Transfer Screen");

		clsBankClient SenderClient = clsBankClient::Find(readAccountNumber("From"));
		printClient(SenderClient, "For Sender");

		clsBankClient ReceiverClient = clsBankClient::Find(readAccountNumber("To"));
		printClient(ReceiverClient, "For Receiver");

		double Amount;

		cout << "\nEnter Transfer Amount? ";
		Amount = clsInputValidate::ReadDblNumberBetween(0, SenderClient.AccountBalance, "Amount Exceeds the available Balance, Enter another Amount? ");
		
		char Choice = 'n';

		cout << "Are you sure you want to perform this operation? y/n? ";
		cin >> Choice;

		if (toupper(Choice) == 'Y')
		{
			if (SenderClient.Transfer(Amount, ReceiverClient, CurrentUser.UserName))
			{
				cout << "\nTransfer done Successfully\n";
			}
			else
			{
				cout << "\nTransfer Failed\n";
			}
		}

		printClient(SenderClient, "For Sender");
		printClient(ReceiverClient, "For Receiver");
	}
};

