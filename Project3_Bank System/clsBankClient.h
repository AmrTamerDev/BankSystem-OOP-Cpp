#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"
using namespace std;

class clsBankClient : public clsPerson
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode mode;

	string accountNumber;
	string pinCode;
	double accountBalance;
	bool markedForDeleted = false;

	struct stTransferLogRecord;

	static clsBankClient covertLineToClientObject(string Line, string Separator = "#//#")
	{
		vector <string> vClientData = clsString::Split(Line, Separator);
		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
	}

	static string convertClientObjectToLine(clsBankClient Client, string Separator = "#//#")
	{
		return Client.FirstName + Separator + Client.LastName + Separator + Client.Email + Separator + Client.Phone + Separator + Client.GetAccountNumber() + Separator + Client.PinCode + Separator + to_string(Client.AccountBalance);
	}

	static clsBankClient getEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static vector <clsBankClient> loadClientDataFromFile()
	{
		vector <clsBankClient> vClients;
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = covertLineToClientObject(Line);
				vClients.push_back(Client);
			}
			MyFile.close();
		}

		return vClients;
	}

	static void saveClientDataToFile(vector <clsBankClient> Clients)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out);

		if (MyFile.is_open())
		{
			for (clsBankClient& Client : Clients)
			{
				if (Client.GetMarkedForDeleted() == false)
				{
					string Line = convertClientObjectToLine(Client);
					MyFile << Line << endl;
				}
			}

			MyFile.close();
		}
	}

	void update()
	{
		vector <clsBankClient> vClients;
		vClients = loadClientDataFromFile();

		for (clsBankClient& Client : vClients)
		{
			if (Client.GetAccountNumber() == GetAccountNumber())
			{
				Client = *this;
				saveClientDataToFile(vClients);
				break;
			}
		}
	}

	void addNewLineToFile(string newLine)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << newLine << endl;
			MyFile.close();
		}
	}

	void addNewClient()
	{
		addNewLineToFile(convertClientObjectToLine(*this));
	}

	void convertToEmptyObject(clsBankClient& Client)
	{
		Client.mode = enMode::EmptyMode;
		Client.FirstName = "";
		Client.LastName = "";
		Client.Email = "";
		Client.Phone = "";
		Client.accountNumber = "";
		Client.PinCode = "";
		Client.AccountBalance = 0;
	}

	string prepareTransferLogRecord(double amount, clsBankClient receiverClient, string userName, string separator = "#//#")
	{
		return clsDate::GetSystemDateTimeString() + separator + GetAccountNumber() + separator + receiverClient.GetAccountNumber() + separator + to_string(amount) + separator + to_string(AccountBalance) + separator + to_string(receiverClient.AccountBalance) + separator + userName;
	}

	void registerTransferLog(double amount, clsBankClient receiverClient, string userName)
	{

		fstream MyFile;
		string stTransferLogData = prepareTransferLogRecord(amount, receiverClient, userName);

		MyFile.open("TransferLog.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << stTransferLogData << endl;

			MyFile.close();
		}
	}

	static stTransferLogRecord convertTransferLogLineToRecord(string sLine)
	{
		stTransferLogRecord TransferLog;
		vector <string> vDataLineTransferLog = clsString::Split(sLine, "#//#");
		
		TransferLog.DataTime = vDataLineTransferLog[0];
		TransferLog.SenderAccount = vDataLineTransferLog[1];
		TransferLog.ReceiverAccount = vDataLineTransferLog[2];
		TransferLog.Amount = stod(vDataLineTransferLog[3]);
		TransferLog.SenderBalanceAfterTransfer = stod(vDataLineTransferLog[4]);
		TransferLog.ReceiverBalanceAfterTransfer = stod(vDataLineTransferLog[5]);
		TransferLog.UserName = vDataLineTransferLog[6];
		
		return TransferLog;
	}

