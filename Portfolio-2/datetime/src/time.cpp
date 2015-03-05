/* time.cpp
 * ENB241 Portfolio 2
 *
 * Time class implementation
 *
 *     IMPLEMENT TIME CLASS HERE
 *
 *  Student #: n8560641
 *  Name: Terrance Ockendon
 */

#include <iostream>
using namespace std;

#include <iomanip>
using std::setw;
using std::setfill;

#include <sstream>
using std::istringstream;
using std::ostringstream;

#include <ctime>
#include <cmath>
#include <time1.h>

const int SECONDS_YEAR = 86400;
const int SECONDS_HOUR = 3600;
const int SECONDS_MINUTE = 60;

Time::Time(void)
//-----------------------------------------------------------------------------
{
    time_t currentTime = time(NULL);
    struct tm* currentDate = localtime(&currentTime);
    _second = currentDate->tm_sec;
    _minute = currentDate->tm_min;
    _hour = currentDate->tm_hour;
}

Time::Time(const unsigned int hour, const unsigned int minute, const unsigned int second)
//-----------------------------------------------------------------------------
{
    setTime(hour, minute, second);
}

Time::Time(const string& stringTime)
//-----------------------------------------------------------------------------
{
    unsigned int hour, minute, second;
    char temp;
    istringstream ss(stringTime);
    ss >> hour >> temp >> minute >> temp >> second;
    setTime(hour, minute, second);
}

string Time::toString() const
//-----------------------------------------------------------------------------
{
    ostringstream ss;
    ss << setw(2) << setfill('0') << _hour << ":"
       << setw(2) << setfill('0') << _minute << ":"
       << setw(2) << setfill('0') << _second;

    return ss.str();
}

string Time::toString12() const
//-----------------------------------------------------------------------------
{
    ostringstream ss;
    if(_hour == 12)
    {
        ss
                << setw(2) << setfill('0') << _hour << ":"
                << setw(2) << setfill('0') << _minute << ":"
                << setw(2) << setfill('0') << _second << " PM";
    }
    else if(_hour == 00)
    {
        ss
                << setw(2) << setfill('0') << "12" << ":"
                << setw(2) << setfill('0') << _minute << ":"
                << setw(2) << setfill('0') << _second << " AM";
    }
    else if(_hour > 12 && _hour < 24  )
    {
        ss
                << setw(2) << setfill('0') << (_hour-12) << ":"
                << setw(2) << setfill('0') << _minute << ":"
                << setw(2) << setfill('0') << _second << " PM";
    }
    else if(_hour > 00 && _hour < 12)
    {
        ss
                << setw(2) << setfill('0') << _hour << ":"
                << setw(2) << setfill('0') << _minute << ":"
                << setw(2) << setfill('0') << _second << " AM";
    }
    return ss.str();
}

int Time::compare(const Time& otherTime) const
//-----------------------------------------------------------------------------
{
    int difference = _hour - otherTime._hour;
    if (difference != 0)
        return difference;

    difference = _minute - otherTime._minute;
    if (difference != 0)
        return difference;

    return _second - otherTime._second;
}

int Time::calcSeconds(const Time& otherTime) const
//-----------------------------------------------------------------------------
{
    return ((_hour*SECONDS_HOUR)+(_minute*SECONDS_MINUTE)+(_second)) -
           ((otherTime._hour*(SECONDS_HOUR))+(otherTime._minute*SECONDS_MINUTE)+(otherTime._second));
}

int Time::increment(const int numSec)
//-----------------------------------------------------------------------------
{
    const int secondsDay = (SECONDS_YEAR);
    const int secondsBefore = ((_hour*(SECONDS_HOUR))+(_minute*SECONDS_MINUTE)+(_second));
    const int secondsAfter = secondsBefore + numSec;

    int numDay = 0;
    int numSecRem = 0;

    numDay = (int) ceil(secondsAfter/secondsDay);
    numSecRem = (int) floor(secondsAfter%secondsDay);

    if(numSecRem < 0)
    {
        numDay = numDay - 1;
        _hour =   (unsigned int) floor((secondsDay+numSecRem)/SECONDS_HOUR);
        _minute = (unsigned int) floor(((secondsDay+numSecRem)%SECONDS_HOUR)/SECONDS_MINUTE);
        _second = (unsigned int) floor(((secondsDay+numSecRem)%SECONDS_HOUR)%SECONDS_MINUTE);
    }
    else if (numSecRem > -1)
    {
        _hour =   (int) floor(numSecRem/SECONDS_HOUR);
        _minute = (int) floor((numSecRem%SECONDS_HOUR)/SECONDS_MINUTE);
        _second = (int) floor((numSecRem%SECONDS_HOUR)%SECONDS_MINUTE);
    }

    return numDay;
}


void Time::setTime(const unsigned int hour, const unsigned int minute, const unsigned int second)
//-----------------------------------------------------------------------------
{
    if (hour < NUM_HOURS) _hour = hour;
    else
    {
        _hour = 0;
        cerr << "Hour " << hour << " is invalid. Hour internal value set to 0." << endl;
    }

    if (minute < NUM_MINUTES) _minute = minute;
    else
    {
        _minute = 0;
        cerr << "Minute " << minute << " is invalid. Minute internal value set to 0." << endl;
    }

    if (second < NUM_SECONDS) _second = second;
    else
    {
        _second = 0;
        cerr << "Second " << second << " is invalid. Second internal value set to 0." << endl;
    }
}
