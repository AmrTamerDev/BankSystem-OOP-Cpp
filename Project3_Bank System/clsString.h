#pragma once
#include <iostream>
#include <vector>
using namespace std;

class clsString
{
private:
	string value;

public:
	clsString()
	{
		value = "";
	}

	clsString(string Value)
	{
		value = Value;
	}

	void SetValue(string Value)
	{
		value = Value;
	}

	string GetValue()
	{
		return value;
	}

	__declspec(property(get = GetValue, put = SetValue)) string Value;

	static short Length(string FillName)
	{
		return (short)FillName.length();
	}

	short Length()
	{
		return Length(value);
	}

	static void PrintFirstLetterOfEachWord(string FillString)
	{
		cout << "\nFirst letters of this string: \n";

		bool isFirstLetter = true;

		for (short i = 0; i < FillString.length(); i++)
		{
			if (FillString[i] != ' ' && isFirstLetter)
			{
				cout << FillString[i] << endl;
			}

			isFirstLetter = (FillString[i] == ' ' ? true : false);
		}
	}

	void PrintFirstLetterOfEachWord()
	{
		PrintFirstLetterOfEachWord(value);
	}

	static string UpperFirstLetterOfEachWord(string FillString)
	{
		bool isFirstElement = true;

		for (short i = 0; i < FillString.length(); ++i)
		{
			if (FillString[i] != ' ' && isFirstElement)
			{
				FillString[i] = toupper(FillString[i]);
			}

			isFirstElement = (FillString[i] == ' ' ? true : false);
		}
		return FillString;
	}

	void UpperFirstLetterOfEachWord()
	{
		value = UpperFirstLetterOfEachWord(value);
	}

	static string LowerFirstLetterOfEachWord(string FillString)
	{
		bool isFirstElement = true;

		for (short i = 0; i < FillString.length(); ++i)
		{
			if (FillString[i] != ' ' && isFirstElement)
			{
				FillString[i] = tolower(FillString[i]);
			}

			isFirstElement = (FillString[i] == ' ' ? true : false);
		}

		return FillString;
	}

	void LowerFirstLetterOfEachWord()
	{
		value = LowerFirstLetterOfEachWord(value);
	}

	static string UpperAllString(string FillString)
	{
		for (short i = 0; i < FillString.length(); ++i)
		{
			FillString[i] = toupper(FillString[i]);
		}

		return FillString;
	}

	void UpperAllString()
	{
		value = UpperAllString(value);
	}

	static string LowerAllString(string FillString)
	{
		for (short i = 0; i < FillString.length(); ++i)
		{
			FillString[i] = tolower(FillString[i]);
		}

		return FillString;
	}

	void LowerAllString()
	{
		value = LowerAllString(value);
	}

	static char InvertLetterCase(char EachCharacter)
	{
		return isupper(EachCharacter) ? tolower(EachCharacter) : toupper(EachCharacter);
	}

	static string InvertAllStringLettersCase(string FillString)
	{

		for (short i = 0; i < FillString.length(); ++i)
		{
			FillString[i] = InvertLetterCase(FillString[i]);
		}

		return FillString;
	}

	void InvertAllStringLettersCase()
	{
		value = InvertAllStringLettersCase(value);
	}

	enum enWhatToCount { LowerCase = 0, UpperCase = 1, All = 3 };

	static short CountLetterInAllCase(string FillString, enWhatToCount WhatCount = enWhatToCount::All)
	{
		if (WhatCount == enWhatToCount::All)
		{
			return (short)FillString.length();
		}
		short Counter = 0;

		for (short i = 0; i < FillString.length(); ++i)
		{

			if (WhatCount == enWhatToCount::UpperCase && isupper(FillString[i]))
			{
				++Counter;
			}
			if (WhatCount == enWhatToCount::LowerCase && islower(FillString[i]))
			{
				++Counter;
			}
		}

		return Counter;
	}

	short CountLetterInAllCase()
	{
		return CountLetterInAllCase(value);
	}

	static short CountUpperCaseLetters(string FillString)
	{
		short Counter = 0;

		for (short i = 0; i < FillString.length(); ++i)
		{
			if (isupper(FillString[i]))
				++Counter;
		}

		return Counter;
	}

	short CountUpperCaseLetters()
	{
		return CountUpperCaseLetters(value);
	}

	static short CountLowerCaseLetters(string FillString)
	{
		short Counter = 0;

		for (short i = 0; i < FillString.length(); ++i)
		{
			if (islower(FillString[i]))
				++Counter;
		}

		return Counter;
	}

	short CountLowerCaseLetters()
	{
		return CountLowerCaseLetters(value);
	}

	static short CountTheCharacterInString(string FillString, char Character)
	{
		short Counter = 0;

		for (short i = 0; i < FillString.length(); ++i)
		{
			if (FillString[i] == Character)
				++Counter;
		}

		return Counter;
	}

	short CountTheCharacterInString(char Character)
	{
		return CountTheCharacterInString(value, Character);
	}

	static short CountLetter(string FillString, char Character, bool MatchCase = true)
	{
		short Counter = 0;

		for (short i = 0; i < FillString.length(); ++i)
		{
			if (MatchCase)
			{
				if (FillString[i] == Character)
					++Counter;
			}
			else
			{
				if (tolower(FillString[i]) == tolower(Character))
					++Counter;
			}
		}

		return Counter;
	}

