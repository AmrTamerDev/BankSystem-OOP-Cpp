#pragma once
#pragma warning (disable : 4996)
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "clsString.h"
using namespace std;

class clsDate
{
private:
	short day;
	short month;
	short year;

public:

	clsDate()
	{
		time_t t = time(0); //get time now
		tm* now = localtime(&t);

		year = now->tm_year + 1900;
		month = now->tm_mon + 1;
		day = now->tm_mday;
	}

	clsDate(string sDate)
	{
		vector <string> vDate = clsString::Split(sDate, "/");

		day = stoi(vDate[0]);
		month = stoi(vDate[1]);
		year = stoi(vDate[2]);
	}

	clsDate(short Day, short Month, short Year)
	{
		day = Day;
		month = Month;
		year = Year;
	}

	clsDate(short DateOrderInDay, short Year)
	{
		clsDate Date1 = GetDataFromBeginningYear(DateOrderInDay, Year);
		day = Date1.day;
		month = Date1.month;
		year = Date1.year;
	}

	void SetDay(short Day)
	{
		day = Day;
	}

	short GetDay()
	{
		return day;
	}

	__declspec(property(get = GetDay, put = SetDay)) short Day;

	void SetMonth(short Month)
	{
		month = Month;
	}

	short GetMonth()
	{
		return month;
	}

	__declspec(property(get = GetMonth, put = SetMonth)) short Month;

	void SetYear(short Year)
	{
		year = Year;
	}

	short GetYear()
	{
		return year;
	}

	__declspec(property(get = GetYear, put = SetYear)) short Year;

	void Print()
	{
		cout << DateToString() << endl;
	}

	static string DateToString(clsDate Date, string Separator = "/")
	{
		return to_string(Date.Day) + Separator + to_string(Date.Month) + Separator + to_string(Date.Year);
	}

	string DateToString()
	{
		return DateToString(*this);
	}

	static clsDate GetSystemDate()
	{
		time_t t = time(0); //get time now
		tm* now = localtime(&t);
		short Day, Month, Year;

		Year = now->tm_year + 1900;
		Month = now->tm_mon + 1;
		Day = now->tm_mday;

		return clsDate(Day, Month, Year);
	}

	static string GetSystemDateTimeString()
	{
		short Second, Minute, Hour, Day, Month, Year;
		time_t t = time(0);
		tm* now = localtime(&t);
		Year = now->tm_year + 1900;
		Month = now->tm_mon + 1;
		Day = now->tm_mday;
		Hour = now->tm_hour;
		Minute = now->tm_min;
		Second = now->tm_sec;
		return to_string(Day) + "/" + to_string(Month) + "/" + to_string(Year)
			+ " - " + to_string(Hour) + ":" + to_string(Minute) + ":" + to_string(Second);
	}

	static bool IsLeapYear(short Year)
	{
		return (Year % 400 == 0) || (Year % 4 == 0 && Year % 100 != 0);
	}

	bool IsLeapYear()
	{
		return IsLeapYear(year);
	}

	static short NumberOfDaysInYear(short YearNum)
	{
		return (IsLeapYear(YearNum)) ? 366 : 365;
	}

	short NumberOfDaysInYear()
	{
		return NumberOfDaysInYear(year);
	}

	static short NumberOfHoursInYear(short YearNum)
	{
		return NumberOfDaysInYear(YearNum) * 24;
	}

	short NumberOfHoursInYear()
	{
		return NumberOfHoursInYear(year);
	}

	static int NumberOfMinutesInYear(short YearNum)
	{
		return NumberOfHoursInYear(YearNum) * 60;
	}

	int NumberOfMinutesInYear()
	{
		return NumberOfMinutesInYear(year);
	}

	static int NumberOfSecondsInYear(short YearNum)
	{
		return NumberOfMinutesInYear(YearNum) * 60;
	}

	int NumberOfSecondsInYear()
	{
		return NumberOfSecondsInYear(year);
	}

