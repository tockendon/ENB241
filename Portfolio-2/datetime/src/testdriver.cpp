/* testdriver.cpp
 * ENB241 Portfolio 2
 *
 * Time and DateTime class test driver
 *
 *     IMPLEMENT TEST DRIVER HERE
 *
 *  Student #: n8560641
 *  Name: Terrance Ockendon
 */
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <iomanip>
using std::setw;

#include <string>
using std::string;

#include <date.h>
#include <time1.h>
#include <datetime.h>

// ANSI colour codes
//   These strings are interpreted by the terminal as a change colour command
const char* DEFAULT = "\033[0m";
const char* GREEN   = "\033[32m";
const char* RED     = "\033[31m";
const char* YELLOW  = "\033[33m";


// Displays PASS or FAIL given true or false
bool dispPass(bool pass)
{
    if (pass) cout << GREEN << "PASS" << DEFAULT << endl;
    else      cout << RED   << "FAIL" << DEFAULT << endl;
    return pass;
}


// Test function prototypes
// Time functions
bool testTimePrereqs();
void testTimeConstructors();
void testTimeCompare();
void testTimeCalcSeconds();
void testTimeIncrement();
// DateTime functions
bool testDateTimePrereqs();
void testDateTimeConstructors();
void testDateTimeCompare();
void testDateTimeCalcSeconds();
void testDateTimeCalcDays();
void testDateTimeSecIncrement();
void testDateTimeDayIncrement();

int main(int argc, char *argv[])
{
    cout << "Time Class and DateTime Class Test Driver" << endl;
    cout << endl;
    // Tests string constructor + toString
    // Program exits if failed as they are required for other tests
    if (!testTimePrereqs())
    {
        cout << "Prerequisite functions failed.\nAborting tests." << endl;
        return 1;
    }
    cout << endl;

    // Perform tests

    // Time tests
    testTimeConstructors();
    cout << endl;

    testTimeCompare();
    cout << endl;

    testTimeCalcSeconds();
    cout << endl;

    testTimeIncrement();
    cout << endl;
    cout << endl;

    // Date tests
    testDateTimePrereqs();
    cout << endl;

    testDateTimeConstructors();
    cout << endl;

    testDateTimeCompare();
    cout << endl;

    testDateTimeCalcSeconds();
    cout << endl;

    testDateTimeCalcDays();
    cout << endl;

    testDateTimeSecIncrement();
    cout << endl;

    testDateTimeDayIncrement();
    cout << endl;

    cout << "--END--" << endl;
    return 0;
}


bool testTimePrereqs()
//-----------------------------------------------------------------------------
{
    // Tests default constructor
    cout << YELLOW << "Time::Time()" << DEFAULT << endl;
    Time currentTime;
    cout << "Time should be current time: " << currentTime.toString() << endl;
    cout << endl;

    cout << YELLOW << "Time::Time(unsigned int, unsigned int, unsigned int)" << DEFAULT << endl;
    cout << "    Uses: " << YELLOW << "Time::setTime(unsigned int, unsigned int, unsigned int)" << DEFAULT << endl;
    Time setTime(12, 02, 03);
    cout << "Setting time with Time(12:02:03): " << setTime.toString() << " ";
    dispPass(setTime.toString() == "12:02:03");
    cout << endl;

    string testTime[] = {"00:00:00", "23:59:59", "11:59:59", "12:00:00", "12:00:01", "00:00:01"};
    cout << YELLOW << "Time::Time(string)" << DEFAULT << endl;
    cout << "    Uses: " << YELLOW << "Time::setTime(unsigned int, unsigned int, unsigned int)" << DEFAULT << endl;
    cout << YELLOW << "Time::toString()" << DEFAULT << endl;

    cout << "String   Actual   Pass?" << endl;
    cout << "-------- -------- --------" << endl;
    for (int i = 0; i < (sizeof(testTime) / sizeof(string)); ++i)
    {
        Time timeObj(testTime[i]);
        string x = timeObj.toString();
        cout << testTime[i] << " "
             << x << " ";
        if (dispPass(x == testTime[i])) continue;

        return false;
    }
    cout << endl;
    string check24[]    = {"12:00:00 AM", "11:59:59 PM", "11:59:59 AM", "12:00:00 PM", "12:00:01 PM", "12:00:01 AM"};
    cout << YELLOW << "Time::toString12()" << DEFAULT << endl;

    cout << "String   Expected    Actual      Pass??" << endl;
    cout << "-------- ----------- ----------- --------" << endl;
    for (int i = 0; i < (sizeof(testTime) / sizeof(string)); ++i)
    {
        Time timeObj(testTime[i]);
        string x = timeObj.toString12();
        cout << testTime[i] << " "
             << check24[i] << " "
             << x << " ";
        if (dispPass(x == check24[i])) continue;

        return false;
    }
    return true;
}


