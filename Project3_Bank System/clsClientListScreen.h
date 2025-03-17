#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUtil.h"
#include "clsUser.h"
using namespace std;

class clsClientListScreen : protected clsScreen
{
private:
	static void printClientRecordLine(clsBankClient Client)
	{
		cout << setw(8) << left << "" << "| " << setw(15) << left << Client.GetAccountNumber();
		cout << "| " << setw(20) << left << Client.GetFullName();
		cout << "| " << setw(12) << left << Client.Phone;
		cout << "| " << setw(20) << left << Client.Email;
		cout << "| " << setw(10) << left << Client.PinCode;
		cout << "| " << setw(12) << left << Client.AccountBalance;
		cout << endl;
	}

public:
	static void ShowClientsList()
	{
		if (!clsScreen::checkAccessRights(clsUser::pListClients))
		{
			return;
		}

		vector <clsBankClient> vClients = clsBankClient::GetClientsList();
		
		string Title = "\t\tClient List Screen";
		string SubTitle = "\t\t(" + to_string(vClients.size()) + ") Client(s).";
		
		drawScreenHeader(Title, SubTitle);
		cout << endl;
		cout << setw(8) << left << "" << "___________________________________________________";
		cout << "_____________________________________________\n\n";
		cout << setw(8) << left << "" << "| " << setw(15) << left << "Account Number";
		cout << "| " << setw(20) << left << "Client Name";
		cout << "| " << setw(12) << left << "Phone";
		cout << "| " << setw(20) << left << "Email";
		cout << "| " << setw(10) << left << "Pin Code";
		cout << "| " << setw(12) << left << "Balance";
		cout << "\n";
		cout << setw(8) << left << "" << "________________________________________";
		cout << "________________________________________________________\n\n";

		if (vClients.size() == 0)
			cout << "\t\t\t\tNo Clients Available In The System!";
		else
		{
			for (clsBankClient Client : vClients)
			{
				printClientRecordLine(Client);
			}
		}

		cout << "\n";
		cout << setw(8) << left << "" << "________________________________________";
		cout << "________________________________________________________\n\n";
	}

};

