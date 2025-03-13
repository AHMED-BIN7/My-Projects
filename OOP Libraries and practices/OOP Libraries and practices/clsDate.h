#pragma once
#pragma warning (disable : 4996)

#include<iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

class clsDate
{
private:
    short _Year;
    short _Month;
    short _Day;

public:

    friend class clsPeriod;

    clsDate()
    {
        time_t t = time(0);
        tm* now = localtime(&t);

        _Year = now->tm_year + 1900;
        _Month = now->tm_mon + 1;
        _Day = now->tm_mday;
    }
    clsDate(short Day, short Month, short Year)
    {
        _Year = Year;
        _Month = Month;
        _Day = Day;
    }
    clsDate(string sDate)
    {
        vector <string>vDate;
        vDate = clsString::Split(sDate, "/");

        _Year = stoi(vDate[0]);
        _Month = stoi(vDate[1]);
        _Day = stoi(vDate[2]);
    }
    void SetDay(short Day) {
        _Day = Day;
    }

    short GetDay() {
        return _Day;
    }
    __declspec(property(get = GetDay, put = SetDay)) short Day;

    void SetMonth(short Month) {
        _Month = Month;
    }

    short GetMonth() {
        return _Month;
    }
    __declspec(property(get = GetMonth, put = SetMonth)) short Month;


    void SetYear(short Year) {
        _Year = Year;
    }

    short GetYear() {
        return _Year;
    }
    __declspec(property(get = GetYear, put = SetYear)) short Year;

