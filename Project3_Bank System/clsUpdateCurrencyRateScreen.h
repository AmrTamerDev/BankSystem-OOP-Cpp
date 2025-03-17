#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"

class clsUpdateCurrencyRateScreen : protected clsScreen
{
private:
	static float readRate()
	{
		float Rate;

		cout << "\nEnter New Rate: ";
		Rate = clsInputValidate::ReadFloatNumber();

		return Rate;
	}

	static void printCurrencyCard(clsCurrency Currency)
	{
		cout << "\nCurrency Card:\n";
		cout << "====================================";
		cout << "\nCountry    : " << Currency.GetCountryName();
		cout << "\nCode       : " << Currency.GetCurrencyCode();
		cout << "\nName       : " << Currency.GetCurrencyName();
		cout << "\nRate(1$) = : " << Currency.GetCurrencyRate();
		cout << "\n====================================\n";
	}

public:

	static void ShowUpdateCurrencyRateScreen()
	{
		drawScreenHeader("\t   Update Currency Screen");
		
		string CurrencyCode;

		cout << "\nPlease Enter Currency Code: ";
		CurrencyCode = clsInputValidate::ReadString();

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		
		while (Currency.IsEmpty())
		{
			cout << "\nNot Correct Please Enter Correct Currency Code: ";
			CurrencyCode = clsInputValidate::ReadString();
			Currency = clsCurrency::FindByCode(CurrencyCode);
		}

		printCurrencyCard(Currency);

		char InputChoice = 'n';

		cout << "\nAre you sure you want to update the rate of this Currency y/n? ";
		cin >> InputChoice;

		if (toupper(InputChoice) == 'Y')
		{
			cout << "\nUpdate Currency Rate:\n";
			cout << "==========================\n";	
			Currency.UpdateRate(readRate());
			cout << "\nCurrency Rate Update Successfully :-)\n";
			printCurrencyCard(Currency);
		}
		
	}
};

