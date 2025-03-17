#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include "clsDate.h"

using namespace std;

class clsUtil
{
public:
	enum enCharType 
	{
		SmallLetter = 1, CapitalLetter= 2, Digit = 3,
		MixCharacter = 4, SpecialCharacter = 5
	};

	static void Srand()
	{
		srand((unsigned)time(NULL));
	}

	static int RandomNumber(int From, int To)
	{
		int RandNum = rand() % (To - From + 1) + From;
		return RandNum;
	}

	static char GetRandomCharacter(enCharType CharType)
	{
		if (CharType == enCharType::MixCharacter)
		{
			CharType = (enCharType)RandomNumber(1, 3);
		}

		switch (CharType)
		{
		case enCharType::SmallLetter:
			return RandomNumber(97, 122);
			break;
		case enCharType::CapitalLetter:
			return RandomNumber(65, 90);
			break;
		case enCharType::Digit:
			return RandomNumber(48, 57);
			break;
		case enCharType::SpecialCharacter:
			return RandomNumber(33, 47);
			break;
		default:
			return RandomNumber(65, 90);
			break;
		}
	}

	static string GenerateWord(enCharType CharType, short Length)
	{
		string sWord;

		for (int i = 0; i < Length; ++i)
		{
			sWord += GetRandomCharacter(CharType);
		}

		return sWord;
	}

	static string GenerateKey(enCharType CharType = enCharType::CapitalLetter)
	{
		string Key;

		Key += GenerateWord(CharType, 4) + "-";
		Key += GenerateWord(CharType, 4) + "-";
		Key += GenerateWord(CharType, 4) + "-";
		Key += GenerateWord(CharType, 4);

		return Key;
	}

	static void GenerateKeys(short NumOfKeys, enCharType CharType)
	{
		for (short i = 1; i <= NumOfKeys; ++i)
		{
			cout << "Key [" << i << "] : " << GenerateKey(CharType) << endl;
		}
	}

	static void FillArrayWithRandomNumbers(int Arr[], int arrLength, int From, int To)
	{
		Arr[arrLength];

		for (int i = 0; i < arrLength; ++i)
		{
			Arr[i] = RandomNumber(From, To);
		}
	}

	static void FillArrayWithRandomWords(string Arr[], int arrLength, enCharType CharType, short WordLength)
	{
		Arr[arrLength];

		for (int i = 0; i < arrLength; ++i)
		{
			Arr[i] = GenerateWord(CharType, WordLength);
		}
	}

	static void FillArrayWithRandomKeys(string Arr[], int arrLength, enCharType CharType)
	{
		Arr[arrLength];

		for (int i = 0; i < arrLength; ++i)
		{
			Arr[i] = GenerateKey(CharType);
		}
	}

	static void Swap(int& Num1, int& Num2)
	{
		int Temp = Num1;
		Num1 = Num2;
		Num2 = Temp;
	}

	static void Swap(double& Num1, double& Num2)
	{
		double Temp = Num1;
		Num1 = Num2;
		Num2 = Temp;
	}

	static void Swap(bool& B1, bool& B2)
	{
		bool Temp = B1;
		B1 = B2;
		B2 = Temp;
	}

	static void Swap(char& C1, char& C2)
	{
		char Temp = C1;
		C1 = C2;
		C2 = Temp;
	}

	static void Swap(string& S1, string& S2)
	{
		string Temp = S1;
		S1 = S2;
		S2 = Temp;
	}

	static void Swap(clsDate& Date1, clsDate& Date2)
	{
		clsDate::SwapDates(Date1, Date2);
	}

	static void ShuffleArray(int Arr[], int arrLength)
	{
		for (int i = 0; i < arrLength; ++i)
		{
			Swap(Arr[RandomNumber(0, arrLength - 1)], Arr[RandomNumber(0, arrLength - 1)]);
		}
	}

	static void ShuffleArray(string Arr[], int arrLength)
	{
		for (int i = 0; i < arrLength; ++i)
		{
			Swap(Arr[RandomNumber(0, arrLength - 1)], Arr[RandomNumber(0, arrLength - 1)]);
		}
	}

	static string Tabs(short NumOfTabs)
	{
		string sTabs;

		for (short i = 0; i < NumOfTabs; ++i)
		{
			sTabs += "\t";
		}

		return sTabs;
	}

	static string EncryptText(string Text, short EncryptKey = 2)
	{
		for (int i = 0; i < Text.length(); ++i)
		{
			Text[i] = char((int)Text[i] + EncryptKey);
		}

		return Text;
	}

	static string DecryptText(string Text, short EncryptKey = 2)
	{
		for (int i = 0; i < Text.length(); ++i)
		{
			Text[i] = char((int)Text[i] - EncryptKey);
		}

		return Text;
	}

	static string NumberToText(int Number)
	{
		if (Number == 0)
		{
			return "";
		}

		if (Number >= 1 && Number <= 19)
		{
			string arr[] = { "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight",
				"Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen",
				"Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen" };
			return arr[Number] + " ";
		}

		if (Number >= 20 && Number <= 99)
		{
			string arr[] = { "", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety" };
			return arr[Number / 10] + " " + NumberToText(Number % 10);
		}

		if (Number >= 100 && Number <= 199)
		{
			return "One Hundred " + NumberToText(Number % 100);
		}

		if (Number >= 200 && Number <= 999)
		{
			return NumberToText(Number / 100) + "Hundreds " + NumberToText(Number % 100);
		}

		if (Number >= 1000 && Number < 1999)
		{
			return "One Thousand " + NumberToText(Number % 1000);
		}

		if (Number >= 2000 && Number <= 999999)
		{
			return NumberToText(Number / 1000) + "Thousands " + NumberToText(Number % 1000);
		}

		if (Number >= 1000000 && Number <= 1999999)
		{
			return "One Million " + NumberToText(Number % 1000000);
		}

		if (Number >= 2000000 && Number <= 999999999)
		{
			return NumberToText(Number / 1000000) + "Millions " + NumberToText(Number % 1000000);
		}

		if (Number >= 1000000000 && Number <= 1999999999)
		{
			return "One Billion " + NumberToText(Number % 1000000000);
		}

		else
		{
			return NumberToText(Number / 1000000000) + "Billions " + NumberToText(Number % 1000000000);
		}
	}
	
};