    static bool IsLepYears(int Years)
    {
        return (Years % 4 == 0 && Years % 100 != 0) || (Years % 400 == 0);
    }
    bool IsLepYears()
    {
        return (_Year % 4 == 0 && _Year % 100 != 0) || (_Year % 400 == 0);
    }
    static int NumberOfDaysInYear(int Year)
    {
        return (IsLepYears(Year)) ? 366 : 365;
    }
    int NumberOfDaysInYear()
    {
        return (IsLepYears(_Year)) ? 366 : 365;
    }
    static int NumberOfHoursInYear(int Year)
    {
        return NumberOfDaysInYear(Year) * 24;
    }
    int NumberOfHoursInYear()
    {
        return NumberOfDaysInYear(_Year) * 24;
    }
    static int NumberOfMinutesInYear(int Year)
    {
        return NumberOfHoursInYear(Year) * 60;
    }
    int NumberOfMinutesInYear()
    {
        return NumberOfHoursInYear(_Year) * 60;
    }
    static int NumberOfSecondsInYear(int Year)
    {
        return NumberOfMinutesInYear(Year) * 60;
    }
    int NumberOfSecondsInYear()
    {
        return NumberOfMinutesInYear(_Year) * 60;
    }
    static short NumberOfDaysInMonth(short Year, short Month)
    {
        if (Month < 1 || Month >12)
            return 0;

        int arry[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

        return (Month == 2) ? (IsLepYears(Year) ? 29 : 28) : arry[Month - 1];
    }
    short NumberOfDaysInMonth()
    {
        if (_Month < 1 || _Month >12)
            return 0;

        int arry[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

        return (_Month == 2) ? (IsLepYears(_Year) ? 29 : 28) : arry[_Month - 1];
    }
    static int NumberOfHoursInMonth(int Year, int Month)
    {
        return NumberOfDaysInMonth(Year, Month) * 24;
    }
    int NumberOfHoursInMonth()
    {
        return NumberOfDaysInMonth(_Year, _Month) * 24;
    }
    static int NumberOfMinutesInMonth(int Year, int Month)
    {
        return NumberOfHoursInMonth(Year, Month) * 60;
    }
    int NumberOfMinutesInMonth()
    {
        return NumberOfHoursInMonth(_Year, _Month) * 60;
    }
    static int NumberOfSecondsInMonth(int Year, int Month)
    {
        return NumberOfMinutesInMonth(Year, Month) * 60;
    }
    int NumberOfSecondsInMonth()
    {
        return NumberOfMinutesInMonth(_Year, _Month) * 60;
    }
    static short DayOfWeekOrder(short Day, short Month, short Year)
    {

        short a = (14 - Month) / 12;
        short y = Year - a;
        short m = Month + (12 * a) - 2;

        // 0 sun 1 mon..etc
        return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
    }
    short DayOfWeekOrder()
    {

        short a = (14 - _Month) / 12;
        short y = _Year - a;
        short m = _Month + (12 * a) - 2;

        // 0 sun 1 mon..etc
        return (_Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
    }
    string DaysNames(short DayNumbr)
    {
        string arry[] = { "Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday" };
        return arry[DayNumbr];
    }
    static string MonthNames(short Month)
    {
        string MonthNames[12] = { "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };
        return (MonthNames[Month - 1]);
    }
    static void PrintMonthCalender(short Month, short Year)
    {
        short NumberOfDays = NumberOfDaysInMonth(Year, Month);
        short Order = DayOfWeekOrder(1, Month, Year);

        cout << "\n======================={" << MonthNames(Month) << "}=======================\n\n";
        cout << "Sun\tMon\tTus\tWed\tThu\tFri\tSat\n";

        int i;
        for (i = 0; i < Order; i++)
        {
            cout << "\t";
        }

        for (int j = 1; j <= NumberOfDays; j++)
        {
            cout << j << "\t";

            if (++i == 7) {

                i = 0;
                cout << "\n";
            }
        }
        cout << "\n\n===================================================" << endl;
    }
    void PrintMonthCalender()
    {
        short NumberOfDays = NumberOfDaysInMonth(_Year, _Month);
        short Order = DayOfWeekOrder(1, _Month, _Year);

        cout << "\n======================={" << MonthNames(_Month) << "}=======================\n\n";
        cout << "Sun\tMon\tTus\tWed\tThu\tFri\tSat\n";

        int i;
        for (i = 0; i < Order; i++)
        {
            cout << "\t";
        }

        for (int j = 1; j <= NumberOfDays; j++)
        {
            cout << j << "\t";

            if (++i == 7) {

                i = 0;
                cout << "\n";
            }
        }
        cout << "\n\n===================================================" << endl;
    }
    static void PrintYearClander(short Year)
    {
        cout << "\n===================================================\n";
        cout << "                  Clander " << Year;
        cout << "\n===================================================\n";
        for (int i = 1; i <= 12; i++)
        {
            PrintMonthCalender(i, Year);
            cout << endl;
        }
        return;
    }
    void PrintYearClander()
    {
        cout << "\n===================================================\n";
        cout << "                  Clander " << _Year;
        cout << "\n===================================================\n";
        for (int i = 1; i <= 12; i++)
        {
            PrintMonthCalender(i, _Year);
            cout << endl;
        }
        return;
    }
    static short TotalDaysFromBegining(short Days, short Month, short Year)
    {
        short TotalDays = 0;

        for (short i = 1; i <= Month - 1; i++)
        {
            TotalDays += NumberOfDaysInMonth(Year, i);
        }

        TotalDays += Days;

        return TotalDays;
    }
    short TotalDaysFromBegining()
    {
        short TotalDays = 0;

        for (short i = 1; i <= _Month - 1; i++)
        {
            TotalDays += NumberOfDaysInMonth(_Year, i);
        }

        TotalDays += _Day;

        return TotalDays;
    }
    static void DateFromTotalDays(short TotalDays, short Year)
    {
        short Month = 1;
        short Days = TotalDays;

        do
        {
            Days -= NumberOfDaysInMonth(Year, Month);
            Month++;

        } while (Days > NumberOfDaysInMonth(Year, Month));

        cout << Days << '/' << Month << '/' << Year << endl;
    }
    void DateFromTotalDays(short TotalDays)
    {
        short Month = 1;
        short Days = TotalDays;

        do
        {
            Days -= NumberOfDaysInMonth(_Year, Month);
            Month++;

        } while (Days > NumberOfDaysInMonth(_Year, Month));

        cout << Days << '/' << Month << '/' << _Year << endl;
    }
    static clsDate ReadDate()
    {
        clsDate Date;

        cout << "Enter Number Day : ";
        cin >> Date._Day;
        cout << "Enter Number Month : ";
        cin >> Date._Month;
        cout << "Enter Number Year : ";
        cin >> Date._Year;

        cout << endl;

        return Date;
    }
    static clsDate AddDaysToDate(short AddNumber, short Days, short Month, short Year)
    {
        clsDate Date;
        short AllDays = AddNumber + TotalDaysFromBegining(Days, Month, Year);

        while (AllDays != 0) {

            for (short i = 1; i <= 12; i++)
            {
                if (AllDays > NumberOfDaysInMonth(Year, i)) {

                    AllDays -= NumberOfDaysInMonth(Year, i);
                }
                else
                {
                    Date._Year = Year;
                    Date._Month = i;
                    Date._Day = AllDays;
                    return Date;
                }
            }
            Year++;
        }
    }
    clsDate AddDaysToDate(short AddNumber)
    {
        short AllDays = AddNumber + TotalDaysFromBegining(_Day, _Month, _Year);
        clsDate Date;

        while (AllDays != 0) {

            for (short i = 1; i <= 12; i++)
            {
                if (AllDays > NumberOfDaysInMonth(_Year, i)) {

                    AllDays -= NumberOfDaysInMonth(_Year, i);
                }
                else
                {
                    _Year = _Year;
                    _Month = i;
                    _Day = AllDays;
                    return Date;
                }
            }
            _Year++;
        }
    }
    static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
    {
        return (Date1._Year < Date2._Year) ? true : ((Date1._Year == Date2._Year) ? (Date1._Month < Date2._Month ? true : (Date1._Month == Date2._Month ? Date1._Day < Date2._Day : false)) : false);
    }
    bool IsDate1BeforeDate2(clsDate Date2)
    {
        clsDate Date1 = *this;
        return (Date1._Year < Date2._Year) ? true : ((Date1._Year == Date2._Year) ? (Date1._Month < Date2._Month ? true : (Date1._Month == Date2._Month ? Date1._Day < Date2._Day : false)) : false);
    }
    static bool IsDate1EquelDate2(clsDate Date1, clsDate Date2)
    {
        return ((Date1._Year == Date2._Year) ? (Date1._Month == Date2._Month ? (Date1._Day == Date2._Day ? true : false) : false) : false);
    }
    bool IsDate1EquelDate2(clsDate Date2)
    {
        IsDate1EquelDate2(*this, Date2);
    }
    static bool IsLastDayInMonth(short Day, short Month, short Year)
    {
        return (Day == NumberOfDaysInMonth(Year, Month)) ? true : false;
    }
    bool IsLastDayInMonth()
    {
        return (_Day == NumberOfDaysInMonth(_Year, _Month)) ? true : false;
    }
    static bool IsLastMonthInYear(short Month)
    {
        return (Month == 12) ? true : false;
    }
    bool IsLastMonthInYear()
    {
        return (_Month == 12) ? true : false;
    }
    static clsDate IncreaseDateByOneDay(clsDate& Date)
    {

        if (IsLastDayInMonth(Date._Day, Date._Month, Date._Year)) {

            if (IsLastMonthInYear(Date._Month)) {

                Date._Year++;
                Date._Month = 1;
                Date._Day = 1;
            }
            else {
                Date._Month++;
                Date._Day = 1;
            }
        }
        else {

            Date._Day++;
        }
        return Date;
    }
    clsDate IncreaseDateByOneDay()
    {
        clsDate Date = *this;

        if (IsLastDayInMonth(Date._Day, Date._Month, Date._Year)) {

            if (IsLastMonthInYear(Date._Month)) {

                Date._Year++;
                Date._Month = 1;
                Date._Day = 1;
            }
            else {
                Date._Month++;
                Date._Day = 1;
            }
        }
        else {

            Date._Day++;
        }
        return Date;
    }
    short TotalDays(clsDate Date)
    {
        short Total = 0;

        for (short i = Date._Month - 1; i <= 12; i++)
        {
            if (i == 0 || i == 1) {
                i++;
            }
            Total += NumberOfDaysInMonth(Date._Year, i);
        }
        Total += Date._Day;

        return Total;
    }
    short CalculateDifferenceInDay(clsDate& Date1, clsDate Date2, bool IncludeEndDay = false)
    {
        short D1 = 0;

        if (IsDate1BeforeDate2(Date1, Date2)) {

            for (short i = Date1._Year; i <= Date2._Year; i++)
            {
                D1 += TotalDays(Date1);
            }
        }

        (IncludeEndDay == true) ? D1++ : D1;

        return D1;
    }
    static clsDate SwapBetweenTowDate(clsDate& Date1, clsDate& Date2)
    {
        clsDate D;

        D = Date1;
        Date1 = Date2;
        Date2 = D;

        return D;
    }
    clsDate SwapBetweenTowDate(clsDate& Date2)
    {
        clsDate Date1 = *this;
        clsDate D;

        D = Date1;
        Date1 = Date2;
        Date2 = D;

        return D;
    }
    static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
    {
        int Days = 0;

        if (!clsDate::IsDate1BeforeDate2(Date1, Date2)) {

            SwapBetweenTowDate(Date1, Date2);
            while (IsDate1BeforeDate2(Date1, Date2))
            {
                Days++;
                Date1 = IncreaseDateByOneDay(Date1);
            }
            if (IncludeEndDay) {
                ++Days;
            }
            return IsDate1BeforeDate2(Date1, Date2) ? Days : Days * -1;
        }
        else {

            while (IsDate1BeforeDate2(Date1, Date2))
            {
                Days++;
                Date1 = IncreaseDateByOneDay(Date1);
            }
            if (IncludeEndDay) {
                ++Days;
            }
            return IsDate1BeforeDate2(Date1, Date2) ? Days * -1 : Days;
        }
    }
    int GetDifferenceInDays2(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
    {
        int Days = 0;
        short Flag = 1;

        if (!IsDate1BeforeDate2(Date1, Date2)) {
            SwapBetweenTowDate(Date1, Date2);
            Flag = -1;
        }
        while (IsDate1BeforeDate2(Date1, Date2))
        {
            Days++;
            Date1 = IncreaseDateByOneDay(Date1);
        }

        return (IncludeEndDay) ? ++Days * Flag : Days * Flag;
    }
    static clsDate GetSystemDate()
    {
        clsDate Date;

        time_t t = time(0);
        tm* now = localtime(&t);

        Date._Year = now->tm_year + 1900;
        Date._Month = now->tm_mon + 1;
        Date._Day = now->tm_mday;

        return Date;
    }
    static void PrintDate(clsDate Date)
    {
        cout << "{ " << Date._Day << '/' << Date._Month << '/' << Date._Year << " }" << endl;
    }
    void PrintDate()
    {
        cout << "{ " << _Day << '/' << _Month << '/' << _Year << " }" << endl;
    }
    clsDate IncreaseDateByXDays(clsDate& Date, short xDays)
    {
        for (short i = 0; i < xDays; i++)
        {
            IncreaseDateByOneDay(Date);
        }

        return Date;
    }
    static clsDate IncreasDateByOneWeek(clsDate& Date)
    {
        for (short i = 0; i < 7; i++)
        {
            Date.IncreaseDateByOneDay(Date);
        }
        return Date;
    }
    void IncreasDateByOneWeek()
    {
        IncreaseDateByOneDay(*this);
    }
    static clsDate IncreaclsDateByXWeek(clsDate& Date, short xWeeks)
    {
        for (short i = 0; i < xWeeks; i++)
        {
            IncreasDateByOneWeek(Date);
        }
        return Date;
    }
    void IncreaclsDateByXWeek(short xWeeks)
    {
        IncreaclsDateByXWeek(*this, xWeeks);
    }
    static clsDate IncreasDateByOneMonth(clsDate& Date)
    {
        if (Date._Month == 12) {
            Date._Month = 1;
            Date._Year++;
        }
        else {
            Date._Month++;
        }

        short NumberDays = NumberOfDaysInMonth(Date._Year, Date._Month);
        if (Date._Day > NumberDays) {

            Date._Day = NumberDays;
        }
        return Date;
    }
    void IncreasDateByOneMonth()
    {
        IncreasDateByOneMonth(*this);
    }
    static clsDate IncreasDateByXMonth(clsDate& Date, short xMonths)
    {
        for (short i = 0; i < xMonths; i++)
        {
            IncreasDateByOneMonth(Date);
        }
        return Date;
    }
    void IncreasDateByXMonth(short xMonths)
    {
        IncreasDateByXMonth(*this, xMonths);
    }
    static clsDate IncreaseDateByOneYear(clsDate& Date)
    {
        Date._Year++;
        return Date;
    }
    void IncreaseDateByOneYear()
    {
        IncreaseDateByOneYear(*this);
    }
    clsDate IncreaseDateByXYear(clsDate& Date, short xYears)
    {
        for (short i = 0; i < xYears; i++)
        {
            IncreaseDateByOneYear(Date);
        }
        return Date;
    }
    clsDate IncreaseDateByXYearFaster(clsDate& Date, short xYears)
    {
        Date._Year += xYears;
        return Date;
    }
    clsDate IncreaseDateByOneDecade(clsDate& Date)
    {
        Date._Year += 10;
        return Date;
    }
    clsDate IncreaseDateByXDecade(clsDate& Date, short xDecades)
    {
        for (short i = 0; i < xDecades; i++)
        {
            IncreaseDateByOneDecade(Date);
        }
        return Date;
    }
    clsDate IncreaseDateByXDecadeFaster(clsDate& Date, short xDecades)
    {
        Date._Year += xDecades * 10;
        return Date;
    }
    clsDate IncreaseDateByOneCentury(clsDate& Date)
    {
        Date._Year += 100;
        return Date;
    }
    clsDate IncreaseDateByOneMillennium(clsDate& Date)
    {
        Date._Year += 1000;
        return Date;
    }
    // Course 8 Problem #33 to 46 ..........
    clsDate DecreaseDateByOneDay(clsDate& Date)
    {
        if (Date._Day == 1) {
            if (Date._Month == 1) {

                Date._Year--;
                Date._Month = 12;
                Date._Day = 31;

            }
            else {

                Date._Month--;
                Date._Day = NumberOfDaysInMonth(Date._Year, Date._Month);
            }
        }
        else {

            Date._Day--;
        }

        return Date;
    }
    clsDate DecreaseDateByXDay(clsDate& Date, short xDays)
    {
        for (short i = 0; i < xDays; i++)
        {
            DecreaseDateByOneDay(Date);
        }
        return Date;
    }
    clsDate DecreaseDateByOneWeek(clsDate& Date)
    {
        for (short i = 0; i < 7; i++)
        {
            DecreaseDateByOneDay(Date);
        }
        return Date;
    }
    clsDate DecreaseDateByXWeek(clsDate& Date, short xWeenk)
    {
        for (short i = 0; i < xWeenk; i++)
        {
            DecreaseDateByOneWeek(Date);
        }
        return Date;
    }
    clsDate DecreaseDateByOneMonth(clsDate& Date)
    {
        if (Date._Month == 1) {

            Date._Month = 12;
            Date._Year--;
        }
        else {

            Date._Month--;
        }

        short ChackDaysInMonth = NumberOfDaysInMonth(Date._Year, Date._Month);

        if (Date._Day > ChackDaysInMonth) {

            Date._Day = ChackDaysInMonth;
        }

        return Date;
    }
    clsDate DecreaseDateByXMonth(clsDate& Date, short xMonth)
    {
        for (short i = 0; i < xMonth; i++)
        {
            DecreaseDateByOneMonth(Date);
        }
        return Date;
    }
    clsDate DecreaseDateByOneYear(clsDate& Date)
    {
        Date._Year--;
        return Date;
    }
    clsDate DecreaseDateByXYear(clsDate& Date, short xYear)
    {
        Date._Year -= xYear;
        return Date;
    }
    clsDate DecreaseDateByOneDecade(clsDate& Date)
    {
        Date._Year -= 10;
        return Date;
    }
    clsDate DecreaseDateByXDecade(clsDate& Date, short xDecade)
    {
        Date._Year -= xDecade * 10;
        return Date;
    }
    clsDate DecreaseDateByOneCentury(clsDate& Date)
    {
        Date._Year -= 100;
        return Date;
    }
    clsDate DecreaseDateByOneMillennium(clsDate& Date)
    {
        Date._Year -= 1000;
        return Date;
    }
    short DayOfWeekOrder(clsDate Date)
    {
        return DayOfWeekOrder(Date._Day, Date._Month, Date._Year);
    }
    void PrintDateNow(clsDate Date)
    {
        cout << "{ " << Date._Day << '/' << Date._Month << '/' << Date._Year << " }" << endl;
    }
    bool IsEndOfWeek(clsDate Date)
    {
        // There are Tow Method : 

        //return (DayOfWeekOrder(Date) == 6) ? true : false;
        return DayOfWeekOrder(Date) == 6;
    }
    bool IsWeekEnd(clsDate Date)
    {
        short DayIndex = DayOfWeekOrder(Date._Day, Date._Month, Date._Year);

        //return (DayIndex == 6 && DayIndex == 0) ? true : false;

        return (DayIndex == 5 || DayIndex == 6);
    }
    bool IsBusinessDay(clsDate Date)
    {
        //return (DayOfWeekOrder(Date) == 6 && DayOfWeekOrder(Date) == 0) ? false : true;
        //return (DayIndex == 6 && DayIndex == 0);

        return !IsWeekEnd(Date);
    }
    short DaysUntilTheEndOfWeek(clsDate Date)
    {
        /*Tow Method

        short Num = DayOfWeekOrder(Date);
        short Counter = 0;
        for (short i = Num ; i <= 6; i++)
        {
            Counter++;
        }

        return Counter;*/

        return 6 - DayOfWeekOrder(Date);
    }
    short DaysUntilTheEndOfMonth(clsDate Date)
    {
        clsDate EndOfDate;

        EndOfDate._Day = NumberOfDaysInMonth(Date._Year, Date._Month);
        EndOfDate._Month = Date._Month;
        EndOfDate._Year = Date._Year;

        return GetDifferenceInDays2(Date, EndOfDate, true);
    }
    short DaysUntilTheEndOfYear(clsDate Date)
    {
        clsDate EndOfDate;

        EndOfDate._Day = 31;
        EndOfDate._Month = 12;
        EndOfDate._Year = Date._Year;

        return GetDifferenceInDays2(Date, EndOfDate, true);
    }
    short ActucalVacationDays(clsDate Date1, clsDate Date2)
    {
        short DaysCount = 0;

        while (IsDate1BeforeDate2(Date1, Date2))
        {
            if (IsBusinessDay(Date1)) {
                DaysCount++;
            }
            IncreaseDateByOneDay(Date1);
        }

        return DaysCount;
    }
    clsDate VacationStartDay(clsDate& Date, short VacationDay)
    {
        short Y = 0;
        for (short i = 0; i < VacationDay + Y; i++)
        {
            if (IsWeekEnd(Date)) {
                Y++;
            }
            IncreaseDateByOneDay(Date);
        }
        return Date;
    }
    clsDate VacationStartDay2(clsDate& Date, short VacationDay)
    {
        short addedDays = 0;

        while (addedDays < VacationDay)
        {
            IncreaseDateByOneDay(Date);
            if (IsBusinessDay(Date)) {
                addedDays++;
            }
        }

        // for last day
        IncreaseDateByOneDay(Date);
        return Date;
    }
    bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
    {
        return (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EquelDate2(Date1, Date2));
    }
    enum enCompareDates { Before = -1, Equal = 0, After = 1 };
    static enCompareDates CompareDates(clsDate Date1, clsDate Date2)
    {
        if (IsDate1BeforeDate2(Date1, Date2))
            return enCompareDates::Before;

        if (IsDate1EquelDate2(Date1, Date2))
            return enCompareDates::Equal;

        return enCompareDates::After;
    }
    static bool IsValideDate(clsDate Date)
    {
        short DaysInMonth = NumberOfDaysInMonth(Date._Year, Date._Month);

        return Date._Day >= 1 && Date._Day <= DaysInMonth;
    }
    bool IsValideDate()
    {
        return IsValideDate(*this);
    }
    vector<short> SplitToVector(string S1, string delim)
    {
        vector<short>vNum;
        short pos = 0;
        string sNum = "";

        while ((pos = S1.find(delim)) != std::string::npos)
        {
            sNum = S1.substr(0, pos);
            if (sNum != " ")
            {
                vNum.push_back(stoi(sNum));
            }

            S1.erase(0, pos + delim.length());
        }

        if (S1 != " ")
            vNum.push_back(stoi(S1));

        return vNum;
    }
    clsDate StringToDate(vector<short>vNum)
    {
        clsDate Date;

        Date._Day = vNum[0];
        Date._Month = vNum[1];
        Date._Year = vNum[2];

        return Date;
    }
    static string DateToString(clsDate Date, string delim)
    {
        string ST;

        ST = to_string(Date._Day) + delim +
            to_string(Date._Month) + delim +
            to_string(Date._Year);

        return ST;
    }
    string DateToString()
    {
        return DateToString(*this, "/");
    }
    string RepleceString(string StringToReplace, string sRepalceTo, string& delim)
    {
        short pos = 0;
        short count = 0;
        char charcter = ' ';

        if (StringToReplace == "yyyy")
            charcter = 'y';
        if (StringToReplace == "dd")
            charcter = 'd';
        if (StringToReplace == "mm")
            charcter = 'm';

        for (short i = delim.find(StringToReplace); i <= delim.length(); i++)
        {
            if (delim[i] == charcter)
                count++;
            if (delim[i] != charcter) {
                delim.insert(i, sRepalceTo);
                pos = delim.find(StringToReplace);
                delim.erase(pos, count);
                break;
            }
        }

        return delim;
    }
    string RepleceString2(string StringToReplace, string sRepalceTo, string& S1)
    {
        short pos = S1.find(StringToReplace);

        while (pos != std::string::npos)
        {
            S1 = S1.replace(pos, StringToReplace.length(), sRepalceTo);
            pos = S1.find(StringToReplace);
        }

        return S1;
    }
    string FormateDate(clsDate Date, string delim)
    {
        string FormattingDateString = "";
        FormattingDateString = RepleceString2("dd", to_string(Date._Day), delim);
        FormattingDateString = RepleceString2("mm", to_string(Date._Month), delim);
        FormattingDateString = RepleceString2("yyyy", to_string(Date._Year), delim);

        return FormattingDateString;
    }
};

