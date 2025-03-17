#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "clsString.h"

class clsCurrency
{
private:
	enum enMode
	{
		eUpdateMode = 0, eEmptyMode = 1 
	};

	enMode mode;
	string countryName;
	string currencyCode;
	string currencyName;
	float currencyRate;

	static vector <clsCurrency> loadCurrencyDataFromFile()
	{
		vector <clsCurrency> vCurrencyData;

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open()) 
		{
			string sLine;
			while (getline(MyFile, sLine))
			{
				clsCurrency Currency = convertLineToCurrencyObject(sLine);
				vCurrencyData.push_back(Currency);
			}
			MyFile.close();
		}
		return vCurrencyData;
	}

	static void saveCurrencyDataToFile(vector <clsCurrency> vCurrencyData)
	{
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::out);
		if (MyFile.is_open())
		{
			for (clsCurrency Currency : vCurrencyData)
			{
				string sLine = convertCurrencyObjectToLine(Currency);
				MyFile << sLine << endl;
			}
			MyFile.close();
		}
	}

	static string convertCurrencyObjectToLine(clsCurrency currency, string separator = "#//#")
	{
		return currency.countryName + separator + currency.currencyCode + separator + currency.countryName + separator + to_string(currency.currencyRate);
	}

	void update()
	{
		vector <clsCurrency> vCurrencyData = loadCurrencyDataFromFile();
	
		for (clsCurrency& Currency : vCurrencyData)
		{
			if (currencyCode == Currency.currencyCode)
			{
				Currency = *this;
				break;
			}
		}

		saveCurrencyDataToFile(vCurrencyData);
	}

	static clsCurrency convertLineToCurrencyObject(string sLine, string separator = "#//#")
	{
		vector <string> vCurrencyData = clsString::Split(sLine, separator);
		return clsCurrency(enMode::eUpdateMode, vCurrencyData[0], vCurrencyData[1], vCurrencyData[2], stof(vCurrencyData[3]));
	}

	static clsCurrency getEmptyCurrencyObject()
	{
		return clsCurrency(enMode::eEmptyMode, "", "", "", 0);
	}

public:

	clsCurrency(enMode Mode, string CountryName, string CurrencyCode, string CurrencyName, float CurrencyRate)
	{
		mode = Mode;
		countryName = CountryName;
		currencyCode = CurrencyCode;
		currencyName = CurrencyName;
		currencyRate = CurrencyRate;
	}

	bool IsEmpty()
	{
		return (mode == enMode::eEmptyMode);
	}

	string GetCountryName()
	{
		return countryName;
	}

	string GetCurrencyCode()
	{
		return currencyCode;
	}

	string GetCurrencyName()
	{
		return currencyName;
	}

	float GetCurrencyRate()
	{
		return currencyRate;
	}

	void UpdateRate(float NewCurrencyRate)
	{
		currencyRate = NewCurrencyRate;
		update();
	}

	static clsCurrency FindByCode(string CurrencyCode)
	{
		CurrencyCode = clsString::UpperAllString(CurrencyCode);

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string sLine;
			while (getline(MyFile, sLine))
			{
				clsCurrency Currency = convertLineToCurrencyObject(sLine);

				if (Currency.GetCurrencyCode() == CurrencyCode)
				{
					MyFile.close();
					return Currency;
				}
			}
			MyFile.close();
		}

		return getEmptyCurrencyObject();
	}

	static clsCurrency FindByCountry(string CountryName)
	{
		fstream MyFile;
		CountryName = clsString::UpperAllString(CountryName);

		MyFile.open("Currencies.txt", ios::in);
		if (MyFile.is_open())
		{
			string sLine;
			while (getline(MyFile, sLine))
			{
				clsCurrency Currency = convertLineToCurrencyObject(sLine);
				
				if (clsString::UpperAllString(Currency.GetCountryName()) == CountryName)
				{
					MyFile.close();
					return Currency;
				}
			}

			MyFile.close();
		}

		MyFile.close();
		return getEmptyCurrencyObject();
	}

	static bool IsCurrencyExist(string CurrencyCode)
	{
		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		return (!Currency.IsEmpty());
	}

	static vector <clsCurrency> GetCurrencyList()
	{
		return loadCurrencyDataFromFile();
	}

	double ConvertToUSD(double Amount)
	{
		return Amount / (double)GetCurrencyRate();
	}

	double ConvertToAnotherCurrency(double Amount, clsCurrency CurrencyTo)
	{
		double AmountToUSA = ConvertToUSD(Amount);

		if (CurrencyTo.GetCurrencyCode() == "USD")
		{
			return AmountToUSA;
		}

		return AmountToUSA * CurrencyTo.GetCurrencyRate();
	}

	double ConvertFromUSDToAnotherCurrency(double Amount, clsCurrency CurrencyTo)
	{
		return Amount * (double)CurrencyTo.GetCurrencyRate();
	}
};

