/* date.cpp
 * ENB241 Portfolio 2
 *
 * Date class implementation
 *
 * Original: 28/02/2013 - C. Fookes
 * Modified: 22/04/2014 - D. Chen
 *
 *     DO NOT MODIFY
 */

#include <iostream>
    using std::cerr;
    using std::endl;

#include <iomanip>
    using std::setw;
    using std::setfill;

#include <sstream>              // allows strings to be used like cin/cout
    using std::istringstream;   // read from string
    using std::ostringstream;   // write to string (or use stringstream for simultaneous read/write

#include <ctime>    // for time() function

#include <date.h>


static const unsigned int daysPerMonth[NUM_MONTHS + 1] =
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static const unsigned int cumDaysForMonth[NUM_MONTHS + 1] =
    {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};

const unsigned int CTIME_YEAR_OFFSET = 1900;
const unsigned int CTIME_MONTH_OFFSET = 1;
const unsigned int FEBRUARY = 2;
const unsigned int FEBRUARY_LEAP_YEAR_DAYS = 29;


// Set the Date to the current system date at the time of construction.
Date::Date(void)
{
    time_t currentTime = time(NULL);                    // get current system date and time
    struct tm* currentDate = localtime(&currentTime);   // convert it to a C date and time struct
    setDate(currentDate);
}


// Initialise to date represented in string
Date::Date(const string& stringDate)
{
    unsigned int day, month, year;              // temporary value storage
    char temp;                                  // read delimiting character
    istringstream ss(stringDate);               // construct input stringstream from string
    ss >> year >> temp >> month >> temp >> day; // read in values
    setDate(day, month, year);                  // set date
}


// Set the Date to the provided day/month/year values.
Date::Date(const unsigned int day, const unsigned int month, const unsigned int year)
{
    setDate(day, month, year);
}


// Return a string with Date in YYYY/MM/DD format
string Date::toString() const
{
    ostringstream ss;
    ss << _year << "/"
       << setw(2) << setfill('0') << _month << "/"  // set the width of the number to 2
       << setw(2) << setfill('0') << _day;          // pad empty spaces with 0s

    return ss.str();    // return string object inside the stringstream
}


// Calculate the number of days between this date and otherDate (date - otherDate)
int Date::calcDays(const Date& otherDate) const
{
    return toDays() - otherDate.toDays();   // convert to days since 1/1/1 and subtract
}


// Is year a leap year?
// Leap years are evenly divisible by 4, but not by 100 unless also divisible by 400.
bool Date::isLeap(const unsigned int year)
{
    if (year % 4 != 0) return false;
    if (year % 100 != 0) return true;
    if (year % 400 != 0) return false;
    return true;
}


// Compare this date to otherDate
//   Can be achieved using calcDays, but faster if number of days is not needed
int Date::compare(const Date& otherDate) const
{
    // if years are not the same return their difference
    int difference = _year - otherDate._year;
    if (difference != 0)
        return difference;

    // if months are not the same return their difference
    difference = _month - otherDate._month;
    if (difference != 0)
        return difference;

    // otherwise days determine the difference
    return _day - otherDate._day;
}


// Advance the date by the provided number of days.
void Date::increment(const int numDays)
{
    fromDays(toDays() + numDays);
}


// Utility Functions

// The last day of a month is?
unsigned int Date::monthEnd() const
{
    if (_month == FEBRUARY && isLeap(_year))
        return FEBRUARY_LEAP_YEAR_DAYS; // last day of Feb. in leap year
    else
        return daysPerMonth[_month];
}


// Set this Date's attributes from the provided time's struct attributes.
void Date::setDate(const struct tm* date)
{
    _day = date->tm_mday;
    _month = date->tm_mon + CTIME_MONTH_OFFSET;     // tm_mon == months since January; is 0 for Jan.
    _year = date->tm_year + CTIME_YEAR_OFFSET;      // tm_year == years since 1900
}


// Sets the date. Ensures only valid dates are entered.
void Date::setDate(const unsigned int day, const unsigned int month, const unsigned int year)
{
    if (year != 0) _year = year;
    else
    {
        _year = 1;
        cerr << "Year " << year << " is invalid. Year internal value set to 1." << endl;
    }

    // validate the month
    if (month != 0 && month <= NUM_MONTHS) _month = month;
    else
    {
        _month = 1;
        cerr << "Month " << month << " is invalid. Month internal value set to 1." << endl;
    }

    // validate the day
    if (day != 0 && day <= monthEnd()) _day = day;
    else
    {
        _day = 1;
        cerr << "Day " << day << " is invalid. Day internal value set to 1." << endl;
    }
}


// Calculates the number of days since 1/1/1
unsigned int Date::toDays() const
{
    unsigned int y = _year - 1;                                 // years since 1AD
    unsigned int days = 365 * y + y / 4 - y / 100 + y / 400;    // convert years to days
    days += cumDaysForMonth[_month - 1];            // add number of days since beginning of year for month
    days += _day - 1;                               // add days since beginning of month
    if (isLeap() && _month > FEBRUARY) ++days;      // add extra day if leap year
    return days;
}


// Get date given number of days since 1/1/1
void Date::fromDays(const unsigned int days)
{
    // get years
    _day = days;
    _year = 1 + (_day / 146097) * 400;   // 400 years
    _day %= 146097;
    _year += (_day / 36524) * 100;       // 100 years
    _day %= 36524;
    _year += (_day / 1461) * 4;          // 4 years
    _day %= 1461;
    _year += _day / 365;                 // 1 year
    _day %= 365;

    // fix for 31st Dec on leap years
    if (_day == 0)
    {
        unsigned int y = _year - 1;
        if (days == 365 * y + y / 4 - y / 100 + y / 400 - 1)
        {
            --_year;
            _month = 12;
            _day = 31;
            return;
        }
    }

    // get month
    _month = 1;
    while (_day >= monthEnd())
    {
        _day -= monthEnd();
        ++_month;
    }

    ++_day; // day
}