	static short NumberOfDaysInMonth(short Month, short Year)
	{
		if (Month < 1 || Month > 12)
			return 0;
		short arrDays[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : arrDays[Month - 1];
	}

	short NumberOfDaysInMonth()
	{
		return NumberOfDaysInMonth(month, year);
	}

	static short NumberOfHoursInMonth(short YearNum, short MonthNum)
	{
		return NumberOfDaysInMonth(YearNum, MonthNum) * 24;
	}

	short NumberOfHoursInMonth()
	{
		return NumberOfHoursInMonth(year, month);
	}
	
	static int NumberOfMinutesInMonth(short YearNum, short MonthNum)
	{
		return NumberOfHoursInMonth(YearNum, MonthNum) * 60;
	}

	int NumberOfMinutesInMonth()
	{
		return NumberOfMinutesInMonth(year, month);
	}

	static int NumberOfSecondsInMonth(short YearNum, short MonthNum)
	{
		return NumberOfMinutesInMonth(YearNum, MonthNum) * 60;
	}

	int NumberOfSecondsInMonth()
	{
		return NumberOfSecondsInMonth(year, month);
	}

	string NameDayInWeek(short DayNum)
	{
		string arrDays[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
		return arrDays[DayNum];
	}

	static string NameDayInWeek(short Day, short Month, short Year)
	{
		string arrDays[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
		return arrDays[DayOfWeekOrder(Day, Month, Year)];
	}

	string NameDayInWeek()
	{
		return NameDayInWeek(day, month, year);
	}

	static string NameOfMonth(short Month)
	{
		string arrMonth[13] = { "", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
		return arrMonth[Month];
	}

	string NameOfMonth()
	{
		return NameOfMonth(month);
	}

	static void PrintMonthCalendar(short Year, short Month)
	{
		short DayInMonth = NumberOfDaysInMonth(Month, Year);
		short DayOrderInWeek = DayOfWeekOrder(1, Month, Year);

		cout << "\n ____________" << NameOfMonth(Month) << "____________\n";
		cout << "\n Sun " << "Mon " << "Tue " << "Wed " << "Thu " << "Fri " << "Sat " << endl;

		short Con = 0;

		for (int i = 0; i < DayOrderInWeek; i++)
		{
			Con++;
			cout << setw(4) << " ";
		}

		for (short j = 1; j <= DayInMonth; j++)
		{
			Con++;
			cout << setw(4) << j;
			if (Con % 7 == 0)
				cout << endl;
		}

		cout << "\n ___________________________" << endl;
	}

	void PrintMonthCalendar()
	{
		PrintMonthCalendar(year, month);
	}

	static void PrintYearCalendar(short Year)
	{
		cout << "\n ___________________________\n";
		cout << "\n       Calendar - " << Year << endl;
		cout << "\n ___________________________\n";

		for (short i = 1; i <= 12; ++i)
		{
			PrintMonthCalendar(i, Year);
		}
	}

	void PrintYearCalendar()
	{
		PrintYearCalendar(year);
	}

	static clsDate GetDataFromBeginningYear(short TotalDays, short Year)
	{
		clsDate Date;
		Date.Month = 1;
		Date.Year = Year;

		short NumDaysMonth;
		short RemainingDays = TotalDays;

		while (RemainingDays > (NumDaysMonth = NumberOfDaysInMonth(Date.Month, Year)))
		{
			RemainingDays -= NumDaysMonth;
			++Date.Month;
		}

		Date.Day = RemainingDays;
		return Date;
	}

	static short NumberOfDaysInYearFromBeginningOfTheYear(short Day, short Month, short Year)
	{
		short TotalDay = 0;

		for (int i = 1; i < Month; ++i)
		{
			TotalDay += NumberOfDaysInMonth(i, Year);
		}

		TotalDay += Day;

		return TotalDay;
	}

	short NumberOfDaysInYearFromBeginningOfTheYear()
	{
		return NumberOfDaysInYearFromBeginningOfTheYear(day, month, year);
	}

	static clsDate GateDateAfterAddingDays(short Days, clsDate Date)
	{
		Date.Day = Days + NumberOfDaysInYearFromBeginningOfTheYear(Date.Day, Date.Month, Date.Year);
		Date.Month = 1;

		while (true)
		{
			short NumDaysInMonth = NumberOfDaysInMonth(Date.Month, Date.Year);
			if (Date.Day > NumDaysInMonth)
			{
				++Date.Month;
				Date.Day -= NumDaysInMonth;

				if (Date.Month > 12)
				{
					++Date.Year;
					Date.Month = 1;
				}
			}
			else
			{
				break;
			}
		}

		return Date;
	}

	void GateDateAfterAddingDays(short Days)
	{
		*this = GateDateAfterAddingDays(Days, *this);
	}

	static bool IsLastDayInMonth(clsDate Date)
	{
		return (Date.day == NumberOfDaysInMonth(Date.month, Date.year));
	}

	bool IsLastDayInMonth()
	{
		return IsLastDayInMonth(*this);
	}

	static bool IsLastMonthInYear(short Month)
	{
		return (Month == 12);
	}

	bool IsLastMonthInYear()
	{
		return IsLastMonthInYear(month);
	}

	static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1.year < Date2.year) ? true :
			((Date1.year == Date2.year) ?
				((Date1.month < Date2.month) ? true :
					(Date1.month == Date2.month) ?
					Date1.day < Date2.day : false) : false);
	}

	bool IsDateBeforeDate2(clsDate Date2)
	{
		return IsDate1BeforeDate2(*this, Date2);
	}

	static bool IsDate1EqualToDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1.year == Date2.year) ? ((Date1.month == Date2.month) ? ((Date1.day == Date2.day) ? true : false) : false) : false;
	}