void testTimeConstructors()
//-----------------------------------------------------------------------------
{
    // Tests constructor setting 24 hour time
    cout << YELLOW << "Time::Time(string)" << DEFAULT << endl;
    cout << "    Uses: " << YELLOW << "Time::toString()" << DEFAULT << endl;

    // Construct invalid 24 hour Times
    cout << "Constructing invalid 24 hour times:" << endl;
    string testTime24[]    = {"24:31:24", "23:60:59", "23:59:60"};
    string expected24[]    = {"00:31:24", "23:00:59", "23:59:00"};
    string invalidType24[] = {"Hour",     "Minute",   "Second"};
    for (int i = 0; i < (sizeof(testTime24) / sizeof(string)); ++i)
    {
        cout << "  Invalid " << invalidType24[i] << " " << testTime24[i] << endl;
        cerr << "  ";
        Time invalidTime24(testTime24[i]);
        cout << "  " << invalidTime24.toString() << " ";
        dispPass(invalidTime24.toString() == expected24[i]);
    }
    cout << endl;

    // Tests constructor setting 12 hour XM time
    cout << YELLOW << "Time::Time(string)" << DEFAULT << endl;
    cout << "    Uses: " << YELLOW << "Time::toString12()" << DEFAULT << endl;

    // Construct invalid 12 hour XM Times
    cout << "Constructing invalid 12 hour times:" << endl;
    string testTime12[]    = {"24:59:59",    "23:60:59",    "01:59:60"};
    string expected12[]    = {"12:59:59 AM", "11:00:59 PM", "01:59:00 AM"};
    string invalidType12[] = {"Hour",        "Minute",      "Second"};
    for (int i = 0; i < (sizeof(testTime12) / sizeof(string)); ++i)
    {
        cout << "  Invalid " << invalidType12[i] << " " << testTime12[i] << endl;
        cerr << "  ";
        Time invalidTime12(testTime12[i]);
        cout << "  " << invalidTime12.toString12() << " ";
        dispPass(invalidTime12.toString12() == expected12[i]);
    }
}


void testTimeCompare()
//-----------------------------------------------------------------------------
{
    // Test different hours, minutes, seconds and equal times
    string startTime[]    = {"12:00:00", "12:00:00", "12:00:00", "15:11:21", "12:30:01"};
    string otherTime[]    = {"11:00:00", "13:00:00", "11:11:00", "15:11:21", "12:30:01"};
    int expectedSign[]    = { 1,         -1,           1,          0,          0};

    cout << YELLOW << "int Time::compare(Time&)" << DEFAULT << endl;
    cout << "Time     Other    Expected Actual   Pass?" << endl;
    cout << "-------- -------- -------- -------- --------" << endl;
    for (int i = 0; i < (sizeof(startTime) / sizeof(string)); ++i)
    {
        Time testTime(startTime[i]);
        Time testTime2(otherTime[i]);
        int x = testTime.compare(testTime2);
        cout << startTime[i] << " "                        // time
             << otherTime[i] << " "                        // other time
             << setw(8) << expectedSign[i] << " "          // expected sign
             << setw(8) << x << " ";                       // actual result
        dispPass(((x > 0) - (x < 0)) == expectedSign[i]);  // ((x > 0) - (x < 0)) gets the sign of x (-1/0/1)

        // test inverted cases
        if (expectedSign[i] != 0)
        {
            int y = testTime2.compare(testTime);
            cout << otherTime[i] << " "
                 << startTime[i] << " "
                 << setw(8) << -expectedSign[i] << " "
                 << setw(8) << y << " ";
            dispPass(((y > 0) - (y < 0)) == -expectedSign[i]);
        }
    }
}


