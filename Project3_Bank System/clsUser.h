#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "clsPerson.h"
#include "clsInputValidate.h"
#include "clsString.h"
#include "clsUtil.h"

using namespace std;

class clsUser : public clsPerson 
{
private:
	enum enMode
	{
		EmptyMode = 0, UpdateMode = 1, AddNewMode = 2
	};

	enMode mode;
	string userName;
	string password;
	short permissions;

	bool markedForDeleted = false;
	struct stLoginRegisterRecord;

	static clsUser convertLineToUserObject(string line, string separator = "#//#")
	{
		vector <string> vUserData = clsString::Split(line, separator);
		return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2], vUserData[3], vUserData[4], clsUtil::DecryptText(vUserData[5], 5), stoi(vUserData[6]));
	}

	static string convertUerObjectToLine(clsUser User, string separator = "#//#")
	{
		return User.FirstName + separator + User.LastName + separator + User.Email + separator + User.Phone + separator + User.UserName + separator + clsUtil::EncryptText(User.Password, 5) + separator + to_string(User.permissions);
	}
	
	static stLoginRegisterRecord convertLoginRegisterLineToRecord(string sLine, string separator = "#//#")
	{
		stLoginRegisterRecord LoginRegisterRecord;
		vector <string> vString = clsString::Split(sLine, separator);
		LoginRegisterRecord.DateTime = vString[0];
		LoginRegisterRecord.UserName = vString[1];
		LoginRegisterRecord.Password = clsUtil::DecryptText(vString[2], 5);
		LoginRegisterRecord.Permissions = stoi(vString[3]);
		return LoginRegisterRecord;
	}

	static vector <clsUser> loadUserDateFromFile()
	{
		vector <clsUser> vUsers;

		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsUser User = convertLineToUserObject(Line);
				vUsers.push_back(User);
			}

			MyFile.close();
		}

		return vUsers;
	}

	static void saveUserDataToFile(vector <clsUser> vUsers)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::out);

		if (MyFile.is_open())
		{
			for (clsUser User : vUsers)
			{
				string Line = convertUerObjectToLine(User);

				if (User.GetMarkedForDeleted() == false)
				{
					MyFile << Line << endl;
				}
			}

			MyFile.close();
		}
	}

	void update()
	{
		vector <clsUser> vUsers = loadUserDateFromFile();

		for (clsUser& User : vUsers)
		{
			if (User.GetUserName() == GetUserName())
			{
				User = *this;
				saveUserDataToFile(vUsers);
				break;
			}
		}
	}

	void addNew()
	{
		addDataLineToFile(convertUerObjectToLine(*this));
	}

	void addDataLineToFile(string stDataLine)
	{
		fstream MyFile;

		MyFile.open("Users.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << stDataLine << endl;

			MyFile.close();
		}
	}

	static clsUser getEmptyUserObject()
	{
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	string prepareLogInRecord(string separator = "#//#")
	{
		return clsDate::GetSystemDateTimeString() + separator + UserName + separator + clsUtil::EncryptText(Password, 5) + separator + to_string(Permissions);
	}

public:
	enum enPermissions
	{
		eAll = -1, pListClients = 1, pAddNewClient = 2, 
		pDeleteClient = 4, pUpdateClient = 8, pFindClient = 16, 
		pTransaction = 32, pManageUsers = 64, pShowLogInRegister = 128
	};

	clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone, string UserName, string Password, int Permissions)
		: clsPerson(FirstName, LastName, Email, Phone)
	{
		mode = Mode;
		userName = UserName;
		password = Password;
		permissions = Permissions;
	}

	struct stLoginRegisterRecord
	{
		string DateTime;
		string UserName;
		string Password;
		int Permissions;
	};

	bool IsEmpty()
	{
		return (mode == enMode::EmptyMode);
	}

	bool GetMarkedForDeleted()
	{
		return markedForDeleted;
	}

	void SetUserName(string UserName)
	{
		userName = UserName;
	}

	string GetUserName()
	{
		return userName;
	}

	__declspec(property(get = GetUserName, put = SetUserName)) string UserName;
	
	void SetPassword(string Password)
	{
		password = Password;
	}

	string GetPassword()
	{
		return password;
	}

	__declspec(property(get = GetPassword, put = SetPassword)) string Password;

	void SetPermissions(int Permissions)
	{
		permissions = Permissions;
	}

	int GetPermissions()
	{
		return permissions;
	}

	__declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

	static clsUser Find(string UserName)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);
		if(MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsUser User = convertLineToUserObject(Line);

				if (User.GetUserName() == UserName)
				{
					MyFile.close();
					return User;
				}
			}	
			MyFile.close();
		}
		return getEmptyUserObject();
	}

	static clsUser Find(string UserName, string Password)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsUser User = convertLineToUserObject(Line);

				if (User.GetUserName() == UserName && User.GetPassword() == Password)
				{
					MyFile.close();
					return User;
				}
			}
			MyFile.close();
		}
		return getEmptyUserObject();
	}

	enum enSaveResults { svFailedEmptyObject = 0, svSucceded = 1, svFailedUserExists = 2 };

	enSaveResults Save()
	{
		switch (mode)
		{
		case enMode::EmptyMode:
			return enSaveResults::svFailedEmptyObject;
			break;

		case enMode::UpdateMode:
			update();
			return enSaveResults::svSucceded;
			break;

		case enMode::AddNewMode:
		{
			if (IsUserExist(userName))
			{
				enSaveResults::svFailedUserExists;
			}
			else
			{
				addNew();
				mode = enMode::UpdateMode;
				return enSaveResults::svSucceded;
			}
		}
		}
	}

	static bool IsUserExist(string UserName)
	{
		clsUser User = clsUser::Find(UserName);
		return (!User.IsEmpty());
	}

	bool Delete()
	{
		vector <clsUser> vUsers = loadUserDateFromFile();

		for (clsUser& User : vUsers)
		{
			if (User.GetUserName() == GetUserName())
			{
				User.markedForDeleted = true;
				*this = getEmptyUserObject();
				saveUserDataToFile(vUsers);
				return true;
			}
		}

		return false;
	}


	static vector <clsUser> GetUsersList()
	{
		return loadUserDateFromFile();
	}

	static vector <stLoginRegisterRecord> GetLoginRegisterList()
	{
		vector <stLoginRegisterRecord> vLoginRegisterRecord;
		stLoginRegisterRecord LoginRegisterRecord;
		
		fstream MyFile;
		MyFile.open("LoginRegister.txt", ios::in);
		if (MyFile.is_open())
		{
			string sLine;
			while (getline(MyFile, sLine))
			{
				LoginRegisterRecord = convertLoginRegisterLineToRecord(sLine);
				vLoginRegisterRecord.push_back(LoginRegisterRecord);
			}

			MyFile.close();
		}

		return vLoginRegisterRecord;
	}

	static clsUser GetAddNewUserObject(string UserName)
	{
		return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}

	bool CheckAccessPermissions(enPermissions Permissions)
	{
		if (this->Permissions == enPermissions::eAll)
			return true;
		else
		{
			if ((this->Permissions & Permissions) == Permissions)
				return true;
			else
				return false;
		}
	}

	void SaveRegisterLogIn()
	{
		string stCurrentDataLine = prepareLogInRecord();
		
		fstream MyFile;
		MyFile.open("LoginRegister.txt", ios::out | ios::app);
		if (MyFile.is_open())
		{
			MyFile << stCurrentDataLine << endl;
			MyFile.close();
		}
	}

};

