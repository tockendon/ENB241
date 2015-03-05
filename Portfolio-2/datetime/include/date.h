/* date.h
 * ENB241 Portfolio 2
 *
 * Date class header
 *
 * Original: 28/02/2013 - C. Fookes
 * Modified: 08/04/2014 - D. Chen
 *
 *     DO NOT MODIFY
 */

#ifndef _DATE_H_
#define _DATE_H_


#include<string>
    using std::string;


const unsigned int NUM_MONTHS = 12;


class Date
{
public:
    // Initialise to today's date
    Date(void);

    // Initialise to the provided day/month/year values
    //   Value(s) set to 1 if invalid
    Date(const unsigned int day, const unsigned int month, const unsigned int year);

    // Initialise to date represented in string
    //   Pre-condition: Date stored in YYYY/MM/DD format
    //   Value(s) set to 1 if invalid
    Date(const string& dateString);

    // Return a string with date in YYYY/MM/DD format
    string toString() const;

    // Compare this date to otherDate
    //   Return a positive value if this date comes after otherDate
    //   Return a negative value if this date comes before otherDate
    //   Return 0 if both dates are equal
    int compare(const Date& otherDate) const;

    // Calculate the number of days between this date and otherDate
    //   Return a positive value if this date comes after otherDate
    //   Return a negative value if this date comes before otherDate
    //   Return 0 if both dates are equal
    int calcDays(const Date& toDate) const;

    // Advance the date by the provided number of days
    //   Number of days can be negative
    void increment(const int numDays = 1);

    // Check if the provided year is a leap year
    static bool isLeap(const unsigned int year);

    // Check if the date is a leap year
    bool isLeap() const
    {
        return isLeap(_year);
    }

private:
    // member variables
    unsigned int _day;      // 1-31, based on month
    unsigned int _month;    // 1-12
    unsigned int _year;     // any year

    // return number of days in _month
    unsigned int monthEnd() const;

    // set this Date to the C date passed in
    void setDate(const struct tm* date);

    // set this Date to d/m/y, setting invalid values to 1
    void setDate(const unsigned int day, const unsigned int month, const unsigned int year);

    // get number of days since 1/01/01
    unsigned int toDays() const;

    // set this Date to number of days since 1/01/01
    void fromDays(const unsigned int days);
};


#endif