void testTimeCalcSeconds()
//-----------------------------------------------------------------------------
{
    // Test same date, different years (with and without leap years)
    string startTime[]    = {"12:00:01", "15:50:01", "23:05:02"};
    string otherTime[]    = {"12:00:01", "15:40:00", "01:01:03"};
    int expectedDiff[]    = {         0,        601,      79439};

    cout << YELLOW << "int Time::calcSeconds(Time&)" << DEFAULT << endl;
    cout << "Time     Other    Expected Actual   Pass?" << endl;
    cout << "-------- -------- -------- -------- --------" << endl;
    for (int i = 0; i < (sizeof(startTime) / sizeof(string)); ++i)
    {
        Time testTime(startTime[i]);
        Time testTime2(otherTime[i]);
        int x = testTime.calcSeconds(testTime2);
        cout << startTime[i] << " "
             << otherTime[i] << " "
             << setw(8) << expectedDiff[i] << " "
             << setw(8) << x << " ";
        dispPass(x == expectedDiff[i]);

        // test inverted cases
        if (expectedDiff[i] != 0)
        {
            int y = testTime2.calcSeconds(testTime);
            cout << otherTime[i] << " "
                 << startTime[i] << " "
                 << setw(8) << -expectedDiff[i] << " "
                 << setw(8) << y << " ";
            dispPass(y == -expectedDiff[i]);
        }
    }
}


void testTimeIncrement()
//-----------------------------------------------------------------------------
{
    // Test simple increment, increment nothing, advance past end of month, end of year, and many years
    string startTime[]    = {"12:00:00", "23:59:59", "02:01:11", "12:00:00", "12:00:00"};
    int increment[]       = {         1,          1,      -7272,     864000,    -864000};
    string expectedTime[] = {"12:00:01", "00:00:00", "23:59:59", "12:00:00", "12:00:00"};
    int expectedDay[]     = {         0,          1,         -1,         10,        -10};

    cout << YELLOW << "void Time::increment(int)" << DEFAULT << endl;
    cout << "                   Expected Actual   Expected Actual           " << endl;
    cout << "Time     Increment Time     Time     Day(s)   Day(s)   Pass?   " << endl;
    cout << "-------- --------- -------- -------- -------- -------- --------" << endl;
    for (int i = 0; i < (sizeof(startTime) / sizeof(string)); ++i)
    {
        Time testTime(startTime[i]);
        int y = testTime.increment(increment[i]);
        string x = testTime.toString();
        cout << startTime[i] << " "
             << setw(9) << increment[i] << " "
             << expectedTime[i] << " "
             << x << " "
             << setw(8) << expectedDay[i] << " "
             << setw(8) << y << " ";
        dispPass(x == expectedTime[i] && y == expectedDay[i]);
    }
}