public:

	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, double AccountBalance)
		: clsPerson(FirstName, LastName, Email, Phone)
	{
		mode = Mode;
		accountNumber = AccountNumber;
		pinCode = PinCode;
		accountBalance = AccountBalance;
	}

	struct stTransferLogRecord
	{
		string DataTime;
		string SenderAccount;
		string ReceiverAccount;
		double Amount;
		double SenderBalanceAfterTransfer;
		double ReceiverBalanceAfterTransfer;
		string UserName;
	};

	bool IsEmpty()
	{
		return (mode == enMode::EmptyMode);
	}

	bool GetMarkedForDeleted()
	{
		return markedForDeleted;
	}

	//Read Only property all property can modify but AccountNumber Not it take a unique Account number when create account in Bank
	string GetAccountNumber()
	{
		return accountNumber;
	}

	void SetPinCode(string PinCode)
	{
		pinCode = PinCode;
	}

	string GetPinCode()
	{
		return pinCode;
	}

	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	void SetAccountBalance(double AccountBalance)
	{
		accountBalance = AccountBalance;
	}

	double GetAccountBalance()
	{
		return accountBalance;
	}

	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) double AccountBalance;

	/*
	No UI Related code inside object
	void Print()
	{
		cout << "\n\t\tClient Card";
		cout << "\n========================================";
		cout << "\nFirst Name     : " << FirstName;
		cout << "\nLast Name      : " << LastName;
		cout << "\nEmail          : " << Email;
		cout << "\nPhone          : " << Phone;
		cout << "\nFull Name      : " << GetFullName();
		cout << "\nAccount Number : " << accountNumber;
		cout << "\nPin Code       : " << pinCode;
		cout << "\nAccount Balance: " << accountBalance;
		cout << "\n========================================\n";
	}*/

	static clsBankClient Find(string AccountNumber)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = covertLineToClientObject(Line, "#//#");
				if (Client.GetAccountNumber() == AccountNumber)
				{
					MyFile.close();
					return Client;
				}
			}
			MyFile.close();
		}

		return getEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string PinCode)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = covertLineToClientObject(Line, "#//#");
				if (Client.GetAccountNumber() == AccountNumber && Client.GetPinCode() == PinCode)
				{
					MyFile.close();
					return Client;
				}
			}
			MyFile.close();
		}

		return getEmptyClientObject();
	}

	static bool IsClientExist(string AccountNumber)
	{
		//Find inside this class I Can Call it Find() without clsBankClient::Find()
		clsBankClient Client = Find(AccountNumber);
		return (!Client.IsEmpty());
	}

	enum enSaveResult { svFailedEmptyObject = 0, svSucceeded = 1, svFailedAccountNumberExists = 2 };

	enSaveResult Save()
	{
		switch (mode)
		{
		case enMode::EmptyMode:
			return enSaveResult::svFailedEmptyObject;
			break;

		case enMode::UpdateMode:
			update();
			return enSaveResult::svSucceeded;
			break;

		case enMode::AddNewMode:
		{
			if (IsClientExist(accountNumber))
			{
				return enSaveResult::svFailedAccountNumberExists;
			}
			else
			{
				addNewClient();
				mode = enMode::UpdateMode;
				return enSaveResult::svSucceeded;
			}
		}

		}
	}

	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	bool Delete()
	{
		vector <clsBankClient> vClients = loadClientDataFromFile();
		for (clsBankClient& Client : vClients)
		{
			if (Client.GetAccountNumber() == GetAccountNumber())
			{
				Client.markedForDeleted = true;
				*this = getEmptyClientObject();
				saveClientDataToFile(vClients);
				return true;
			}
		}
		return false;
	}

	static vector <clsBankClient> GetClientsList()
	{
		return loadClientDataFromFile();
	}

	static double GetTotalBalances()
	{
		double TotalBalances = 0;
		vector <clsBankClient> vClients = loadClientDataFromFile();

		for (clsBankClient Client : vClients)
		{
			TotalBalances += Client.AccountBalance;
		}

		return TotalBalances;
	}

	void Deposit(double DepositAmount)
	{
		AccountBalance += DepositAmount;
		Save();
	}

	bool WithDraw(double WithDrawAmount)
	{
		if (WithDrawAmount > AccountBalance)
		{
			return false;
		}
		else
		{
			AccountBalance -= WithDrawAmount;
			Save();
			return true;
		}
	}

	bool Transfer(double Amount, clsBankClient& ReceiverClient, string UserName)
	{
		if (Amount > AccountBalance)
		{
			return false;
		}

		WithDraw(Amount);
		ReceiverClient.Deposit(Amount);
		registerTransferLog(Amount, ReceiverClient, UserName);

		return true;
	}

	static vector <stTransferLogRecord> GetTransferLogList()
	{
		vector <stTransferLogRecord> vDataTransferLog;
		stTransferLogRecord TransferLog;

		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::in);

		if (MyFile.is_open())
		{
			string sLine;
			while (getline(MyFile, sLine))
			{
				TransferLog = convertTransferLogLineToRecord(sLine);
				vDataTransferLog.push_back(TransferLog);
			}
			MyFile.close();
		}

		return vDataTransferLog;
	}
};

