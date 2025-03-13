#pragma once
#include <istream>
#include <string>
#include "clsDate.h"
using namespace std;

class clsPeriod
{
public:
    clsDate StartDate;
    clsDate EndDate;

    clsPeriod(clsDate Date1, clsDate Date2)
    {
        StartDate = Date1;
        EndDate = Date2;
    }
    clsPeriod()
    {
        StartDate = clsDate::GetSystemDate();
        EndDate = clsDate::GetSystemDate();
    }
    clsPeriod ReadPeriod()
    {
        clsPeriod Period;

        Period.StartDate = clsDate::ReadDate();
        Period.EndDate = clsDate::ReadDate();
        return Period;
    }
    static bool IsPeriodOverlap(clsPeriod Period1, clsPeriod Period2)
    {
        for (short i = Period1.StartDate._Day; i <= Period1.EndDate._Day; i++)
        {
            if (Period1.StartDate._Month == Period2.StartDate._Month || Period1.EndDate._Month == Period2.EndDate._Month)
                if (Period1.StartDate._Year == Period2.StartDate._Year || Period1.EndDate._Year == Period2.EndDate._Year)
                    if (Period2.StartDate._Day == i || Period2.EndDate._Day == i)
                        return true;
        }

        return false;
    }
    bool IsPeriodOverlap(clsPeriod Period2)
    {
        return IsPeriodOverlap(*this, Period2);
    }
    bool IsPeriodOverlap2(clsPeriod Period1, clsPeriod Period2)
    {
        if (clsDate::CompareDates(Period2.EndDate, Period1.StartDate) == clsDate::enCompareDates::Before
            ||
            clsDate::CompareDates(Period2.StartDate, Period1.EndDate) == clsDate::enCompareDates::After
            )
            return false;
        else
            return true;
    }
    short PeriodLengthInDays(clsPeriod Period, bool IncludeEndDate = false)
    {
        return clsDate::GetDifferenceInDays(Period.StartDate, Period.EndDate, IncludeEndDate);
    }
    bool IsDateWithinPeriod(clsPeriod Period, clsDate ChackDate)
    {
        for (short i = Period.StartDate._Day; i <= Period.EndDate._Day; i++)
        {
            if (ChackDate._Day == i) {
                if (Period.StartDate._Month == ChackDate._Month && Period.StartDate._Year == ChackDate._Year) {

                    return true;
                }
            }
        }
        return false;
    }
    bool IsDateWithinPeriod2(clsPeriod Period, clsDate ChackDate)
    {
        return !(clsDate::CompareDates(ChackDate, Period.StartDate) == clsDate::enCompareDates::Before // False
            ||
            clsDate::CompareDates(ChackDate, Period.EndDate) == clsDate::enCompareDates::After // false
            );
    }
    short CountOverlapDays(clsPeriod Period1, clsPeriod Period2)
    {
        short OverlapDays = 0;

        if (!IsPeriodOverlap(Period1, Period2)) {
            cout << "\nThere isn't Period\n";
            return OverlapDays;
        }

        for (short i = Period1.StartDate._Day; i <= Period1.EndDate._Day; i++)
        {
            if (Period1.StartDate._Month == Period2.StartDate._Month && Period1.StartDate._Year == Period2.StartDate._Year) {
                if (Period2.StartDate._Day == i) {
                    OverlapDays++;
                    return OverlapDays;
                }
                OverlapDays++;
            }
        }
    }
    short CountOverlapDays2(clsPeriod Period1, clsPeriod Period2)
    {
        short Period1Length = PeriodLengthInDays(Period1, true);
        short Period2Length = PeriodLengthInDays(Period2, true);
        short OverlapDays = 0;

        if (!IsPeriodOverlap(Period1, Period2))
            return 0;

        if (Period1Length < Period2Length) {

            while (clsDate::IsDate1BeforeDate2(Period1.StartDate, Period1.EndDate))
            {
                if (IsDateWithinPeriod2(Period2, Period1.StartDate))
                    OverlapDays++;

                clsDate::IncreaseDateByOneDay(Period1.StartDate);
            }
        }
        else {

            while (clsDate::IsDate1BeforeDate2(Period2.StartDate, Period2.EndDate))
            {
                if (IsDateWithinPeriod2(Period1, Period2.StartDate))
                    OverlapDays++;

                clsDate::IncreaseDateByOneDay(Period2.StartDate);
            }
        }

        return OverlapDays;
    }
    bool IsValideDate(clsDate Date)
    {
        short DaysInMonth = clsDate::NumberOfDaysInMonth(Date._Year, Date._Month);

        return Date._Day >= 1 && Date._Day <= DaysInMonth;
    }

};