bool testDateTimePrereqs()
//-----------------------------------------------------------------------------
{
    // Tests default constructor
    cout << YELLOW << "DateTime::DateTime()" << DEFAULT << endl;
    Time currentDateTime;
    cout << "Date and time should be current date and time: " << currentDateTime.toString() << endl;
    cout << endl;

    cout << YELLOW << "DateTime::DateTime(Date&, Time&)" << DEFAULT << endl;
    cout << "    Uses: " << YELLOW << "Time::setTime.(unsigned int, unsigned int, unsigned int)" << DEFAULT << endl;
    cout << "          " << YELLOW << "Date::setDate.(unsigned int, unsigned int, unsigned int)" << DEFAULT << endl;
    Date myDate(04, 11, 2014);
    Time myTime(10, 02, 03);
    DateTime setDateTime(myDate, myTime);
    cout << "Setting date and time with DateTime(2014/11/04 10:02:03): " << endl << setDateTime.toString() << " ";
    dispPass(setDateTime.toString() == "2014/11/04 10:02:03");
    cout << endl;

    cout << YELLOW << "DateTime::DateTime(string)" << DEFAULT << endl;
    cout << "    Uses: " << YELLOW << "Time::setTime(unsigned int, unsigned int, unsigned int)" << DEFAULT << endl;
    cout << "          " << YELLOW << "Date::setDate(unsigned int, unsigned int, unsigned int)" << DEFAULT << endl;
    cout << YELLOW << "DateTime::toString()" << DEFAULT << endl;
    string testDateTime[]  = {"1000/01/01 00:00:00",
                              "1999/12/31 23:59:59",
                              "2000/01/01 00:00:00",
                              "2999/12/12 23:59:59",
                              "3000/01/01 00:00:00"
                             };

    cout << "String              Actual              Pass?" << endl;
    cout << "------------------- ------------------- --------" << endl;
    for (int i = 0; i < (sizeof(testDateTime) / sizeof(string)); ++i)
    {
        DateTime datetimeObj(testDateTime[i]);
        string x = datetimeObj.toString();
        cout << testDateTime[i] << " "
             << x << " ";
        if (dispPass(x == testDateTime[i])) continue;

        return false;
    }
    cout << endl;
    cout << YELLOW << "DateTime::DateTime(string)" << DEFAULT << endl;
    cout << "    Uses: " << YELLOW << "Time::setTime(unsigned int, unsigned int, unsigned int)" << DEFAULT << endl;
    cout << "          " << YELLOW << "Date::setDate(unsigned int, unsigned int, unsigned int)" << DEFAULT << endl;
    cout << YELLOW << "DateTime::toString12()" << DEFAULT << endl;
    string testDateTime2[]  = {"1000/01/01 00:00:00",
                               "1999/12/31 23:59:59",
                               "2000/02/29 00:00:00",
                               "2999/12/12 23:59:59",
                               "3000/01/01 00:00:00"
                              };
    string expectedDateTime[]  = {"1000/01/01 12:00:00 AM",
                                  "1999/12/31 11:59:59 PM",
                                  "2000/02/29 12:00:00 AM",
                                  "2999/12/12 11:59:59 PM",
                                  "3000/01/01 12:00:00 AM"
                                 };
    cout << "String              Actual                 Pass?" << endl;
    cout << "------------------- ---------------------- --------" << endl;
    for (int i = 0; i < (sizeof(testDateTime) / sizeof(string)); ++i)
    {
        DateTime datetimeObj(testDateTime2[i]);
        string x = datetimeObj.toString12();
        cout << testDateTime2[i] << " "
             << x << " ";
        if (dispPass(x == expectedDateTime[i])) continue;

        return false;
    }
}

