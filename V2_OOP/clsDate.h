#pragma once
#pragma warning (disable : 4996)
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <format>
#include <ctime>
#include "clsString.h"
using namespace std;

struct stDate {
    short Day = 0;
    short Month = 0;
    short Year = 0;
};
enum enCompareDates { Before = -1, Equal = 0, After = 1 };

class clsDate
{
private:
    stDate _Date;

public:

// **** Constructors ****
    clsDate() : _Date(GetSystemDate()) {}
    clsDate(string sDate, string Delim = "/") : _Date(StringToDate(sDate, Delim)) {}
    clsDate(short Day, short Month, short Year)
    {
        SetYear(Year);
        SetMonth(Month);
        SetDay(Day);
    }
    clsDate(short DayOrderInYear, short Year) : _Date(GetDateFromDayOrderInYear(DayOrderInYear, Year)){}


// "SET" HELPERS
    bool IsValidDay(short Day) {
        return Day >= 1 && Day <= GetTotalDaysInMonth(Year, Month);
    }
    bool IsValidMonth(short Month) {
        return Month >= 1 && Month <= 12;
    }
    bool IsValidYear(short Year) {
        return Year >= 1;
    }

// **** Set & Get Properties ****
    bool SetDay(short Day) {
        if (!IsValidDay(Day)) {
            cout << "\nInvalid Day!";
            return false;
        }
        _Date.Day = Day;
        return true;
    }
    short GetDay() const {
        return _Date.Day;
    }
    __declspec(property(get = GetDay, put = SetDay)) short Day;

    bool SetMonth(short Month) {
        if (!IsValidMonth(Month)) {
            cout << "\nInvalid Month!";
            return false;
        }
        _Date.Month = Month;
        return true;
    }
    short GetMonth() const {
        return _Date.Month;
    }
    __declspec(property(get = GetMonth, put = SetMonth)) short Month;

    bool SetYear(short Year) {
        if (!IsValidYear(Year)) {
            cout << "\nInvalid Year!";
            return false;
        }
        _Date.Year = Year;
        return true;
    }
    short GetYear() const {
        return _Date.Year;
    }
    __declspec(property(get = GetYear, put = SetYear)) short Year;

    bool SetDate(stDate Date) {
        if (!IsValidDate(Date)) {
            cout << "\nInvalid Date!";
            return false;
        }
        _Date = Date;
        return true;
    }
    stDate GetDate() const {
        return _Date;
    }
    __declspec(property(get = GetDate, put = SetDate)) stDate Date;


// ==========================================================
// 1. SYSTEM DATE & CONVERSIONS
// ==========================================================

    static stDate GetSystemDate()
    {
        stDate Date;
        time_t t = time(0);
        tm* now = localtime(&t);

        Date.Year = now->tm_year + 1900;
        Date.Month = now->tm_mon + 1;
        Date.Day = now->tm_mday;

        return Date;
    }
    static string GetSystemTime() {
        time_t now = time(0);
        tm* t = localtime(&now);

        return to_string(t->tm_hour) + ":" +
            to_string(t->tm_min) + ":" +
            to_string(t->tm_sec);
    }
    static stDate StringToDate(string DateString, const string& Delim = "/")
    {
        stDate DateStruct;
        vector<string> vDate = clsString::SplitText(DateString, Delim);

        DateStruct.Day = stoi(vDate[0]);
        DateStruct.Month = stoi(vDate[1]);
        DateStruct.Year = stoi(vDate[2]);

        return DateStruct;
    }

    static string DateToString(const stDate& Date, const string& Delim = "/")
    {
        return to_string(Date.Day) + Delim + to_string(Date.Month) + Delim + to_string(Date.Year);
    }
    string DateToString(const string& Delim = "/")
    {
        return DateToString(_Date, Delim);
    }

