/* time1.h
 * ENB241 Portfolio 2
 *
 * Time class header
 *
 *  Student #: n8560641
 *  Name: Terrance Ockendon
 *
 */

#ifndef _TIME1_H_
#define _TIME1_H_


#include <string>
    using std::string;


// Constants
//=============================================================================
const unsigned int NUM_HOURS = 24;
const unsigned int NUM_MINUTES = 60;
const unsigned int NUM_SECONDS = 60;

class Time
{
public:

// Public Function Declarations
//=============================================================================

    // Time - Initializes the time to system clock.
    Time(void);


    // Time - Initialise to the provided hour/minute/second values.
    //  Pre-condition:  System time converted into time structure.
    //  Post-condition: Value(s) set to 0 if invalid.
    Time(const unsigned int hour, const unsigned int minute, const unsigned int second);


    // Time - Initialise to time represented in string.
    //  Pre-condition:  Time stored in HH:MM:SS 24-hour string format.
    //  Post-condition: Value(s) set to 0 if invalid.
    Time(const string& timeString);


    // toString - Return a string with time in HH:MM:SS 24-hour format.
    //  Pre-condition:  Time variables are valid.
    //  Post-condition: String stream is constructed with format HH:MM:SS.
    string toString() const;


    // toString12 - Return a string with time in HH:MM:SS XM 12-hour format.
    //  Pre-condition:  Time variables are valid.
    //  Post-condition: String stream is constructed with format HH:MM:SS XM.
    string toString12() const;


    // compare - Compares this time to otherTime
    //   Pre-condition:  Both time variables are a valid time.
    //   Post-condition: Return a positive value if this time comes after otherTime.
    //                   Return a negative value if this time comes before otherTime.
    //                   Return 0 if both times are equal.
    int compare(const Time& otherTime) const;


    // calcSeconds - Calculate the number of seconds between this time and otherTime.
    //   Pre-condition:  Both time variables are a valid time.
    //   Post-condition: Return a positive value if this time comes after otherTime.
    //                   Return a negative value if this time comes before otherTime.
    //                   Return 0 if both times are equal.
    int calcSeconds(const Time& otherTime) const;


    // increment - Advance the time by the provided number of seconds.
    //   Pre-condition:  Time variable is a valid time.
    //   Post-Condition: Number of seconds can be negative.
    //                   Return the number of days rolled over from incrementing.
    int increment(const int numSec = 1);


private:

// Private Member Variables
//=============================================================================
    unsigned int _hour;     // 0-23
    unsigned int _minute;   // 0-59
    unsigned int _second;   // 0-59


    // setTime - set this Time to h/m/s, setting invalid values to 0
    void setTime(const unsigned int hour, const unsigned int minute, const unsigned int second);
};

#endif
