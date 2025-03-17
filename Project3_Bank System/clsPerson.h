#pragma once
#include <iostream>
using namespace std;
class clsPerson
{
private:
	string firstName;
	string lastName;
	string email;
	string phone;

public:

	clsPerson(string FirstName, string LastName, string Email, string Phone)
	{
		firstName = FirstName;
		lastName = LastName;
		email = Email;
		phone = Phone;
	}

	void SetFirstName(string FirstName)
	{
		firstName = FirstName;
	}

	string GetFirstName()
	{
		return firstName;
	}

	__declspec(property(get = GetFirstName, put = SetFirstName)) string FirstName;

	void SetLastName(string LastName)
	{
		lastName = LastName;
	}

	string GetLastName()
	{
		return lastName;
	}

	__declspec(property(get = GetLastName, put = SetLastName)) string LastName;

	void SetEmail(string Email)
	{
		email = Email;
	}

	string GetEmail()
	{
		return email;
	}

	__declspec(property(get = GetEmail, put = SetEmail)) string Email;

	void SetPhone(string Phone)
	{
		phone = Phone;
	}

	string GetPhone()
	{
		return phone;
	}

	__declspec(property(get = GetPhone, put = SetPhone)) string Phone;

	string GetFullName()
	{
		return firstName + " " + lastName;
	}

};