	short CountLetter(char Character, bool MatchCase = true)
	{
		return CountLetter(value, Character, MatchCase);
	}

	static bool IsVowel(char Ch)
	{
		Ch = tolower(Ch);
		return ((Ch == 'a') || (Ch == 'e') || (Ch == 'i') || (Ch == 'o') || (Ch == 'u'));
	}

	static short CountVowels(string S)
	{
		short Counter = 0;

		for (short i = 0; i < S.length(); ++i)
		{
			if (IsVowel(S[i]))
				++Counter;
		}

		return Counter;
	}

	short CountVowels()
	{
		return CountVowels(value);
	}

	static void PrintVowels(string S)
	{
		cout << "\nVowels in string are: ";

		for (short i = 0; i < S.length(); ++i)
		{
			if (IsVowel(S[i]))
				cout << S[i] << "    ";
		}
		cout << endl;
	}

	void PrintVowels()
	{
		PrintVowels(value);
	}

	static void PrintEachWordInString(string S)
	{
		string delim = " "; //delimite
		string sWord = "";
		size_t Pos = 0; //Position

		cout << "\nYour string words are: \n\n";

		while ((Pos = S.find(delim)) != S.npos)
		{
			sWord = S.substr(0, Pos);

			if (sWord != "")
			{
				cout << sWord << endl;
			}

			S.erase(0, Pos + delim.length());

		}

		if (S != "")
			cout << S << endl;
	}

	void PrintEachWordInString()
	{
		PrintEachWordInString(value);
	}

	static short CountWords(string S)
	{
		string sWord = "";
		string delim = " ";
		size_t Pos = 0;
		short Counter = 0;

		while ((Pos = S.find(delim)) != S.npos)
		{
			sWord = S.substr(0, Pos);

			if (sWord != "")
			{
				++Counter;
			}

			S.erase(0, Pos + delim.length());
		}

		if (S != "")
			++Counter;

		return Counter;
	}

	short CountWords()
	{
		return CountWords(value);
	}

	static vector <string> Split(string S, string Delim)
	{
		vector <string> vString;
		string sWord = "";
		short Pos = 0;

		while ((Pos = (short)S.find(Delim)) != S.npos)
		{
			sWord = S.substr(0, Pos);

			if (sWord != "")
			{
				vString.push_back(sWord);
			}
			S.erase(0, Pos + Delim.length());
		}

		if (S != "")
			vString.push_back(S);

		return vString;
	}

	vector <string> Split(string Delim)
	{
		return Split(value, Delim);
	}

	static string TrimLeft(string S)
	{
		for (short i = 0; i < S.length(); i++)
		{
			if (S[i] != ' ')
			{
				return S.substr(i, S.length() - i);
			}
		}

		return "";

	}

	void TrimLeft()
	{
		value = TrimLeft(value);
	}

	static string TrimRight(string S)
	{
		for (short i = (short)S.length() - 1; i >= 0; i--)
		{
			if (S[i] != ' ')
			{
				return S.substr(0, i + 1);
			}
		}

		return "";
	}

	void TrimRight()
	{
		value = TrimRight(value);
	}

	static string Trim(string S)
	{
		return (TrimLeft(TrimRight(S)));
	}

	void Trim()
	{
		value = Trim(value);
	}

	static string JoinString(vector <string> vString, string Delim)
	{
		string S1 = "";
		for (string& S : vString)
		{
			S1 += S + Delim;
		}

		return S1.substr(0, S1.length() - Delim.length());
	}

	static string JoinString(string arrString[], short Length, string Delim)
	{
		string S1 = "";

		for (short i = 0; i < Length; ++i)
		{
			S1 += arrString[i] + Delim;
		}

		return S1.substr(0, S1.length() - Delim.length());
	}

	static string ReversWordsInString(string S)
	{
		vector <string> vStrings = Split(S, " ");
		vector <string>::iterator iter = vStrings.end();
		string S2 = "";

		while (iter != vStrings.begin())
		{
			--iter;
			S2 += *iter + " ";
		}
		S2 = S2.substr(0, S2.length() - 1);

		return S2;
	}

	void ReversWordsInString()
	{
		value = ReversWordsInString(value);
	}

	static string ReplaceWordInStringUsingSplit(string S, string StringReplace, string sReplaceTo, bool MatchCase = true)
	{
		vector<string> vStrings = Split(S, " ");

		for (string& sWord : vStrings)
		{
			if (MatchCase)
			{
				if (sWord == StringReplace)
					sWord = sReplaceTo;
			}
			else
			{
				if (LowerAllString(sWord) == LowerAllString(StringReplace))
					sWord = sReplaceTo;
			}
		}

		return JoinString(vStrings, " ");
	}

	void ReplaceWordInStringUsingSplit(string StringReplace, string sReplaceTo, bool MatchCase = true)
	{
		value = ReplaceWordInStringUsingSplit(value, StringReplace, sReplaceTo, MatchCase);
	}

	static string RemovePunctuationsFromString(string S)
	{
		string S2 = "";

		for (short i = 0; i < S.length(); ++i)
		{
			if (!ispunct(S[i]))
				S2 += S[i];
		}

		return S2;
	}

	void RemovePunctuationsFromString()
	{
		value = RemovePunctuationsFromString(value);
	}
};



