/* datetime.cpp
 * ENB241 Portfolio 2
 *
 * DateTime class implementation
 *
 *     IMPLEMENT DATETIME CLASS HERE
 *
 *  Student #: n8560641
 *  Name: Terrance Ockendon
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

#include <ctime>                // for time() function
#include <string>
#include <cmath>

#include "datetime.h"
#include "date.h"
#include "time1.h"

const int SECONDS_YEAR = 86400;
const int SECONDS_HOUR = 3600;
const int SECONDS_MINUTE = 60;

DateTime::DateTime(void) : _date(), _time()
{
}


DateTime::DateTime(const Date& date, const Time& time)
    : _date(date), _time(time)
{
}

DateTime::DateTime(const string& stringTime)
     : _date(stringTime.substr(0, 10)),
       _time(stringTime.substr(11, 8))
{
}


string DateTime::toString() const
{
    ostringstream ss;
    ss << _date.toString() << " "
       << _time.toString();

    return ss.str();
}


string DateTime::toString12() const
{
    ostringstream ss;
    ss << _date.toString() << " "
       << _time.toString12();

    return ss.str();
}


int DateTime::compare(const DateTime& otherTime) const
{
    int difference = _date.compare(otherTime._date);
    if(difference != 0)
        return difference;

    return _time.compare(otherTime._time);
}


int DateTime::calcSeconds(const DateTime& otherTime) const
{
    return (_date.calcDays(otherTime._date)*SECONDS_YEAR+
            _time.calcSeconds(otherTime._time));
}


int DateTime::calcDays(const DateTime& otherTime) const
{
    return (_date.calcDays(otherTime._date)+
            (int) floor(_time.calcSeconds(otherTime._time)/SECONDS_YEAR));
}


void DateTime::increment(const int numSec)
{
    int numDays = (int) floor(numSec/SECONDS_YEAR);
    int numHours = numSec%SECONDS_YEAR;

    _date.increment(numDays);
    int numRollover = _time.increment(numHours);
    if(numRollover != 0)
        _date.increment(numRollover);
}


void DateTime::incrementDays(const int numDays)
{
    _date.increment(numDays);
}
