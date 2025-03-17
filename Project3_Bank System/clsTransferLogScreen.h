#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"

class clsTransferLogScreen : protected clsScreen
{
private:
	static void printTransferRecordLine(clsBankClient::stTransferLogRecord TransferLog)
	{
		cout << setw(8) << left << "" << "| " << setw(25) << left << TransferLog.DataTime;
		cout << "| " << setw(10) << left << TransferLog.SenderAccount;
		cout << "| " << setw(10) << left << TransferLog.ReceiverAccount;
		cout << "| " << setw(10) << left << TransferLog.Amount;
		cout << "| " << setw(10) << left << TransferLog.SenderBalanceAfterTransfer;
		cout << "| " << setw(10) << left << TransferLog.ReceiverBalanceAfterTransfer;
		cout << "| " << setw(10) << left << TransferLog.UserName;
		cout << "\n";
	}

public:

	static void ShowTransferLogScreen()
	{
		vector <clsBankClient::stTransferLogRecord> vDataTransferLog = clsBankClient::GetTransferLogList();

		string Title = "\t  Transfer Log List Screen";
		string SubTitle = "\t       (" + to_string(vDataTransferLog.size()) + ") Record(s).";
		drawScreenHeader(Title, SubTitle);

		cout << endl;
		cout << setw(8) << left << "" << "___________________________________________________";
		cout << "_________________________________________________\n\n";
		cout << setw(8) << left << "" << "| " << setw(25) << left << "Date/Time";
		cout << "| " << setw(10) << left << "S.Acct";
		cout << "| " << setw(10) << left << "R.Acct";
		cout << "| " << setw(10) << left << "Amount";
		cout << "| " << setw(10) << left << "S.Balance";
		cout << "| " << setw(10) << left << "R.Balance";
		cout << "| " << setw(10) << left << "User";
		cout << "\n";
		cout << setw(8) << left << "" << "________________________________________";
		cout << "____________________________________________________________\n\n";

		if (vDataTransferLog.size() == 0)
			cout << "\t\t\t\tNo Transfer Available In The System!";

		for (clsBankClient::stTransferLogRecord TransferLog : vDataTransferLog)
		{
			printTransferRecordLine(TransferLog);
		}

		cout << "\n";
		cout << setw(8) << left << "" << "________________________________________";
		cout << "____________________________________________________________\n\n";
	}
};

