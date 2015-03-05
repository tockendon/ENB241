/* testlocation.cpp
 * ENB241 Propject
 *
 * Location class testdriver
 */

#include <iostream>
    using std::cout;	// Allows for output display.
    using std::endl;	// Allows for end of line.
#include <iomanip>
    using std::setw;	// Allows set spacing on the display output.
    using std::setprecision;
#include <cmath>

#include <location.h>

// ANSI colour codes
//   These strings are interpreted by the terminal as a change colour command
const char* DEFAULT = "\033[0m";
const char* GREEN   = "\033[32m";
const char* RED     = "\033[31m";
const char* YELLOW  = "\033[33m";
const char* BLUE    = "\033[34m";
const char* MAGENTA = "\033[35m";
const char* CYAN    = "\033[36m";

// Displays PASS or FAIL given true or false
bool dispPass(bool pass)
{
    if (pass) cout << GREEN << "PASS" << DEFAULT << endl;
    else      cout << RED   << "FAIL" << DEFAULT << endl;
    return pass;
}

// Test function prototypes
bool testStringConstructor();
void testOptimalAngle();
void testsunlightHours();

int main(int argc, char *argv[])
{
    cout << MAGENTA << "\t\t\t   TestDriver-Location\n";
	cout << BLUE << "\t  *****************Testing Constructors*****************\n";

    if (!testStringConstructor())
    {
        cout << "Prerequisite functions failed.\nAborting tests." << endl;
        return 1;
    }
    cout << endl;

	cout << BLUE << "\t  *****************Testing Member Functions*****************\n";

	testOptimalAngle();
	cout << endl;

    testsunlightHours();
    cout << endl;

	cout << MAGENTA << "\t\t\t           END\n" << DEFAULT;

    return 0;
}

// Constructs location from string and extracts string, comparing the result.
// Passing will not guarentee the functions are without errors, it will only
// demonstrate that the contructors are correctly working.
bool testStringConstructor()
//-----------------------------------------------------------------------------
{
    string testInput[] = {"27.4679 S 153.0278 E", "33.8600 S 151.2111 E", "35.3075 S 149.1244 E", "37.8136 S 144.9631 E",
                          "42.8806 S 147.3250 E", "34.9290 S 138.6010 E", "31.9522 S 115.8589 E", "12.4500 S 130.8333 E"};

    cout << YELLOW << "Location::Location(string)" << DEFAULT << endl;
    cout << "    Uses: " << YELLOW << "Location::toString()" << DEFAULT << endl;
    cout << CYAN << "       String                 Actual          Pass?" << endl;
    cout << "--------------------   --------------------   ----" << DEFAULT  << endl;
    for (int i = 0; i < (sizeof(testInput) / sizeof(string)); ++i)
    {
		Location LocationObj(testInput[i]);	// Create Time object with string.

		string x = LocationObj.toString(); // Convert back to string.

		// Display output
		cout << setw(20) << testInput[i] << "   " << setw(20) << setprecision(7) << x << "   ";

        if (dispPass(x == testInput[i])) continue;	//Compare the result.

        return false;
    }

    return true;
}

// Testing the location classes optimalAngle() function by comparing
// the output with a precalculated correct value.
// The following assumptions are made before tests are conducted:
// - Entered lattitudes are no greater than 2 degrees in difference to predesigned city's.
// - Entered longitudes are no greater than 2 degrees in difference to predesigned city's.
void testOptimalAngle()
{
    string testInput[] = {"27.4679 S 153.0278 E", "33.8600 S 151.2111 E", "35.3075 S 149.1244 E", "37.8136 S 144.9631 E",
                          "42.8806 S 147.3250 E", "34.9290 S 138.6010 E", "31.9522 S 115.8589 E", "12.4500 S 130.8333 E"};
    double expectedDiff[] = {26.9971, 32.5582, 33.8175, 35.9978, 40.4061, 33.4882, 30.8984, 10.8315};

    cout << YELLOW << "double Location::optimalAngle()" << DEFAULT << endl;
	cout << CYAN << "       Inputs          Expected     Actual     Pass?" << endl;
    cout << "--------------------   --------    --------    ----" << DEFAULT << endl;

    // Test each location
	for (int i = 0; i < (sizeof(testInput) / sizeof(string)); ++i)
    {
        Location setLocation(testInput[i]);     // Create location object.
        double x = setLocation.optimalAngle();  // Get the optimal angle using that location.

        // Round the double value to 4 decimal places.
        double intpart;
        double fractpart = modf (x, &intpart);
        fractpart  = roundf(fractpart * 10000.0)/10000.0;
        x = intpart + fractpart;

		// Display the output.
        cout << setw(20) << testInput[i] << "    "
             << setw(7) << expectedDiff[i] << "     "
             << setw(7) << x << "    ";

        //Compare the result.
        dispPass(x == expectedDiff[i]);
	}
}

// Testing the location classes sunlightHours() function by comparing
// the output with a precalculated correct value. The GPS corrdinates have been slightly
// altered from the predesigned cities by a difference of less than 2 degrees. This is to
// test that the constructor will automatically pin point to the nearest town for sunlight hours.
// The following assumptions are made before tests are conducted:
// - Entered lattitudes are no greater than 2 degrees in difference to predesigned cities.
// - Entered longitudes are no greater than 2 degrees in difference to predesigned cities.
void testsunlightHours()
{
    string testInput[] = {"26.1679 S 154.0278 E", "34.8600 S 152.2111 E", "34.3075 S 149.1244 E", "36.8136 S 144.0631 E",
                          "43.8806 S 146.3250 E", "35.9290 S 138.0010 E", "31.5522 S 115.1589 E", "12.4599 S 131.8333 E"};
    double expectedDiff[] = {5.2, 6.4, 7.3, 6.7, 6.6, 7.4, 5.6, 8.3};

    cout << YELLOW << "double Location::sunlightHours()" << DEFAULT << endl;
	cout << CYAN << "       Inputs          Expected     Actual     Pass?" << endl;
    cout << "--------------------   --------    --------    ----" << DEFAULT << endl;

    // Test each location
	for (int i = 0; i < (sizeof(testInput) / sizeof(string)); ++i)
    {
        Location setLocation(testInput[i]);         // Create location object.
        double x = setLocation.sunlightHours();     // Get the sunlight hours for that location.

		// Display the output.
        cout << setw(20) << testInput[i] << "    "
             << setw(7) << expectedDiff[i] << "     "
             << setw(7) << x << "    ";

        //Compare the result.
        dispPass(x == expectedDiff[i]);
	}
}