void testDateTimeConstructors()
//-----------------------------------------------------------------------------
{
    // Tests constructor setting 24 hour time
    cout << YELLOW << "Time::DateTime(string)" << DEFAULT << endl;
    cout << "    Uses: " << YELLOW << "DateTime::toString()" << DEFAULT << endl;

    // Construct invalid 24 hour Times
    cout << "Constructing invalid 24 hour times:" << endl;
    string testDateTime24[]  = {"2000/01/01 24:59:59",
                                "2000/13/01 00:00:00",
                                "2000/01/01 23:60:59",
                                "2000/02/30 00:00:00",
                                "2000/02/28 23:59:60"
                               };
    string expectedDateTime24[]  = {"2000/01/01 00:59:59",
                                    "2000/01/01 00:00:00",
                                    "2000/01/01 23:00:59",
                                    "2000/02/01 00:00:00",
                                    "2000/02/28 23:59:00"
                                   };
    string invalidType24[] = {"Year", "Hour", "Month", "Minute", "Day", "Second"};
    for (int i = 0; i < (sizeof(testDateTime24) / sizeof(string)); ++i)
    {
        cout << "  Invalid " << invalidType24[i] << " " << testDateTime24[i] << endl;
        cerr << "  ";
        DateTime invalidDateTime24(testDateTime24[i]);
        cout << "  " << invalidDateTime24.toString() << " ";
        dispPass(invalidDateTime24.toString() == expectedDateTime24[i]);
    }
    cout << endl;

    // Tests constructor setting 12 hour time
    cout << YELLOW << "Time::DateTime(string)" << DEFAULT << endl;
    cout << "    Uses: " << YELLOW << "DateTime::toString12()" << DEFAULT << endl;

    // Construct invalid 24 hour Times
    cout << "Constructing invalid 12 hour times:" << endl;
    string testDateTime12[]  = {"2000/01/01 24:59:59",
                                "2000/13/01 00:00:00",
                                "2000/01/01 23:60:59",
                                "2000/02/30 00:00:00",
                                "2000/02/28 23:59:60"
                               };
    string expectedDateTime12[]  = {"2000/01/01 12:59:59 AM",
                                    "2000/01/01 12:00:00 AM",
                                    "2000/01/01 11:00:59 PM",
                                    "2000/02/01 12:00:00 AM",
                                    "2000/02/28 11:59:00 PM"
                                   };
    string invalidType12[] = {"Year", "Hour", "Month", "Minute", "Day", "Second"};
    for (int i = 0; i < (sizeof(testDateTime12) / sizeof(string)); ++i)
    {
        cout << "  Invalid " << invalidType12[i] << " " << testDateTime12[i] << endl;
        cerr << "  ";
        DateTime invalidDateTime12(testDateTime12[i]);
        cout << "  " << invalidDateTime12.toString12() << " ";
        dispPass(invalidDateTime12.toString12() == expectedDateTime12[i]);
    }
}

void testDateTimeCompare()
//-----------------------------------------------------------------------------
{
    // Test different years, months, days, hours, minutes, seconds and equal times
    string startDateTime[]    = {"2002/01/13 12:00:00",
                                 "2002/01/13 12:00:00",
                                 "2002/01/13 12:00:00",
                                 "2002/01/13 12:00:00",
                                 "2002/01/13 12:00:00",
                                 "2002/01/13 12:00:00",
                                };
    string otherDateTime[]    = {"2003/01/11 12:00:00",
                                 "2002/02/11 12:00:00",
                                 "2002/01/14 12:00:00",
                                 "2002/01/13 13:00:00",
                                 "2002/01/13 12:01:00",
                                 "2002/01/13 12:00:01",
                                };
    int expectedSign[]    = {-1,-1,-1,-1,-1,-1};

    cout << YELLOW << "int DateTime::compare(DateTime&)" << DEFAULT << endl;
    cout << "Date       Time     Other               Expected Actual   Pass?   " << endl;
    cout << "------------------- ------------------- -------- -------- --------" << endl;
    for (int i = 0; i < (sizeof(startDateTime) / sizeof(string)); ++i)
    {
        DateTime testDateTime(startDateTime[i]);
        DateTime testDateTime2(otherDateTime[i]);
        int x = testDateTime.compare(testDateTime2);
        cout << startDateTime[i] << " "                    // time
             << otherDateTime[i] << " "                    // other time
             << setw(8) << expectedSign[i] << " "          // expected sign
             << setw(8) << x << " ";                       // actual result
        dispPass(((x > 0) - (x < 0)) == expectedSign[i]);  // ((x > 0) - (x < 0)) gets the sign of x (-1/0/1)

        // test inverted cases
        if (expectedSign[i] != 0)
        {
            int y = testDateTime2.compare(testDateTime);
            cout << otherDateTime[i] << " "
                 << startDateTime[i] << " "
                 << setw(8) << -expectedSign[i] << " "
                 << setw(8) << y << " ";
            dispPass(((y > 0) - (y < 0)) == -expectedSign[i]);
        }
    }
}