	bool IsDate1EqualToDate2(clsDate Date2)
	{
		return IsDate1EqualToDate2(*this, Date2);
	}

	static short DayOfWeekOrder(short Day, short Month, short Year)
	{
		short a, y, m;

		a = (14 - Month) / 12;
		y = (Year - a);
		m = Month + 12 * a - 2;

		//For the Gregorian Calendar
		return (Day + y + (y / 4) - (y / 100) + (y / 400) + (31 * m / 12)) % 7;
	}

	short DayOfWeekOrder()
	{
		return DayOfWeekOrder(day, month, year);
	}

	static short NumberOfDaysFromBeginningYear(short Day, short Month, short Year)
	{
		short NumberOfDays = 0;

		for (int i = 1; i < Month; ++i)
		{
			NumberOfDays += NumberOfDaysInMonth(i, Year);
		}

		NumberOfDays += Day;

		return NumberOfDays;
	}

	short NumberOfDaysFromBeginningYear()
	{
		return NumberOfDaysFromBeginningYear(day, month, year);
	}

	static clsDate IncreaseDateByOneDay(clsDate Date)
	{
		if (IsLastDayInMonth(Date))
		{
			if (IsLastMonthInYear(Date.month))
			{
				Date.day = 1;
				Date.month = 1;
				Date.year++;
			}
			else
			{
				Date.day = 1;
				Date.month++;
			}
		}
		else
		{
			Date.day++;
		}
		return Date;
	}

	void IncreaseDateByOneDay()
	{
		*this = IncreaseDateByOneDay(*this);
	}

	static void SwapDates(clsDate& Date1, clsDate& Date2)
	{
		clsDate TempDate;
		TempDate = Date1;
		Date1 = Date2;
		Date2 = TempDate;
	}

	static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
	{
		int TotalDays = 0;
		short SwapFlagValue = 1;

		if (!IsDate1BeforeDate2(Date1, Date2))
		{
			SwapFlagValue = -1;
			SwapDates(Date1, Date2);
		}

		while (IsDate1BeforeDate2(Date1, Date2))
		{
			TotalDays++;
			Date1 = IncreaseDateByOneDay(Date1);
		}

		return IncludeEndDay ? ++TotalDays * SwapFlagValue : TotalDays * SwapFlagValue;
	}