    static string FormatDate(const stDate& Date, const string& DateFormat = "dd/mm/yyyy")
    {
        string FormattedDateString = DateFormat;

        FormattedDateString = clsString::ReplaceWordInString(FormattedDateString, "dd", to_string(Date.Day));
        FormattedDateString = clsString::ReplaceWordInString(FormattedDateString, "mm", to_string(Date.Month));
        FormattedDateString = clsString::ReplaceWordInString(FormattedDateString, "yyyy", to_string(Date.Year));

        return FormattedDateString;
    }
    string FormatDate(const string& DateFormat = "dd/mm/yyyy")
    {
        return FormatDate(_Date, DateFormat);
    }

// =========================================================
// 2. LEAP YEAR & MONTH/YEAR CALCULATIONS
// =========================================================

    static bool IsLeapYear(short Year)
    {
        return (Year % 400 == 0 || (Year % 4 == 0 && Year % 100 != 0));
    }

    static short GetTotalDaysInYear(short Year)
    {
        return IsLeapYear(Year) ? 366 : 365;
    }

    static int GetTotalHoursInYear(short Year)
    {
        return GetTotalDaysInYear(Year) * 24;
    }

    static long GetTotalMinutesInYear(short Year)
    {
        return GetTotalHoursInYear(Year) * 60;
    }

    static long long GetTotalSecondsInYear(short Year)
    {
        return GetTotalMinutesInYear(Year) * 60;
    }

