#pragma once
#include <iostream>
#include <string>
#include "clsDate.h"
#include "clsString.h"
using namespace std;

class clsInputValidate
{
public:

	static bool IsNumberBetween(short Num, short From, short To)
	{
		return (Num >= From && Num <= To);
	}

	static bool IsNumberBetween(int Num, int From, int To)
	{
		return (Num >= From && Num <= To);
	}

	static bool IsNumberBetween(float Num, float From, float To)
	{
		return (Num >= From && Num <= To);
	}

	static bool IsNumberBetween(double Num, double From, double To)
	{
		return (Num >= From && Num <= To);
	}

	static bool IsDateBetween(clsDate Date, clsDate DateFrom, clsDate DateTo)
	{
		return ((((clsDate::IsDate1AfterDate2(Date, DateFrom)) && (clsDate::IsDate1BeforeDate2(Date, DateTo)))
			||
			((clsDate::IsDate1BeforeDate2(Date, DateFrom)) && (clsDate::IsDate1AfterDate2(Date, DateTo))))
			||
			(clsDate::IsDate1EqualToDate2(Date, DateFrom))
			||
			(clsDate::IsDate1EqualToDate2(Date, DateTo))
			);
	}
	
	static short ReadShortNumber(string ErrorMessage = "Invalid Number, Enter again:\n")
	{
		double NumberRead;
		cin >> NumberRead;

		while (true)
		{
			if (!cin.fail())
			{
				// Implicit casting
				//return NumberRead;  // Automatically truncates the double to an int
				// Explicit truncation
				return static_cast<short>(NumberRead);
			}

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
			cin >> NumberRead;
		}

	}

	static short ReadShortNumberBetween(short From, short To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		short NumberRead = ReadShortNumber();

		while (!IsNumberBetween(NumberRead, From, To))
		{
			cout << ErrorMessage;
			NumberRead = ReadIntNumber();
		}

		return NumberRead;
	}

	static int ReadIntNumber(string ErrorMessage = "Invalid Number, Enter again:\n")
	{
		double NumberRead;
		cin >> NumberRead;

		while (true)
		{
			if (!cin.fail())
			{
				// Implicit casting
				//return NumberRead;  // Automatically truncates the double to an int
				// Explicit truncation
				return static_cast<int>(NumberRead);
			}

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
			cin >> NumberRead;
		}
		
	}

	static int ReadIntNumberBetween(int From, int To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		int NumberRead = ReadIntNumber();

		while (!IsNumberBetween(NumberRead, From, To))
		{
			cout << ErrorMessage;
			NumberRead = ReadIntNumber();
		}

		return NumberRead;
	}

	static float ReadFloatNumber(string ErrorMessage = "Invalid Number, Enter again :\n")
	{
		float NumberRead;
		cin >> NumberRead;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
			cin >> NumberRead;
		}

		return NumberRead;
	}

	static float ReadFloatNumberBetween(float From, float To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		float NumberRead = ReadFloatNumber();

		while (!IsNumberBetween(NumberRead, From, To))
		{
			cout << ErrorMessage << endl;
			cin >> NumberRead;
		}

		return NumberRead;
	}

	static double ReadDblNumber(string ErrorMessage = "Invalid Number, Enter again :\n")
	{
		double NumberRead;
		cin >> NumberRead;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
			cin >> NumberRead;
		}

		return NumberRead;
	}

	static double ReadDblNumberBetween(double From, double To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		double NumberRead = ReadDblNumber();

		while (!IsNumberBetween(NumberRead, From, To))
		{
			cout << ErrorMessage << endl;
			cin >> NumberRead;
		}

		return NumberRead;
	}

	static bool IsValidationDate(clsDate Date)
	{
		return clsDate::IsValidateDate(Date);
	}

	static string ReadString()
	{
		string sLine;
		getline(cin >> ws, sLine);
		return sLine;
	}
};