	int GetDifferenceInDays(clsDate Date2)
	{
		return GetDifferenceInDays(*this, Date2);
	}

	static short CalculateMyAgeInDays(clsDate DateOfBirth)
	{
		return GetDifferenceInDays(DateOfBirth, clsDate::GetSystemDate(), true);
	}

	static clsDate IncreaseDateByXDays(clsDate Date, short Days)
	{
		for (short i = 0; i < Days; ++i)
		{
			Date = IncreaseDateByOneDay(Date);
		}
		return Date;
	}

	void IncreaseDateByXDays(short Days)
	{
		*this = IncreaseDateByXDays(*this, Days);
	}

	static clsDate IncreaseDateByOneWeek(clsDate Date)
	{
		Date = IncreaseDateByXDays(Date, 7);
		return Date;
	}

	void IncreaseDateByOneWeek()
	{
		*this = IncreaseDateByOneWeek(*this);
	}

	clsDate IncreaseDateByXWeeks(clsDate Date, short Weeks)
	{
		for (short i = 0; i < Weeks; ++i)
		{
			Date = IncreaseDateByOneWeek(Date);
		}

		return Date;
	}

	void IncreaseDateByXWeeks(short Weeks)
	{
		*this = IncreaseDateByXWeeks(*this, Weeks);
	}

	static clsDate IncreaseDateByOneMonth(clsDate Date)
	{
		if (IsLastMonthInYear(Date.month))
		{
			Date.month = 1;
			Date.year++;
		}

		else
		{
			Date.month++;
		}

		short NumMonth = NumberOfDaysInMonth(Date.month, Date.year);

		if (Date.day > NumMonth)
		{
			Date.day = NumMonth;
		}

		return Date;
	}

	void IncreaseDateByOneMonth()
	{
		*this = IncreaseDateByOneMonth(*this);
	}

	static clsDate IncreaseDateByXMonths(clsDate Date, short Months)
	{
		for (short i = 0; i < Months; ++i)
		{
			Date = IncreaseDateByOneMonth(Date);
		}

		return Date;
	}

	void IncreaseDateByXMonths(short Months)
	{
		*this = IncreaseDateByXMonths(*this, Months);
	}

	static clsDate IncreaseDateByOneYear(clsDate Date)
	{
		Date.year++;
		return Date;
	}

	void IncreaseDateByOneYear()
	{
		*this = IncreaseDateByOneYear(*this);
	}

	static clsDate IncreaseDateByXYears(clsDate Date, short Years)
	{
		for (short i = 0; i < Years; ++i)
		{
			Date = IncreaseDateByOneYear(Date);
		}
		return Date;
	}

	void IncreaseDateByXYears(short Years)
	{
		*this = IncreaseDateByXYears(*this, Years);
	}

	static clsDate IncreaseDateByXYearsFaster(clsDate Date, short Years)
	{
		Date.year += Years;
		return Date;
	}

	void IncreaseDateByXYearsFaster(short Years)
	{
		*this = IncreaseDateByXYearsFaster(*this, Years);
	}

	static clsDate IncreaseDateByOneDecade(clsDate Date)
	{
		Date.year += 10;
		return Date;
	}

	void IncreaseDateByOneDecade()
	{
		*this = IncreaseDateByOneDecade(*this);
	}

	static clsDate IncreaseDateByXDecades(clsDate Date, short Decades)
	{
		for (short i = 0; i < Decades; ++i)
		{
			Date = IncreaseDateByOneDecade(Date);
		}
		return Date;
	}

	void IncreaseDateByXDecades(short Decades)
	{
		*this = IncreaseDateByXDecades(*this, Decades);
	}

	static clsDate IncreaseDateByXDecadesFaster(clsDate Date, short Decades)
	{
		Date.year += Decades * 10;
		return Date;
	}

	void IncreaseDateByXDecadesFaster(short Decades)
	{
		*this = IncreaseDateByXDecadesFaster(*this, Decades);
	}

