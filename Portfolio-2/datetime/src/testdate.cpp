/* datetest.cpp
 * ENB241 Portfolio 2
 *
 * Date class test driver
 *
 * Original: 28/02/2013 - C. Fookes
 * Modified: 08/04/2014 - D. Chen
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

#include <date.h>


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
void testCalcDays();
void testIncrement();
void testIsLeap();


int main(int argc, char *argv[])
//-----------------------------------------------------------------------------
{
    cout << "Date Class Test Driver\n"  << endl;

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

    testIncrement();
    cout << endl;

    testCompare();
    cout << endl;

    testCalcDays();
    cout << endl;

    testIsLeap();
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
    string testDate[] = {"2014/05/02", "2014/01/01", "1999/12/31", "2000/02/29", "2014/02/28", "2014/04/30"};
    cout << YELLOW << "Date::Date(string)" << DEFAULT << endl;
    cout << "    Uses: " << YELLOW << "Date::setDate(unsigned int, unsigned int, unsigned int)" << DEFAULT << endl;
    cout << YELLOW << "Date::toString()" << DEFAULT << endl;

    cout << "String     Actual     Pass?" << endl;
    cout << "---------- ---------- ----------" << endl;
    for (int i = 0; i < (sizeof(testDate) / sizeof(string)); ++i)
    {
        Date dateObj(testDate[i]);
        string x = dateObj.toString();
        cout << testDate[i] << " "
             << x << " ";
        if (dispPass(x == testDate[i])) continue;

        return false;
    }

    return true;
}


void testConstructors()
//-----------------------------------------------------------------------------
{
    // Tests default constructor
    cout << YELLOW << "Date::Date()" << DEFAULT << endl;
    Date currentDate;
    cout << "Date should be current date: " << currentDate.toString() << endl;
    cout << endl;

    // Tests constructor setting dates
    cout << YELLOW << "Date::Date(unsigned int, unsigned int, unsigned int)" << DEFAULT << endl;
    cout << "    Uses: " << YELLOW << "Date::setDate(unsigned int, unsigned int, unsigned int)" << DEFAULT << endl;
    Date setDate(2, 5, 2014);
    cout << "Setting date with Date(2, 5, 2014): " << setDate.toString() << " ";
    dispPass(setDate.toString() == "2014/05/02");
    cout << endl;

    // Construct invalid dates
    cout << "Constructing invalid dates:" << endl;
    string testDate[]    = {"2014/02/29", "2014/04/31", "2014/03/32", "2000/02/30", "2014/01/00", "2014/00/01", "2014/13/01", "0/01/01"};
    string expected[]    = {"2014/02/01", "2014/04/01", "2014/03/01", "2000/02/01", "2014/01/01", "2014/01/01", "2014/01/01", "1/01/01"};
    string invalidType[] = {       "Day",        "Day",        "Day",        "Day",        "Day",      "Month",      "Month",    "Year"};
    for (int i = 0; i < (sizeof(testDate) / sizeof(string)); ++i)
    {
        cout << "  Invalid " << invalidType[i] << " " << testDate[i] << endl;
        cerr << "  ";
        Date invalidDate(testDate[i]);
        cout << "  " << invalidDate.toString() << " ";
        dispPass(invalidDate.toString() == expected[i]);
    }
}


void testCompare()
//-----------------------------------------------------------------------------
{
    // Test different days, months, years, and equal dates
    string startDate[]    = {"2014/01/01", "2014/01/01", "2014/01/01", "2014/05/02", "2000/01/01"};
    string otherDate[]    = {"2014/01/03", "2014/02/01", "2020/01/01", "2014/05/02", "2000/01/01"};
    int expectedSign[]    = {          -1,           -1,           -1,            0,            0};

    cout << YELLOW << "int Date::compare(Date&)" << DEFAULT << endl;
    cout << "Date       Other      Expected   Actual     Pass?" << endl;
    cout << "---------- ---------- ---------- ---------- ----------" << endl;
    for (int i = 0; i < (sizeof(startDate) / sizeof(string)); ++i)
    {
        Date testDate(startDate[i]);
        Date testDate2(otherDate[i]);
        int x = testDate.compare(testDate2);
        cout << startDate[i] << " "                         // date
             << otherDate[i] << " "                         // other date
             << setw(10) << expectedSign[i] << " "          // expected sign
             << setw(10) << x << " ";                       // actual result
        dispPass(((x > 0) - (x < 0)) == expectedSign[i]);   // ((x > 0) - (x < 0)) gets the sign of x (-1/0/1)

        // test inverted cases
        if (expectedSign[i] != 0)
        {
            int y = testDate2.compare(testDate);
            cout << otherDate[i] << " "
                 << startDate[i] << " "
                 << setw(10) << -expectedSign[i] << " "
                 << setw(10) << y << " ";
            dispPass(((y > 0) - (y < 0)) == -expectedSign[i]);
        }
    }
}


void testCalcDays()
//-----------------------------------------------------------------------------
{
    // Test same date, different years (with and without leap years)
    string startDate[]    = {"2014/05/02", "2014/05/02", "2014/05/02"};
    string otherDate[]    = {"2014/05/02", "2012/12/31", "1234/01/01"};
    int expectedDiff[]    = {           0,          487,       285010};

    cout << YELLOW << "int Date::calcDays(Date&)" << DEFAULT << endl;
    cout << "Date       Other      Expected   Actual     Pass?" << endl;
    cout << "---------- ---------- ---------- ---------- ----------" << endl;
    for (int i = 0; i < (sizeof(startDate) / sizeof(string)); ++i)
    {
        Date testDate(startDate[i]);
        Date testDate2(otherDate[i]);
        int x = testDate.calcDays(testDate2);
        cout << startDate[i] << " "
             << otherDate[i] << " "
             << setw(10) << expectedDiff[i] << " "
             << setw(10) << x << " ";
        dispPass(x == expectedDiff[i]);

        // test inverted cases
        if (expectedDiff[i] != 0)
        {
            int y = testDate2.calcDays(testDate);
            cout << otherDate[i] << " "
                 << startDate[i] << " "
                 << setw(10) << -expectedDiff[i] << " "
                 << setw(10) << y << " ";
            dispPass(y == -expectedDiff[i]);
        }
    }
}


void testIncrement()
//-----------------------------------------------------------------------------
{
    // Test simple increment, increment nothing, advance past end of month, end of year, and many years
    string startDate[]    = {"2014/05/02", "2014/05/02", "2014/05/02", "2014/05/02", "2014/05/02"};
    int increment[]       = {           1,            0,           30,          300,       100000};
    string expectedDate[] = {"2014/05/03", "2014/05/02", "2014/06/01", "2015/02/26", "2288/02/15"};

    cout << YELLOW << "void Date::increment(int)" << DEFAULT << endl;
    cout << "Date       Increment  Expected   Actual     Pass?" << endl;
    cout << "---------- ---------- ---------- ---------- ----------" << endl;
    for (int i = 0; i < (sizeof(startDate) / sizeof(string)); ++i)
    {
        Date testDate(startDate[i]);
        testDate.increment(increment[i]);
        string x = testDate.toString();
        cout << startDate[i] << " "
             << setw(10) << increment[i] << " "
             << expectedDate[i] << " "
             << x << " ";
        dispPass(x == expectedDate[i]);

        // test decrement
        if (increment[i] != 0)
        {
            Date testDate2(expectedDate[i]);
            testDate2.increment(-increment[i]);
            string y = testDate2.toString();
            cout << expectedDate[i] << " "
                 << setw(10) << -increment[i] << " "
                 << startDate[i] << " "
                 << y << " ";
             dispPass(y == startDate[i]);
        }
    }
}


void testIsLeap()
//-----------------------------------------------------------------------------
{
    // Test year divisible only by 4; by 4, 100 and 400; and only by 4 and 100
    unsigned int testYear[] = { 2004,  2000,  2100,  2014};
    bool expectedResult[]   = { true,  true, false, false};

    cout << YELLOW << "bool Date::isLeap(unsigned int)" << DEFAULT << endl;
    cout << "Year       Expected   Actual     Pass?" << endl;
    cout << "---------- ---------- ---------- ----------" << endl;
    for (int i = 0; i < (sizeof(testYear) / sizeof(unsigned int)); ++i)
    {
        bool x = Date::isLeap(testYear[i]);
        cout << setw(10) << testYear[i] << " "
             << setw(10) << expectedResult[i] << " "
             << setw(10) << x << " ";
        dispPass(x == expectedResult[i]);
    }
    cout << endl;

    string startDate[] = {"2014/05/02", "2004/12/31"};
    bool expected[]    = {       false,         true};
    cout << YELLOW << "bool Date::isLeap()" << DEFAULT << endl;
    cout << "    Uses: " << YELLOW << "bool Date::isLeap(unsigned int)" << DEFAULT << endl;
    cout << "Date       Expected   Actual     Pass?" << endl;
    cout << "---------- ---------- ---------- ----------" << endl;
    for (int i = 0; i < (sizeof(startDate) / sizeof(string)); ++i)
    {
        Date testDate(startDate[i]);
        bool x = testDate.isLeap();
        cout << startDate[i] << " "
             << setw(10) << expected[i] << " "
             << setw(10) << x << " ";
        dispPass(x == expected[i]);
    }

}