    static short GetTotalDaysInMonth(short Year, short Month)
    {
        short DaysInMonths[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        return (Month == 2 && IsLeapYear(Year)) ? 29 : DaysInMonths[Month];
    }

    static int GetTotalHoursInMonth(short Year, short Month)
    {
        return GetTotalDaysInMonth(Year, Month) * 24;
    }

    static long GetTotalMinutesInMonth(short Year, short Month)
    {
        return GetTotalHoursInMonth(Year, Month) * 60;
    }

    static long long GetTotalSecondsInMonth(short Year, short Month)
    {
        return GetTotalMinutesInMonth(Year, Month) * 60;
    }

// ===================================================
// 3. DAY OF WEEK & CALENDAR PRINTING
// ===================================================

    static short GetDayOfWeekOrder(short Day, short Month, short Year)
    {
        short a = (14 - Month) / 12;
        short y = Year - a;
        short m = Month + (12 * a) - 2;
        return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
    }
    static short GetDayOfWeekOrder(const stDate& Date)
    {
        return GetDayOfWeekOrder(Date.Day, Date.Month, Date.Year);
    }
    short GetDayOfWeekOrder()
    {
        return GetDayOfWeekOrder(_Date);
    }

    static string GetWeekDayName(short DayOfWeekOrder)
    {
        string arrWeekDaysName[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
        return arrWeekDaysName[DayOfWeekOrder];
    }
    string GetWeekDayName()
    {
        return GetWeekDayName(GetDayOfWeekOrder(_Date));
    }

    static string GetMonthName(short Month)
    {
        string arrMonthName[13] = { "", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
        return arrMonthName[Month];
    }
    string GetMonthName()
    {
        return GetMonthName(_Date.Month);
    }

    static void PrintMonthCalendar(short Year, short Month)
    {
        short DayOrder = GetDayOfWeekOrder(1, Month, Year);
        short TotalDays = GetTotalDaysInMonth(Year, Month);

        cout << "\n  _______________" << GetMonthName(Month) << "_______________\n\n";
        cout << "  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n";

        int CurrentDayOfWeek = 0;
        for (CurrentDayOfWeek = 0; CurrentDayOfWeek < DayOrder; CurrentDayOfWeek++)
        {
            cout << "     ";
        }

        for (short Day = 1; Day <= TotalDays; Day++)
        {
            cout << setw(5) << Day;

            if (++CurrentDayOfWeek == 7)
            {
                CurrentDayOfWeek = 0;
                cout << "\n";
            }
        }

        if (CurrentDayOfWeek != 0)
        {
            cout << "\n";
        }

        cout << "  _________________________________\n";
    }
    void PrintMonthCalendar() {
        PrintMonthCalendar(_Date.Year, _Date.Month);
    }

    static void PrintYearCalendar(short Year)
    {
        cout << "\n  _________________________________\n\n";
        cout << "          Calendar - " << Year << "          ";
        cout << "\n  _________________________________\n";

        for (short Month = 1; Month <= 12; Month++)
        {
            PrintMonthCalendar(Year, Month);
            cout << "\n";
        }
    }
    void PrintYearCalendar() {
         PrintYearCalendar(_Date.Year);
    }

    static void PrintDate(const stDate& Date)
    {
        cout << Date.Day << "/" << Date.Month << "/" << Date.Year;
    }
    void PrintDate()
    {
        PrintDate(_Date);
    }

// =====================================================
// 4. DATE VALIDATION & DAY ORDERS
// =====================================================

    static bool IsValidDate(stDate Date)
    {
        return (Date.Month >= 1 && Date.Month <= 12) &&
            (Date.Day >= 1 && Date.Day <= GetTotalDaysInMonth(Date.Year, Date.Month));
    }
    bool IsValidDate() {
        return IsValidDate(this->Date);
    }

    static short GetNumberOfDaysFromTheBeginingOfTheYear(short Day, short Month, short Year)
    {
        short TotalDays = 0;
        for (short i = 1; i < Month; i++)
        {
            TotalDays += GetTotalDaysInMonth(Year, i);
        }
        return TotalDays + Day;
    }
    static short GetNumberOfDaysFromTheBeginingOfTheYear(const stDate& Date)
    {
        return GetNumberOfDaysFromTheBeginingOfTheYear(Date.Day, Date.Month, Date.Year);
    }
    short GetNumberOfDaysFromTheBeginingOfTheYear() {
        return GetNumberOfDaysFromTheBeginingOfTheYear(_Date);
    }

    static stDate GetDateFromDayOrderInYear(short DayOrderInYear, short Year)
    {
        short DaysInCurrentMonth = 0;

        for (short Month = 1; Month <= 12; Month++)
        {
            DaysInCurrentMonth = GetTotalDaysInMonth(Year, Month);

            if (DayOrderInYear <= DaysInCurrentMonth)
            {
                return { DayOrderInYear, Month, Year };
            }

            DayOrderInYear -= DaysInCurrentMonth;
        }

        return { 0, 0, Year };
    }

    static bool IsLastDayInMonth(const stDate& Date)
    {
        return (Date.Day == GetTotalDaysInMonth(Date.Year, Date.Month));
    }
    bool IsLastDayInMonth() {
        return IsLastDayInMonth(_Date);
    }

    static bool IsLastMonthInYear(short Month)
    {
        return (Month == 12);
    }
    bool IsLastMonthInYear() {
        return IsLastMonthInYear(_Date.Month);
    }

// ========================================================
// 5. DATE COMPARISONS & DIFFERENCES
// ========================================================

    static bool IsDate1BeforeDate2(const stDate& Date1, const stDate& Date2)
    {
        return (Date1.Year < Date2.Year) ? true :
            (Date1.Year == Date2.Year) ? ((Date1.Month < Date2.Month) ? true :
                (Date1.Month == Date2.Month) ? (Date1.Day < Date2.Day) : false)
            : false;
    }
    static bool IsDate1BeforeDate2(const clsDate& Date1, const clsDate& Date2)
    {
        return IsDate1BeforeDate2(Date1._Date, Date2._Date);
    }
    bool IsDateBeforeDate2(const stDate& Date2)
    {
        return IsDate1BeforeDate2(_Date, Date2);
    }
    bool IsDateBeforeDate2(const clsDate& Date2)
    {
        return IsDate1BeforeDate2(*this, Date2);
    }


    static bool IsDate1EqualDate2(const stDate& Date1, const stDate& Date2)
    {
        return ((Date1.Year == Date2.Year) && (Date1.Month == Date2.Month) && (Date1.Day == Date2.Day));
    }
    static bool IsDate1EqualDate2(const clsDate& Date1, const clsDate& Date2)
    {
        return IsDate1EqualDate2(Date1._Date, Date2._Date);
    }
    bool IsDateEqualDate2(const stDate& Date2)
    {
        return IsDate1EqualDate2(_Date, Date2);
    }
    bool IsDateEqualDate2(const clsDate& Date2)
    {
        return IsDate1EqualDate2(*this, Date2);
    }


    static bool IsDate1AfterDate2(const stDate& Date1, const stDate& Date2)
    {
        return (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2));
    }
    static bool IsDate1AfterDate2(const clsDate& Date1, const clsDate& Date2)
    {
        return IsDate1AfterDate2(Date1._Date, Date2._Date);
    }
    bool IsDateAfterDate2(const stDate& Date2)
    {
        return IsDate1AfterDate2(_Date, Date2);
    }
    bool IsDateAfterDate2(const clsDate& Date2)
    {
        return IsDate1AfterDate2(*this, Date2);
    }

    static bool IsDateBetween(const stDate& Date, const stDate& Date1, const stDate& Date2) {
        return (IsDate1EqualDate2(Date, Date1) || IsDate1EqualDate2(Date, Date2)) ? true : 
       ((IsDate1AfterDate2(Date, Date1) && IsDate1BeforeDate2(Date, Date2)) ||(IsDate1BeforeDate2(Date, Date1) && IsDate1AfterDate2(Date, Date2)));
    }
    static bool IsDateBetween(const clsDate& Date, const clsDate& Date1, const clsDate& Date2) {
        return IsDateBetween(Date._Date, Date1._Date, Date2._Date);
    }
    bool IsDateBetween(const clsDate& Date1, const clsDate& Date2) {
        return IsDateBetween(*this, Date1, Date2);
    }
    bool IsDateBetween(const stDate& Date1, const stDate& Date2) {
        return IsDateBetween(_Date, Date1, Date2);
    }

    static enCompareDates CompareDates(const stDate& Date1, const stDate& Date2)
    {
        if (IsDate1BeforeDate2(Date1, Date2)) return enCompareDates::Before;
        if (IsDate1EqualDate2(Date1, Date2))  return enCompareDates::Equal;
        return enCompareDates::After;
    }
    static enCompareDates CompareDates(const clsDate& Date1, const clsDate& Date2) {
        return CompareDates(Date1._Date, Date2._Date);
    }

    static void SwapDates(stDate& Date1, stDate& Date2)
    {
        stDate Temp = Date1;
        Date1 = Date2;
        Date2 = Temp;
    }
    static void SwapDates(clsDate& Date1, clsDate& Date2)
    {
        stDate Temp = Date1._Date;
        Date1._Date = Date2._Date;
        Date2._Date = Temp;
    }
    void SwapDateWithDate2(stDate& Date2)
    {
        SwapDates(_Date, Date2);
    }
    void SwapDateWithDate2(clsDate& Date2)
    {
        SwapDates(*this, Date2);
    }

   static int GetDiffInDaysBetweenTwoDates(const stDate& Date1, const stDate& Date2, bool IncludeEndDay = false)
    {
        int DaysDiff = 0;
        short SwapFlagValue = 1;
        stDate Date1Temp = Date1, Date2Temp = Date2;

        if (!IsDate1BeforeDate2(Date1Temp, Date2Temp) && !IsDate1EqualDate2(Date1Temp, Date2Temp))
        {
            SwapDates(Date1Temp, Date2Temp);
            SwapFlagValue = -1;
        }

        if (Date1Temp.Year < Date2Temp.Year)
        {
            DaysDiff += GetTotalDaysInYear(Date1Temp.Year) - GetNumberOfDaysFromTheBeginingOfTheYear(Date1Temp);
            Date1Temp.Year++;

            while (Date1Temp.Year < Date2Temp.Year)
            {
                DaysDiff += GetTotalDaysInYear(Date1Temp.Year);
                Date1Temp.Year++;
            }

            DaysDiff += GetNumberOfDaysFromTheBeginingOfTheYear(Date2Temp);  
        }
        else
        {
            DaysDiff = GetNumberOfDaysFromTheBeginingOfTheYear(Date2Temp) - GetNumberOfDaysFromTheBeginingOfTheYear(Date1Temp);
        }

        return IncludeEndDay ? (DaysDiff + 1) * SwapFlagValue : DaysDiff * SwapFlagValue;
    }
    int GetDiffInDaysBetweenDateAndDate2(const stDate& Date2, bool IncludeEndDay = false)
    {
        return GetDiffInDaysBetweenTwoDates(_Date, Date2, IncludeEndDay);
    }

// ===================================================
// 6. DATE INCREAMENTATION
// ===================================================

    static void IncreaseDateByOneDay(stDate& Date)
    {
        if (IsLastDayInMonth(Date))
        {
            Date.Day = 1;

            if (IsLastMonthInYear(Date.Month))
            {
                Date.Month = 1;
                Date.Year++;
            }
            else
            {
                Date.Month++;
            }
        }
        else
        {
            Date.Day++;
        }

    }
    void IncreaseDateByOneDay()
    {
       IncreaseDateByOneDay(_Date);
    }

    static void IncreaseDateByXDays(stDate& Date, short DaysToAdd)
    {
        for (short i = 1; i <= DaysToAdd; i++)
        {
           IncreaseDateByOneDay(Date);
        }
    }
    void IncreaseDateByXDays(short DaysToAdd)
    {
        IncreaseDateByXDays(_Date, DaysToAdd);
    }


    static void IncreaseDateByOneWeek(stDate& Date)
    {
         IncreaseDateByXDays(Date, 7);
    }
    void IncreaseDateByOneWeek()
    {
        IncreaseDateByOneWeek(_Date);
    }

    static void IncreaseDateByXWeeks(stDate& Date, short WeeksToAdd)
    {
        for (short i = 1; i <= WeeksToAdd; i++)
            IncreaseDateByOneWeek(Date);
    }
    void IncreaseDateByXWeeks(short WeeksToAdd)
    {
        IncreaseDateByXWeeks(_Date, WeeksToAdd);
    }

    static void IncreaseDateByOneMonth(stDate& Date)
    {
        if (Date.Month == 12)
        {
            Date.Month = 1;
            Date.Year++;
        }
        else
        {
            Date.Month++;
        }

        short NumberOfDaysInCurrentMonth = GetTotalDaysInMonth(Date.Year, Date.Month);
        if (Date.Day > NumberOfDaysInCurrentMonth)
        {
            Date.Day = NumberOfDaysInCurrentMonth;
        }

    }
    void IncreaseDateByOneMonth()
    {
        IncreaseDateByOneMonth(_Date);
    }

    static void IncreaseDateByXMonths(stDate& Date, short MonthsToAdd)
    {
        for (short i = 1; i <= MonthsToAdd; i++)
            IncreaseDateByOneMonth(Date);
    }
    void IncreaseDateByXMonths(short MonthsToAdd)
    {
        IncreaseDateByXMonths(_Date, MonthsToAdd);
    }

    static void IncreaseDateByOneYear(stDate& Date)
    {
        Date.Year++;
        short NumberOfDaysInCurrentMonth = GetTotalDaysInMonth(Date.Year, Date.Month);
        if (Date.Day > NumberOfDaysInCurrentMonth)
            Date.Day = NumberOfDaysInCurrentMonth;
    }
    void IncreaseDateByOneYear()
    {
        IncreaseDateByOneYear(_Date);
    }

    static void IncreaseDateByXYears(stDate& Date, short YearsToAdd)
    {
        for (short i = 1; i <= YearsToAdd; i++)
            IncreaseDateByOneYear(Date);
    }
    void IncreaseDateByXYears(short YearsToAdd)
    {
        IncreaseDateByXYears(_Date, YearsToAdd);
    }

    static void IncreaseDateByXYearsFaster(stDate& Date, short YearsToAdd)
    {
        Date.Year += YearsToAdd;
        short NumberOfDaysInCurrentMonth = GetTotalDaysInMonth(Date.Year, Date.Month);
        if (Date.Day > NumberOfDaysInCurrentMonth)
        {
            Date.Day = NumberOfDaysInCurrentMonth;
        }
    }
    void IncreaseDateByXYearsFaster(short YearsToAdd)
    {
        IncreaseDateByXYearsFaster(_Date, YearsToAdd);
    }

    static void IncreaseDateByOneDecade(stDate& Date)
    {
         IncreaseDateByXYearsFaster(Date, 10);
    }
    void IncreaseDateByOneDecade()
    {
        IncreaseDateByOneDecade(_Date);
    }

    static void IncreaseDateByXDecades(stDate& Date, short DecadesToAdd)
    {
        for (short i = 1; i <= DecadesToAdd; i++)
            IncreaseDateByOneDecade(Date);
    }
    void IncreaseDateByXDecades(short DecadesToAdd)
    {
         IncreaseDateByXDecades(_Date, DecadesToAdd);
    }

    static void IncreaseDateByXDecadesFaster(stDate& Date, short DecadesToAdd)
    {
        Date.Year += DecadesToAdd * 10;
        short NumberOfDaysInCurrentMonth = GetTotalDaysInMonth(Date.Year, Date.Month);
        if (Date.Day > NumberOfDaysInCurrentMonth)
        {
            Date.Day = NumberOfDaysInCurrentMonth;
        }
    }
    void IncreaseDateByXDecadesFaster(short DecadesToAdd)
    {
       IncreaseDateByXDecadesFaster(_Date, DecadesToAdd);
    }

    static void IncreaseDateByOneCentury(stDate& Date)
    {
        IncreaseDateByXDecadesFaster(Date, 10);
    }
    void IncreaseDateByOneCentury()
    {
        IncreaseDateByOneCentury(_Date);
    }

    static void IncreaseDateByXCenturiesFaster(stDate& Date, short CenturiesToAdd)
    {
        Date.Year += CenturiesToAdd * 100;
        short NumberOfDaysInCurrentMonth = GetTotalDaysInMonth(Date.Year, Date.Month);
        if (Date.Day > NumberOfDaysInCurrentMonth)
        {
            Date.Day = NumberOfDaysInCurrentMonth;
        }
    }
    void IncreaseDateByXCenturiesFaster(short CenturiesToAdd)
    {
        IncreaseDateByXCenturiesFaster(_Date, CenturiesToAdd);
    }

    static void IncreaseDateByOneMillennium(stDate& Date)
    {
         IncreaseDateByXCenturiesFaster(Date, 10);
    }
    void IncreaseDateByOneMillennium()
    {
         IncreaseDateByOneMillennium(_Date);
    }

    static stDate GetDateAfterAddingDays(stDate Date, short DaysAdded)
    {
        short DaysInCurrentYear = 0;
        short DayOrderInYear = GetNumberOfDaysFromTheBeginingOfTheYear(Date.Day, Date.Month, Date.Year);
        short TotalDays = DayOrderInYear + DaysAdded;

        while (TotalDays > (DaysInCurrentYear = GetTotalDaysInYear(Date.Year)))
        {
            TotalDays -= DaysInCurrentYear;
            Date.Year++;
        }

        return GetDateFromDayOrderInYear(TotalDays, Date.Year);
    }
    stDate GetDateAfterAddingDays(short DaysAdded)
    {
        return GetDateAfterAddingDays(_Date, DaysAdded);
    }

    // ===================================================
    // 7. DATE DECREAMENTATION
    // ===================================================

    static void DecreaseDateByOneDay(stDate& Date)
    {
        if (Date.Day == 1)
        {
            if (Date.Month == 1)
            {
                Date.Month = 12;
                Date.Year--;
            }
            else
            {
                Date.Month--;
            }

            Date.Day = GetTotalDaysInMonth(Date.Year, Date.Month);
        }
        else
        {
            Date.Day--;
        }

    }
    void DecreaseDateByOneDay()
    {
        DecreaseDateByOneDay(_Date);
    }

    static void DecreaseDateByXDays(stDate& Date, short DaysToRemove)
    {
        for (short i = 1; i <= DaysToRemove; i++)
            DecreaseDateByOneDay(Date);


    }
    void DecreaseDateByXDays(short DaysToRemove)
    {
         DecreaseDateByXDays(_Date, DaysToRemove);
    }

    static void DecreaseDateByOneWeek(stDate& Date)
    {
         DecreaseDateByXDays(Date, 7);
    }
    void DecreaseDateByOneWeek()
    {
         DecreaseDateByOneWeek(_Date);
    }

    static void DecreaseDateByXWeeks(stDate& Date, short WeeksToRemove)
    {
        for (short i = 1; i <= WeeksToRemove; i++)
             DecreaseDateByOneWeek(Date);

    }
    void DecreaseDateByXWeeks(short WeeksToRemove)
    {
        DecreaseDateByXWeeks(_Date, WeeksToRemove);
    }

    static void DecreaseDateByOneMonth(stDate& Date)
    {
        if (Date.Month == 1)
        {
            Date.Month = 12;
            Date.Year--;
        }
        else
        {
            Date.Month--;
        }

        short NumberOfDaysInCurrentMonth = GetTotalDaysInMonth(Date.Year, Date.Month);
        if (Date.Day > NumberOfDaysInCurrentMonth)
        {
            Date.Day = NumberOfDaysInCurrentMonth;
        }

    }
    void DecreaseDateByOneMonth()
    {
        DecreaseDateByOneMonth(_Date);
    }

    static void DecreaseDateByXMonths(stDate& Date, short MonthsToRemove)
    {
        for (short i = 1; i <= MonthsToRemove; i++)
             DecreaseDateByOneMonth(Date);
    }
    void DecreaseDateByXMonths(short MonthsToRemove)
    {
         DecreaseDateByXMonths(_Date, MonthsToRemove);
    }

    static void DecreaseDateByOneYear(stDate& Date)
    {
        Date.Year--;
        short NumberOfDaysInCurrentMonth = GetTotalDaysInMonth(Date.Year, Date.Month);
        if (Date.Day > NumberOfDaysInCurrentMonth)
        {
            Date.Day = NumberOfDaysInCurrentMonth;
        }
    }
    void DecreaseDateByOneYear()
    {
        DecreaseDateByOneYear(_Date);
    }

    static void DecreaseDateByXYears(stDate& Date, short YearsToRemove)
    {
        for (short i = 1; i <= YearsToRemove; i++)
        {
            DecreaseDateByOneYear(Date);
        }
    }
    void DecreaseDateByXYears(short YearsToRemove)
    {
         DecreaseDateByXYears(_Date, YearsToRemove);
    }

    static void DecreaseDateByXYearsFaster(stDate& Date, short YearsToRemove)
    {
        Date.Year -= YearsToRemove;
        short NumberOfDaysInCurrentMonth = GetTotalDaysInMonth(Date.Year, Date.Month);
        if (Date.Day > NumberOfDaysInCurrentMonth)
        {
            Date.Day = NumberOfDaysInCurrentMonth;
        }
    }
    void DecreaseDateByXYearsFaster(short YearsToRemove)
    {
        DecreaseDateByXYearsFaster(_Date, YearsToRemove);
    }

    static void DecreaseDateByOneDecade(stDate& Date)
    {
         DecreaseDateByXYearsFaster(Date, 10);
    }
    void DecreaseDateByOneDecade()
    {
        DecreaseDateByOneDecade(_Date);
    }

    static void DecreaseDateByXDecades(stDate& Date, short DecadesToRemove)
    {
        for (short i = 1; i <= DecadesToRemove; i++)
            DecreaseDateByOneDecade(Date);
    }
    void DecreaseDateByXDecades(short DecadesToRemove)
    {
         DecreaseDateByXDecades(_Date, DecadesToRemove);
    }

    static void DecreaseDateByXDecadesFaster(stDate& Date, short DecadesToRemove)
    {
        Date.Year -= DecadesToRemove * 10;
        short NumberOfDaysInCurrentMonth = GetTotalDaysInMonth(Date.Year, Date.Month);
        if (Date.Day > NumberOfDaysInCurrentMonth)
        {
            Date.Day = NumberOfDaysInCurrentMonth;
        }
    }
    void DecreaseDateByXDecadesFaster(short DecadesToRemove)
    {
         DecreaseDateByXDecadesFaster(_Date, DecadesToRemove);
    }

    static void DecreaseDateByOneCentury(stDate& Date)
    {
         DecreaseDateByXDecadesFaster(Date, 10);
    }
    void DecreaseDateByOneCentury()
    {
        DecreaseDateByOneCentury(_Date);
    }

    static void DecreaseDateByXCenturiesFaster(stDate& Date, short CenturiesToRemove)
    {
        Date.Year -= CenturiesToRemove * 100;
        short NumberOfDaysInCurrentMonth = GetTotalDaysInMonth(Date.Year, Date.Month);
        if (Date.Day > NumberOfDaysInCurrentMonth)
        {
            Date.Day = NumberOfDaysInCurrentMonth;
        }
    }
    void DecreaseDateByXCenturiesFaster(short CenturiesToRemove)
    {
         DecreaseDateByXCenturiesFaster(_Date, CenturiesToRemove);
    }

    static void DecreaseDateByOneMillennium(stDate& Date)
    {
        DecreaseDateByXCenturiesFaster(Date, 10);
    }
    void DecreaseDateByOneMillennium()
    {
        DecreaseDateByOneMillennium(_Date);
    }

    // ===========================================================
    // 8. BUSINESS DAYS & VACATIONS
    // ===========================================================

    static bool IsEndOfWeek(const stDate& Date)
    {
        return GetDayOfWeekOrder(Date) == 6;
    }
    bool IsEndOfWeek()
    {
        return IsEndOfWeek(_Date);
    }

    static bool IsWeekEnd(const stDate& Date)
    {
        short DayIndex = GetDayOfWeekOrder(Date);
        return (DayIndex == 5 || DayIndex == 6);
    }
    bool IsWeekEnd()
    {
        return IsWeekEnd(_Date);
    }

    static bool IsBusinessDay(const stDate& Date)
    {
        return !IsWeekEnd(Date);
    }
    bool IsBusinessDay()
    {
        return IsBusinessDay(_Date);
    }

    static short GetDaysUntilEndOfWeek(const stDate& Date)
    {
        return 6 - GetDayOfWeekOrder(Date);
    }
    short GetDaysUntilEndOfWeek() {
        return GetDaysUntilEndOfWeek(_Date);
    }

    static short GetDaysUntilEndOfMonth(const stDate& Date)
    {
        stDate EndOfMonthDate = Date;
        EndOfMonthDate.Day = GetTotalDaysInMonth(Date.Year, Date.Month);
        return GetDiffInDaysBetweenTwoDates(Date, EndOfMonthDate, true);
    }
    short GetDaysUntilEndOfMonth() {
        return GetDaysUntilEndOfMonth(_Date);
    }

    static short GetDaysUntilEndOfYear(const stDate& Date)
    {
        stDate EndOfYearDate = { 31, 12, Date.Year };
        return GetDiffInDaysBetweenTwoDates(Date, EndOfYearDate, true);
    }
    short GetDaysUntilEndOfYear() {
        return GetDaysUntilEndOfYear(_Date);
    }

    static short CalcVacationDays(const stDate& VacationStart, const stDate& VacationEnd, bool IncludeEndDay = false)
    {
        short Counter = 0;
        stDate StartDate =  VacationStart;
        while (IsDate1BeforeDate2(StartDate, VacationEnd))
        {
            if (!IsWeekEnd(StartDate)) {
            Counter++;
            }
            IncreaseDateByOneDay(StartDate);
        }
        return (IncludeEndDay && IsBusinessDay(VacationEnd)) ? ++Counter : Counter;
    }
    static stDate CalcEndDateOfVacation(const stDate& DateStart, short ActualVacationDays) {
        stDate DateEnd = DateStart;
        while (ActualVacationDays) {
            if (!IsWeekEnd(DateEnd))
                ActualVacationDays--;
            IncreaseDateByOneDay(DateEnd);
        }
        return DateEnd;
    }

    static short CalcBusinessDays(const stDate& BusinessStart, const stDate& BusinessEnd, bool IncludeEndDay = false)
    {
        stDate TempDate = BusinessStart; 
        short Counter = 0;

        while (IsDate1BeforeDate2(TempDate, BusinessEnd))
        {
            if (IsBusinessDay(TempDate)) {
            Counter++;
            }
            IncreaseDateByOneDay(TempDate);
        }
        return (IncludeEndDay && IsBusinessDay(BusinessEnd)) ? ++Counter : Counter;
    }
    static stDate CalcEndDateOfBusinessDays(const stDate& DateStart, short ActualBusinessDays) {
        stDate DateEnd = DateStart;
        while (ActualBusinessDays) {
            if (IsBusinessDay(DateEnd))
                ActualBusinessDays--;
            IncreaseDateByOneDay(DateEnd);
        }
        return DateEnd;
    }

};

