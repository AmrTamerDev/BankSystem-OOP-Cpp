#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUtil.h"

using namespace std;

class clsTotalBalancesScreen : protected clsScreen
{
private:

	static void PrintClientRecordBalanceLine(clsBankClient Client)
	{
		cout << setw(30) << left << "" << "| " << setw(24) << left << Client.GetAccountNumber();
		cout << "| " << setw(26) << left << Client.GetFullName();
		cout << "| " << setw(15) << left << Client.AccountBalance;
	}

public:

	static void ShowTotalBalances()
	{
		vector <clsBankClient> vClients = clsBankClient::GetClientsList();
		string Title = "\t    Balances List Screen";
		string SubTitle = "\t    (" + to_string(vClients.size()) + ") Client(s).";
		drawScreenHeader(Title, SubTitle);
		cout << endl; 
		cout << setw(30) << left << "" << "_________________________________________";
		cout << "______________________\n\n";
		cout << left << setw(30) << "" << "| " << "Account Number";
		cout << left << setw(10) << "" << "| " << "Client Name";
		cout << left << setw(15) << "" << "| " << "Balance";
		cout << endl;
		cout << setw(30) << left << "" << "_________________________________________";
		cout << "______________________\n\n";
	
		double TotalBalances = clsBankClient::GetTotalBalances();

		if (vClients.size() == 0)
			cout << "\t\t\t\tNo Clients Available In The System!";
		else
		{
			for (clsBankClient Client : vClients)
			{
				PrintClientRecordBalanceLine(Client);
				cout << endl;
			}
		}

		cout << endl;
		cout << setw(30) << left << "" << "_________________________________________";
		cout << "______________________\n\n";

		cout << "\n\t\t\t\t\t\tTotal Balances = " << TotalBalances << endl;
		cout << "\n\t\t\t\t\t\t( " << clsUtil::NumberToText(TotalBalances) << ")" << endl;
	}
};