	clsDate IncreaseDateByOneCentury(clsDate Date)
	{
		Date.year += 100;
		return Date;
	}

	void IncreaseDateByOneCentury()
	{
		*this = IncreaseDateByOneCentury(*this);
	}

	clsDate IncreaseDateByOneMillennium(clsDate Date)
	{
		Date.year += 1000;
		return Date;
	}

	void IncreaseDateByOneMillennium()
	{
		*this = IncreaseDateByOneMillennium(*this);
	}

	static bool IsFirstDayInMonth(short Day)
	{
		return (Day == 1);
	}

	bool IsFirstDayInMonth()
	{
		return IsFirstDayInMonth(day);
	}

	static bool IsFirstMonthInYear(short Month)
	{
		return (Month == 1);
	}

	bool IsFirstMonthInYear()
	{
		return IsFirstMonthInYear(month);
	}

	static clsDate DecreaseDateByOneDay(clsDate Date)
	{
		if (IsFirstDayInMonth(Date.day))
		{
			if (IsFirstMonthInYear(Date.month))
			{
				Date.day = 31;
				Date.month = 12;
				--Date.year;
			}
			else
			{
				--Date.month;
				short NumMonth = NumberOfDaysInMonth(Date.month, Date.year);
				Date.day = NumMonth;
			}
		}
		else
		{
			--Date.day;
		}

		return Date;
	}

	void DecreaseDateByOneDay()
	{
		*this = DecreaseDateByOneDay(*this);
	}

