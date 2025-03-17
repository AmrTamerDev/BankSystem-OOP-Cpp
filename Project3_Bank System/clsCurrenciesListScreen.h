#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
#include <string>
#include <iostream>

class clsListCurrenciesScreen : protected clsScreen
{
private:
	static void printCurrencyRecordLine(clsCurrency Currency)
	{
		cout << setw(8) << left << "" << "| " << setw(36) << left << Currency.GetCountryName();
		cout << "| " << setw(10) << left << Currency.GetCurrencyCode();
		cout << "| " << setw(36) << left << Currency.GetCurrencyName();
		cout << "| " << setw(10) << left << Currency.GetCurrencyRate();
		cout << "\n";
	}

public:
	static void ShowCurrenciesListScreen()
	{
		vector <clsCurrency> vCurrencyData = clsCurrency::GetCurrencyList();
		string Title = "\t   Currencies List Screen";
		string SubTitle = "\t      (" + to_string(vCurrencyData.size()) + ") Currency.";
		drawScreenHeader(Title, SubTitle);

		cout << endl;
		cout << setw(8) << left << "" << "___________________________________________________";
		cout << "________________________________________________\n\n";
		cout << setw(8) << left << "" << "| " << setw(36) << left << "Country";
		cout << "| " << setw(10) << left << "Code";
		cout << "| " << setw(36) << left << "Name";
		cout << "| " << setw(10) << left << "Rate/(1$)";
		cout << "\n";
		cout << setw(8) << left << "" << "___________________________________________";
		cout << "________________________________________________________\n\n";

		if (vCurrencyData.size() == 0)
			cout << "\t\t\t\tNo Currencies Available In The System!";

		for (clsCurrency Currency : vCurrencyData)
		{
			printCurrencyRecordLine(Currency);
		}

		cout << setw(8) << left << "" << "___________________________________________";
		cout << "________________________________________________________\n\n";
	}
};