void testDateTimeCalcSeconds()
//-----------------------------------------------------------------------------
{
    // Test same date, different years (with and without leap years)
    string startDateTime[]    = {"2000/01/01 00:00:00",
                                 "2001/01/01 00:00:00",
                                 "2001/02/01 00:00:00",
                                 "2001/02/02 00:00:00",
                                 "2001/02/02 01:00:00",
                                 "2001/02/02 01:01:00"
                                };
    string otherDateTime[]    = {"2001/01/01 00:00:00",
                                 "2001/02/01 00:00:00",
                                 "2001/02/02 00:00:00",
                                 "2001/02/02 01:00:00",
                                 "2001/02/02 01:01:00",
                                 "2001/02/02 01:01:01"
                                };
    int expectedDiff[]        = {-31622400,-2678400,-86400,-3600,-60,-1};

    cout << YELLOW << "int DateTime::calcSeconds(DateTime&)" << DEFAULT << endl;
    cout << "Date       Time     Other               Expected  Actual    Pass?   " << endl;
    cout << "------------------- ------------------- --------- --------- --------" << endl;
    for (int i = 0; i < (sizeof(startDateTime) / sizeof(string)); ++i)
    {
        DateTime testDateTime(startDateTime[i]);
        DateTime testDateTime2(otherDateTime[i]);
        int x = testDateTime.calcSeconds(testDateTime2);
        cout << startDateTime[i] << " "
             << otherDateTime[i] << " "
             << setw(9) << expectedDiff[i] << " "
             << setw(9) << x << " ";
        dispPass(x == expectedDiff[i]);

        // test inverted cases
        if (expectedDiff[i] != 0)
        {
            int y = testDateTime2.calcSeconds(testDateTime);
            cout << otherDateTime[i] << " "
                 << startDateTime[i] << " "
                 << setw(9) << -expectedDiff[i] << " "
                 << setw(9) << y << " ";
            dispPass(y == -expectedDiff[i]);
        }
    }
}

void testDateTimeCalcDays()
//-----------------------------------------------------------------------------
{
    // Test same date, different years (with and without leap years)
    string startDateTime[]    = {"2000/01/01 00:00:00",
                                 "2001/01/01 00:00:00",
                                 "2001/02/01 00:00:00",
                                 "2000/02/29 00:00:00",
                                };
    string otherDateTime[]    = {"2001/01/01 00:00:00",
                                 "2001/02/01 00:00:00",
                                 "2001/02/28 00:00:00",
                                 "2001/02/28 23:59:59",
                                };
    int expectedDiff[]    = {-366, -31, -27, -365};

    cout << YELLOW << "int DateTime::calcDays(DateTime&)" << DEFAULT << endl;
    cout << "Date       Time     Other               Expected  Actual    Pass?   " << endl;
    cout << "------------------- ------------------- --------- --------- --------" << endl;
    for (int i = 0; i < (sizeof(startDateTime) / sizeof(string)); ++i)
    {
        DateTime testDateTime(startDateTime[i]);
        DateTime testDateTime2(otherDateTime[i]);
        int x = testDateTime.calcDays(testDateTime2);
        cout << startDateTime[i] << " "
             << otherDateTime[i] << " "
             << setw(9) << expectedDiff[i] <<  " "
             << setw(9) << x << " ";
        dispPass(x == expectedDiff[i]);

        // test inverted cases
        if (expectedDiff[i] != 0)
        {
            int y = testDateTime2.calcDays(testDateTime);
            cout << otherDateTime[i] << " "
                 << startDateTime[i] << " "
                 << setw(9) << -expectedDiff[i] << " "
                 << setw(9) << y << " ";
            dispPass(y == -expectedDiff[i]);
        }
    }
}

