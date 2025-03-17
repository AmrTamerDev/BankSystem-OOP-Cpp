#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"

class clsCurrencyCalculatorScreen : protected clsScreen
{
private:

	static double readAmount()
	{
		double Amount;

		cout << "\nEnter Amount To Exchange: ";
		Amount = clsInputValidate::ReadDblNumber();

		return Amount;
	}

	static void printCurrencyCard(clsCurrency Currency, string Text = "Convert From")
	{
		string S = "\n" + Text + ": \n";
		cout << S;
		cout << "====================================";
		cout << "\nCountry    : " << Currency.GetCountryName();
		cout << "\nCode       : " << Currency.GetCurrencyCode();
		cout << "\nName       : " << Currency.GetCurrencyName();
		cout << "\nRate(1$) = : " << Currency.GetCurrencyRate();
		cout << "\n====================================\n";
	}

	static clsCurrency getCurrency(string Message)
	{
		string CurrencyCode;

		cout << Message;
		CurrencyCode = clsInputValidate::ReadString();

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);

		while (Currency.IsEmpty())
		{
			cout << "\nNot Correct Please Enter Correct Currency Code: ";
			CurrencyCode = clsInputValidate::ReadString();
			Currency = clsCurrency::FindByCode(CurrencyCode);
		}

		return Currency;
	}

	static void printCalculationCurrencyFromTo(double Amount, clsCurrency CurrencyTransferFrom, clsCurrency CurrencyTransferTo)
	{
		double AmountInUSD;

		printCurrencyCard(CurrencyTransferFrom);

		if (CurrencyTransferFrom.GetCurrencyCode() == "USD")
		{
			double AmountTransferTo = CurrencyTransferTo.ConvertFromUSDToAnotherCurrency(Amount, CurrencyTransferTo);
			cout << Amount << " USD" << " = " << AmountTransferTo << " " << CurrencyTransferTo.GetCurrencyCode();
			return;
		}

		AmountInUSD = CurrencyTransferFrom.ConvertToUSD(Amount);
		cout << Amount << " " << CurrencyTransferFrom.GetCurrencyCode() << " = " << AmountInUSD << " SUD\n";

		if (CurrencyTransferTo.GetCurrencyCode() == "USD")
		{
			return;
		}
		cout << "\nConverting From USD To\n";
		printCurrencyCard(CurrencyTransferTo, "Convert To");

		double AmountTransfer = CurrencyTransferFrom.ConvertToAnotherCurrency(Amount, CurrencyTransferTo);

		cout << Amount << " " << CurrencyTransferFrom.GetCurrencyCode() << " = " << AmountTransfer << " " << CurrencyTransferTo.GetCurrencyCode() << endl;
	}

public:

	static void ShowCurrencyCalculatorScreen()
	{
		char Choice = 'Y';

		while (toupper(Choice) == 'Y')
		{
			system("cls");

			drawScreenHeader("\t   Calculator Currency Screen");

			clsCurrency CurrencyFrom = getCurrency("\nPlease Enter Currency Code To Convert From: ");
			clsCurrency CurrencyTo = getCurrency("\nPlease Enter Currency Code To Convert To: ");
			double Amount = readAmount();

			printCalculationCurrencyFromTo(Amount, CurrencyFrom, CurrencyTo);
			
			cout << "\n\nDo you want to perform another calculation? y/n? ";
			cin >> Choice;
		}
	}
};

