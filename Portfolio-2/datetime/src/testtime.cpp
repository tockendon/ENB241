/* timetest.cpp
 * ENB241 Portfolio 2
 *
 * Time class test driver
 *
 *  Student #: n8560641
 *  Name: Terrance Ockendon
 *
 *     DO NOT MODIFY
 */

#include <iostream>
    using std::cout;
    using std::cerr;
    using std::endl;

#include <iomanip>
    using std::setw;

#include <string>
    using std::string;

#include <time1.h>


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
bool testPrereqs();
void testConstructors();
void testCompare();
void testCalcSeconds();
void testIncrement();


int main(int argc, char *argv[])
//-----------------------------------------------------------------------------
{
    cout << "Time Class Test Driver\n"  << endl;

    // Tests string constructor + toString
    // Program exits if failed as they are required for other tests
    if (!testPrereqs())
    {
        cout << "Prerequisite functions failed.\nAborting tests." << endl;
        return 1;
    }
    cout << endl;

    // Perform tests

    testConstructors();
    cout << endl;

    testCompare();
    cout << endl;

    testCalcSeconds();
    cout << endl;

    testIncrement();
    cout << endl;

    cout << "--END--" << endl;

    return 0;
}


// Constructs date from string and extracts string, comparing the result.
// Passing does not guarantee the two functions are without errors, only that
// they are functional. Passing all other tests in the test driver ensures the
// two functions are operating as expected.
bool testPrereqs()
//-----------------------------------------------------------------------------
{
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
    cout << endl;

    return true;
}


void testConstructors()
//-----------------------------------------------------------------------------
{
    // Tests default constructor
    cout << YELLOW << "Time::Time()" << DEFAULT << endl;
    Time currentTime;
    cout << "Time should be current time: " << currentTime.toString() << endl;
    cout << endl;

    // Tests constructor setting 24 hour time
    cout << YELLOW << "Time::Time(unsigned int, unsigned int, unsigned int)" << DEFAULT << endl;
    cout << "    Uses: " << YELLOW << "Time::setTime.toString(unsigned int, unsigned int, unsigned int)" << DEFAULT << endl;
    Time setTime(12, 02, 03);
    cout << "Setting time with Time(12:02:03): " << setTime.toString() << " ";
    dispPass(setTime.toString() == "12:02:03");
    cout << endl;

    // Construct invalid 24 hour Times
    cout << "Constructing invalid 24 hour times:" << endl;
    string testTime24[]    = {"24:00:00", "-1:00:00", "00:60:00", "00:-1:00", "00:00:60", "00:00:-1"};
    string expected24[]    = {"00:00:00", "00:00:00", "00:00:00", "00:00:00", "00:00:00", "00:00:00"};
    string invalidType24[] = {"Hour",     "Hour",     "Minute",   "Minute",   "Second",   "Second"};
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
    cout << YELLOW << "Time::Time(unsigned int, unsigned int, unsigned int)" << DEFAULT << endl;
    cout << "    Uses: " << YELLOW << "Time::setTime.toString12(unsigned int, unsigned int, unsigned int)" << DEFAULT << endl;
    //Time setTime(12, 02, 03);
    cout << "Setting time with Time(12:02:03): " << setTime.toString12() << " ";
    dispPass(setTime.toString12() == "12:02:03 PM");
    cout << endl;

    // Construct invalid 12 hour XM Times
    cout << "Constructing invalid 12 hour times:" << endl;
    string testTime12[]    = {"24:00:00", "-1:00:00", "00:60:00", "00:-1:00", "00:00:60", "00:00:-1"};
    string expected12[]    = {"12:00:00 AM", "12:00:00 AM", "12:00:00 AM", "12:00:00 AM", "12:00:00 AM", "12:00:00 AM"};
    string invalidType12[] = {"Hour",     "Hour",     "Minute",   "Minute",   "Second",   "Second"};
    for (int i = 0; i < (sizeof(testTime12) / sizeof(string)); ++i)
    {
        cout << "  Invalid " << invalidType12[i] << " " << testTime12[i] << endl;
        cerr << "  ";
        Time invalidTime12(testTime12[i]);
        cout << "  " << invalidTime12.toString12() << " ";
        dispPass(invalidTime12.toString12() == expected12[i]);
    }
    cout << endl;
}


void testCompare()
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


void testCalcSeconds()
//-----------------------------------------------------------------------------
{
    // Test same date, different years (with and without leap years)
    string startTime[]    = {"12:00:01", "15:50:01", "23:05:02"};
    string otherTime[]    = {"12:00:01", "15:40:00", "01:01:03"};
    int expectedDiff[]    = {         0,        601,      79439};

    cout << YELLOW << "int Time::calcDays(Time&)" << DEFAULT << endl;
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


void testIncrement()
//-----------------------------------------------------------------------------
{
    // Test simple increment, increment nothing, advance past end of month, end of year, and many years
    string startTime[]    = {"12:00:00", "23:59:59", "02:01:11", "12:00:00", "12:00:00"};
    int increment[]       = {         1,          1,      -7272,     864000,    -864000};
    string expectedTime[] = {"12:00:01", "00:00:00", "23:59:59", "12:00:00", "12:00:00"};
    int expectedDay[]     = {         0,          1,         -1,         10,        -10};

    cout << YELLOW << "void Time::increment(int)" << DEFAULT << endl;
    cout << "Time     Increment Exp Time Act Time Exp Days Act Days Pass?" << endl;
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
