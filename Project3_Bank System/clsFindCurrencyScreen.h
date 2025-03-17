#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"

class clsFindCurrencyScreen : protected clsScreen
{
private:
	enum enFind
	{
		eCode = 1, eCountry = 2
	};

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

	static short ReadFindNumber()
	{
		short NumberChoice;

		cout << "\nFind By: [1] Code or [2] Country ? ";
		NumberChoice = clsInputValidate::ReadShortNumberBetween(1, 2, "Not Correct Enter [1] For Find By Code or [2] For Find By Country? ");

		return NumberChoice;
	}

	static void findByCode()
	{
		string Code;

		cout << "\nPlease Enter CurrencyCode: ";
		Code = clsInputValidate::ReadString();

		clsCurrency Currency = clsCurrency::FindByCode(Code);

		while (Currency.IsEmpty())
		{
			cout << "\nNot Correct Enter Again Code!: ";
			Code = clsInputValidate::ReadString();
			Currency = clsCurrency::FindByCode(Code);
		}

		cout << "\nCurrency Found :-)\n";
		printCurrencyCard(Currency);

	}

	static void findByCountry()
	{
		string CountryName;

		cout << "\nPlease Enter Country Name: ";
		CountryName = clsInputValidate::ReadString();

		clsCurrency Currency = clsCurrency::FindByCountry(CountryName);

		while (Currency.IsEmpty())
		{
			cout << "\nNot Correct Enter Again Country!: ";
			CountryName = clsInputValidate::ReadString();
			Currency = clsCurrency::FindByCountry(CountryName);
		}

		cout << "\nCurrency Found :-)\n";
		printCurrencyCard(Currency);
	}

public:
	static void ShowFindCurrencyScreen()
	{
		drawScreenHeader("\t   Find Currency Screen");
		enFind Find = (enFind)ReadFindNumber();

		switch (Find)
		{
		case enFind::eCode:
			findByCode();
			break;

		case enFind::eCountry:
			findByCountry();
			break;
		}
	}
};