void testDateTimeSecIncrement()
//-----------------------------------------------------------------------------
{
    // Test simple increment, increment nothing, advance past end of month, end of year, and many years
    string startDateTime[]    = {"2001/01/01 00:00:00",
                                 "2001/01/01 00:00:00",
                                 "2001/01/01 00:00:00",
                                 "2001/01/01 00:00:00",
                                 "2001/01/01 00:00:00",
                                 "2001/01/01 00:00:00"
                                };
    int increment[]           = {31536000, 2678400, 86400, 3600, 60, 1};
    string expectedDateTime[] = {"2002/01/01 00:00:00",
                                 "2001/02/01 00:00:00",
                                 "2001/01/02 00:00:00",
                                 "2001/01/01 01:00:00",
                                 "2001/01/01 00:01:00",
                                 "2001/01/01 00:00:01"
                                };

    cout << YELLOW << "void DateTime::increment(int)" << DEFAULT << endl;
    cout << "                              Expected            Actual " << endl;
    cout << "Date       Time     Increment Date       Time     Date       Time     Pass?" << endl;
    cout << "------------------- --------- ------------------- ------------------- --------" << endl;
    for (int i = 0; i < (sizeof(startDateTime) / sizeof(string)); ++i)
    {
        DateTime testDateTime(startDateTime[i]);
        testDateTime.increment(increment[i]);
        string x = testDateTime.toString();
        cout << startDateTime[i] << " "
             << setw(9) << increment[i] << " "
             << expectedDateTime[i] << " "
             << x << " ";
        dispPass(x == expectedDateTime[i]);
        // test decrement
        if (increment[i] != 0)
        {
            DateTime testDateTime2(expectedDateTime[i]);
            testDateTime2.increment(-increment[i]);
            string y = testDateTime2.toString();
            cout << expectedDateTime[i] << " "
                 << setw(9) << -increment[i] << " "
                 << startDateTime[i] << " "
                 << y << " ";
            dispPass(y == startDateTime[i]);
        }
    }
}

void testDateTimeDayIncrement()
//-----------------------------------------------------------------------------
{
    // Test simple increment, increment nothing, advance past end of month, end of year, and many years
    string startDateTime[]    = {"2001/01/01 00:00:00",
                                 "2001/01/01 00:00:00",
                                 "2001/01/01 00:00:00"
                                };
    int increment[]           = {365, 31, 1};
    string expectedDateTime[] = {"2002/01/01 00:00:00",
                                 "2001/02/01 00:00:00",
                                 "2001/01/02 00:00:00"
                                };

    cout << YELLOW << "void DateTime::increment(int)" << DEFAULT << endl;
    cout << "                              Expected            Actual " << endl;
    cout << "Date       Time     Increment Date       Time     Date       Time     Pass?" << endl;
    cout << "------------------- --------- ------------------- ------------------- --------" << endl;
    for (int i = 0; i < (sizeof(startDateTime) / sizeof(string)); ++i)
    {
        DateTime testDateTime(startDateTime[i]);
        testDateTime.incrementDays(increment[i]);
        string x = testDateTime.toString();
        cout << startDateTime[i] << " "
             << setw(9) << increment[i] << " "
             << expectedDateTime[i] << " "
             << x << " ";
        dispPass(x == expectedDateTime[i]);
        // test decrement
        if (increment[i] != 0)
        {
            DateTime testDateTime2(expectedDateTime[i]);
            testDateTime2.incrementDays(-increment[i]);
            string y = testDateTime2.toString();
            cout << expectedDateTime[i] << " "
                 << setw(9) << -increment[i] << " "
                 << startDateTime[i] << " "
                 << y << " ";
            dispPass(y == startDateTime[i]);
        }
    }
}

