/* datetime.h
 * ENB241 Portfolio 2
 *
 * DateTime class header
 *
 * 08/04/2014 - D. Chen
 *
 *     DO NOT MODIFY
 */

#ifndef _DATETIME_H_
#define _DATETIME_H_


#include <string>
#include <date.h>
#include <time1.h>


class DateTime
{
public:

// Public Function Declarations
//=============================================================================

    // DateTime - Initialise to current date and time of system clock.
    DateTime();


    // DateTime - Initialise to the provided year/month/day hour/minute/second values.
    //  Pre-condition:  System date time converted into date time structure.
    //  Post-condition: If invalid time value(s) are set to 0 and dates value(s) are set to 1.
    DateTime(const Date& date, const Time& time);


    // DateTime - Initialise date and time via string representation.
    //  Pre-condition:  Time stored in YYYY/MM/DD HH:MM:SS 24-hour string format.
    //  Post-condition: String stream is deconstructed into date and time variables.
    DateTime(const string& timeString);


    // toString - Return a string with time in YYYY/MM/DD HH:MM:SS 24-hour format.
    //  Pre-condition:  Date and time variables are valid.
    //  Post-condition: String stream is constructed with format YYYY/MM/DD HH:MM:SS.
    string toString() const;

    // tostring12 - Return a string with time in YYYY/MM/DD HH:MM:SS AM/PM 12-hour format.
    //  Pre-condition:  Date and time variables are valid.
    //  Post-condition: String stream is constructed with format YYYY/MM/DD HH:MM:SS XM.
    string toString12() const;

    // compare - Compare this time to otherTime.
    //  Pre-condition:  Date and time variables are valid.
    //  Post-condition: Return a positive value if this time comes after otherTime
    //                  Return a negative value if this time comes before otherTime
    //                  Return 0 if both dates are equal
    int compare(const DateTime& otherTime) const;

    // Calculate the number of seconds between this time and otherTime
    //  Pre-condition:  Date and time variables are valid.
    //  Post-condition: Return a positive value if this time comes after otherTime
    //                  Return a negative value if this time comes before otherTime
    //                  Return 0 if both dates are equal
    int calcSeconds(const DateTime& otherTime) const;

    // Calculate the number of days between this time and otherTime
    //   Only complete days are counted
    //   Return a positive value if this time comes after otherTime
    //   Return a negative value if this time comes before otherTime
    //   Return 0 if both dates are equal
    int calcDays(const DateTime& otherTime) const;

    // Advance the time by the provided number of seconds
    //   Number of seconds can be negative
    void increment(const int numSec = 1);

    // Advance the time by the provided number of days
    //   Number of days can be negative
    void incrementDays(const int numDays = 1);

private:
    Date _date;
    Time _time;
};


#endif