	static clsDate DecreaseDateByXDays(clsDate Date, short Days)
	{
		for (short i = 0; i < Days; ++i)
		{
			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}

	void DecreaseDateByXDays(short Days)
	{
		*this = DecreaseDateByXDays(*this, Days);
	}

	static clsDate DecreaseDateByOneWeek(clsDate Date)
	{
		Date = DecreaseDateByXDays(Date, 7);
		return Date;
	}

	void DecreaseDateByOneWeek()
	{
		*this = DecreaseDateByOneWeek(*this);
	}

	static clsDate DecreaseDateByXWeeks(clsDate Date, short Weeks)
	{
		for (short i = 0; i < Weeks; ++i)
		{
			Date = DecreaseDateByOneWeek(Date);
		}

		return Date;
	}

	void DecreaseDateByXWeeks(short Weeks)
	{
		*this = DecreaseDateByXWeeks(*this, Weeks);
	}

	static clsDate DecreaseDateByOneMonth(clsDate Date)
	{
		if (IsFirstMonthInYear(Date.month))
		{
			Date.month = 12;
			--Date.year;
		}
		else
		{
			--Date.month;
		}

		short DaysInMonth = NumberOfDaysInMonth(Date.month, Date.year);

		if (Date.day > DaysInMonth)
		{
			Date.day = DaysInMonth;
		}

		return Date;
	}

	void DecreaseDateByOneMonth()
	{
		*this = DecreaseDateByOneMonth(*this);
	}

	static clsDate DecreaseDateByXMonths(clsDate Date, short Months)
	{
		for (short i = 0; i < Months; ++i)
		{
			Date = DecreaseDateByOneMonth(Date);
		}

		return Date;
	}

	void DecreaseDateByXMonths(short Months)
	{
		*this = DecreaseDateByXMonths(*this, Months);
	}

	static clsDate DecreaseDateByOneYear(clsDate Date)
	{
		--Date.year;
		return Date;
	}

	void DecreaseDateByOneYear()
	{
		*this = DecreaseDateByOneYear(*this);
	}

	static clsDate DecreaseDateByXYears(clsDate Date, short Years)
	{
		for (short i = 0; i < Years; ++i)
		{
			Date = DecreaseDateByOneYear(Date);
		}

		return Date;
	}

	void DecreaseDateByXYears(short Years)
	{
		*this = DecreaseDateByXYears(*this, Years);
	}

	static clsDate DecreaseDateByXYearsFaster(clsDate Date, short Years)
	{
		Date.year -= Years;
		return Date;
	}

	void DecreaseDateByXYearsFaster(short Years)
	{
		*this = DecreaseDateByXYearsFaster(*this, Years);
	}

	static clsDate DecreaseDateByOneDecade(clsDate Date)
	{
		Date.year -= 10;
		return Date;
	}

	void DecreaseDateByOneDecade()
	{
		*this = DecreaseDateByOneDecade(*this);
	}

	static clsDate DecreaseDateByXDecades(clsDate Date, short Decades)
	{
		for (short i = 0; i < Decades; ++i)
		{
			Date = DecreaseDateByOneDecade(Date);
		}
		return Date;
	}

	void DecreaseDateByXDecades(short Decades)
	{
		*this = DecreaseDateByXDecades(*this, Decades);
	}

	static clsDate DecreaseDateByXDecadesFaster(clsDate Date, short Decades)
	{
		Date.year -= Decades * 10;
		return Date;
	}

	void DecreaseDateByXDecadesFaster(short Decades)
	{
		*this = DecreaseDateByXDecadesFaster(*this, Decades);
	}

	static clsDate DecreaseDateByOneCentury(clsDate Date)
	{
		Date.year -= 100;
		return Date;
	}

	void DecreaseDateByOneCentury()
	{
		*this = DecreaseDateByOneCentury(*this);
	}

	static clsDate DecreaseDateByOneMillennium(clsDate Date)
	{
		Date.year -= 1000;
		return Date;
	}

	void DecreaseDateByOneMillennium()
	{
		*this = DecreaseDateByOneMillennium(*this);
	}

	static short DayOfWeekOrder(clsDate Date)
	{
		return DayOfWeekOrder(Date.day, Date.month, Date.year);
	}

	string TodayName(short NumOrder)
	{
		string NameDayWeek[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
		return NameDayWeek[NumOrder];
	}

	static bool isEndOfWeek(clsDate Date)
	{
		short NumOrder = DayOfWeekOrder(Date);
		return (NumOrder == 6);
	}

	bool isEndOfWeek()
	{
		return isEndOfWeek(*this);
	}

	static bool isWeekEnd(clsDate Date)
	{
		short NumOrder = DayOfWeekOrder(Date);
		return (NumOrder == 5 || NumOrder == 6);
	}

	bool isWeekEnd()
	{
		return isWeekEnd(*this);
	}

	static bool IsBusinessDay(clsDate Date)
	{
		return !isWeekEnd(Date);
		//Another Solution
		//short NumOrder = DayOfWeekOrder(Date);
		//return (NumOrder != 5 && NumOrder != 6);	
	}

	bool IsBusinessDay()
	{
		return IsBusinessDay(*this);
	}

	static short DaysUntilTheEndOfWeek(clsDate Date)
	{
		short NumOrder = DayOfWeekOrder(Date);
		return 6 - NumOrder;
	}

	short DaysUntilTheEndOfWeek()
	{
		return DaysUntilTheEndOfWeek(*this);
	}

	static short DaysUntilTheEndOfMonth(clsDate Date)
	{
		short NumInMonth = NumberOfDaysInMonth(Date.month, Date.year);
		short TotalDays = NumInMonth - Date.day;
		return ++TotalDays;
		//Another Solution
		/*
		stDate EndOfMonthDate;
		EndOfMonthDate.Day = NumberOfDaysInMonth(Date.Month, Date.Year);
		EndOfMonthDate.Month = Date.Month;
		EndOfMonthDate.Year = Date.Year;

		return GetDifferenceInDays(Date, EndOfMonthDate, true);
		*/
	}

	short DaysUntilTheEndOfMonth()
	{
		return DaysUntilTheEndOfMonth(*this);
	}

	static short DaysUntilTheEndOfYear(clsDate Date)
	{
		short NumDaysFromBegin = NumberOfDaysFromBeginningYear(Date.day, Date.month, Date.year);
		short NumDaysInYear = NumberOfDaysInYear(Date.year);
		short TotalDays = NumDaysInYear - NumDaysFromBegin;
		return ++TotalDays;
		//Another Solution
		/*
		stDate EndOfYearDate;
		EndOfYearDate.Day = 31;
		EndOfYearDate.Month = 12;
		EndOfYearDate.Year = Date.Year;

		return GetDifferenceInDays(Date, EndOfYearDate, true);
		*/
	}

	short DaysUntilTheEndOfYear()
	{
		return DaysUntilTheEndOfYear(*this);
	}

	static short NumberOfVacationDays(clsDate DateFrom, clsDate DateTo)
	{
		short TotalDays = 0;

		while (IsDate1BeforeDate2(DateFrom, DateTo))
		{
			if (!IsBusinessDay(DateFrom))
				++TotalDays;

			DateFrom = IncreaseDateByOneDay(DateFrom);
		}
		return TotalDays;
	}

	static clsDate FinishVacationDate(clsDate DateFrom, short DurationTime)
	{
		clsDate DateTo;

		while (isWeekEnd(DateFrom))
		{
			DateFrom = IncreaseDateByOneDay(DateFrom);
		}

		while (DurationTime > 0)
		{
			if (IsBusinessDay(DateFrom))
			{
				DurationTime -= 1;
			}
			DateFrom = IncreaseDateByOneDay(DateFrom);
		}

		while (isWeekEnd(DateFrom))
		{
			DateFrom = IncreaseDateByOneDay(DateFrom);
		}

		DateTo = DateFrom;
		return DateTo;

		//Another Solution
		short WeekEndCounter = 0;

		/*while (isWeekEnd(DateFrom))
		{
			DateFrom = IncreaseDateByOneDay(DateFrom);
		}

		for (short i = 0; i < DurationTime + WeekEndCounter; ++i)
		{
			if (isWeekEnd(DateFrom))
				++WeekEndCounter;

			DateFrom = IncreaseDateByOneDay(DateFrom);
		}

		while (isWeekEnd(DateFrom))
		{
			DateFrom = IncreaseDateByOneDay(DateFrom);
		}

		stDate DateTo = DateFrom;
		return DateTo;*/
	}

	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
	{
		return !IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualToDate2(Date1, Date2);

		//Another Solution
		//return Date1.Year > Date2.Year ? true : ((Date1.Year == Date2.Year) ? ((Date1.Month > Date2.Month) ? true : ((Date1.Month == Date2.Month) ? (Date1.Day > Date2.Day) : false)) : false);
	}

	bool IsDate1AfterDate2(clsDate Date2)
	{
		return IsDate1AfterDate2(*this, Date2);
	}

	static short CalculateBusinessDay(clsDate DateFrom, clsDate DateTo)
	{
		short TotalDays = 0;

		while (IsDate1BeforeDate2(DateFrom, DateTo))
		{
			if (IsBusinessDay(DateFrom))
				TotalDays++;
			DateFrom = IncreaseDateByOneDay(DateFrom);
		}

		return TotalDays;
	}
	
	enum enCompareDates { Before = -1, Equal = 0, After = 1 };

	static enCompareDates CompareDates(clsDate Date1, clsDate Date2)
	{
		if (IsDate1BeforeDate2(Date1, Date2))
			return enCompareDates::Before;
		else if (IsDate1EqualToDate2(Date1, Date2))
			return enCompareDates::Equal;
		else
			return enCompareDates::After;
	}

	enCompareDates CompareDates(clsDate Date2)
	{
		return CompareDates(*this, Date2);
	}

	static bool IsValidateDate(clsDate Date)
	{
		if (Date.Day > NumberOfDaysInMonth(Date.month, Date.year) || Date.day < 1)
			return false;
		if (Date.month < 1 || Date.month > 12)
			return false;
		if (Date.year < 1)
			return false;
		return true;
	}

	bool IsValidateDate()
	{
		return IsValidateDate(*this);
	}

};


