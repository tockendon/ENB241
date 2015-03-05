/* testcomponent.cpp
 * ENB241 Propject
 *
 * Component class testdriver
 */

#include <iostream>
    using std::cout;	// Allows for output display.
    using std::endl;	// Allows for end of line.
	using std::cerr;	// Allows for error output.

#include <iomanip>
    using std::setw;	// Allows set spacing on the display output.
    using std::setprecision;
#include <cmath>

#include <component.h>
#include <bank.h>
#include <wire.h>
#include <inverter.h>


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

// Number of components to be tested
const unsigned int NUM_COMPONENTS = 12;
const unsigned int NUM_BANKS = 3;

// Test function prototypes
bool testConstructors();
void testGetPower();
void testAdditionalBanks();

int main(int argc, char *argv[])
{
    cout << MAGENTA << "\t\t\t   TestDriver-Component\n";
	cout << BLUE << "\t  *****************Testing Constructors*****************\n";

	if (!testConstructors())
    {
        cout << "Prerequisite functions failed.\nAborting tests." << endl;
        return 1;
    }

	cout << BLUE << "\t  *****************Testing Member Functions*****************\n";

	testGetPower();

    testAdditionalBanks();
    cout << endl;

	cout << MAGENTA << "\t\t\t           END\n" << DEFAULT;

    return 0;
}

// Constructs a component object dynamically and uses toString() to compare the result.
// Passing will not guarentee the functions are without errors, it will only demonstrate
// that the contructors are correctly working.
bool testConstructors()
//-----------------------------------------------------------------------------
{
    string expectedDiff[4][3] = {{"100 20", "100 50", "5000 13"},                           // Exp output to Bank(Basic)
                                 {"100 20 30 31 S", "100 90 44 20 S", "100 180 84 90 S"},   // Exp output to Bank(Advanced)
                                 {"100 20", "100 50", "5000 13"},                           // Exp output to Wire
                                 {"100 20", "100 50", "5000 13"}};                          // Exp output to Inverter

    Component *component[NUM_COMPONENTS] = {NULL};
    // Create components
    component[0] = new Bank(100,20);
    component[1] = new Bank(100,50);
    component[2] = new Bank(5000,13);
    component[3] = new Bank(100,20,30,31,'S');
    component[4] = new Bank(100,90,44,20,'S');
    component[5] = new Bank(100,180,84,90,'S');
    component[6] = new Wire(100,20);
    component[7] = new Wire(100,50);
    component[8] = new Wire(5000,13);
    component[9] = new Inverter(100,20);
    component[10] = new Inverter(100,50);
    component[11] = new Inverter(5000,13);

    int counter = 0;

	for(int i = 0; i < 4; i++)
    {
        // Print headings depending on which set of iterations loop is on.
        if (i == 0)
        {
            cout << YELLOW << "Bank::Bank(double, double)" << DEFAULT << endl;
            cout << YELLOW << "Uses: Bank::toString()" << DEFAULT << endl;
            cout << CYAN << "Expected    Actual     Pass?" << endl;
            cout << "--------   --------    ----" << DEFAULT << endl;
        }
        else if (i == 1)
        {
            cout << YELLOW << "Bank::Bank(double, double, double, double)" << DEFAULT << endl;
            cout << YELLOW << "Uses: Bank::toString()" << DEFAULT << endl;
            cout << CYAN << "   Expected             Actual        Pass?" << endl;
            cout << "---------------    ---------------    ----" << DEFAULT << endl;
        }
        else if (i == 2)
        {
            cout << YELLOW << "Wire::Wire(double, double)" << DEFAULT << endl;
            cout << YELLOW << "Uses: Wire::toString()" << DEFAULT << endl;
            cout << CYAN << "Expected    Actual     Pass?" << endl;
            cout << "--------   --------    ----" << DEFAULT << endl;
        }
        else
        {
            cout << YELLOW << "Inverter::Inverter(double, double)" << DEFAULT << endl;
            cout << YELLOW << "Uses: Inverter::toString()" << DEFAULT << endl;
            cout << CYAN << "Expected    Actual     Pass?" << endl;
            cout << "--------   --------    ----" << DEFAULT << endl;
        }
        // Run the 3 different tests on the current component
        for(int j = 0; j<3; j++)
        {
            if(i == 1) //Special case for the advanced Banks constructor
            {
                // Display the output.
                cout << setw(15) << expectedDiff[i][j] << "    "
                     << setw(15) << component[j+counter]->toString() << "    ";
                dispPass(component[j+counter]->toString() == expectedDiff[i][j]);
            }
            else //For all normal cases
            {
                // Display the output.
                cout << setw(7) << expectedDiff[i][j] << "    "
                     << setw(7) << component[j+counter]->toString() << "     ";
                dispPass( component[j+counter]->toString() == expectedDiff[i][j]);
            }

        }
        counter += 3;   //Increment to the next type of component
        cout << endl;
	}

    // Deallocate the memory for the components.
    for (int i = 0; i < NUM_COMPONENTS; i++)
    {
        if (component[i])
        {
            delete component[i];
        }
    }

    return true;
}

// Testing the component classes getPower(), tests are comparing the
// output power using the function with the correct value.
// The following assumptions are made before tests are conducted:
// - Entered powers will greater than zero.
// - Component efficiencys or losses will between 0 - 100%.
// - Orientation will be between 0-359 degrees.
// - Tilt angle will be between 0-90 degress.
// - Optimal angle will be between 0-90 degress.
void testGetPower()
//-----------------------------------------------------------------------------
{
    double x;
    int i;
    double expectedDiff[4][3] = { {80, 50, 4350},               // Exp output to Bank(Basic)
                                  {94.9214, 44.3263, 89.5472},  // Exp output to Bank(Advanced)
                                  {80, 50, 4350},               // Exp output to Wire
                                  {20, 50, 650}};               // Exp output to Inverer

    Component *component[NUM_COMPONENTS] = {NULL};
    // Create components
    component[0] = new Bank(100,20);
    component[1] = new Bank(100,50);
    component[2] = new Bank(5000,13);
    component[3] = new Bank(100,20,30,31,'S');
    component[4] = new Bank(100,90,44,20,'S');
    component[5] = new Bank(100,180,84,90,'N');
    component[6] = new Wire(100,20);
    component[7] = new Wire(100,50);
    component[8] = new Wire(5000,13);
    component[9] = new Inverter(100,20);
    component[10] = new Inverter(100,50);
    component[11] = new Inverter(5000,13);

    int counter = 0;

	for(i = 0; i < 4; i++)
    {
        // Print headings depending on which set of iterations loop is on.
        if (i == 0)
        {
            cout << YELLOW << "double Bank::getPowerOut() (Basic)" << DEFAULT << endl;
            cout << CYAN << " Inputs   Expected  Actual  Pass?" << endl;
            cout << "--------  --------  ------  ----" << DEFAULT << endl;
        }
        else if (i == 1)
        {
            cout << YELLOW << "double Bank::getPowerOut() (Advanced)" << DEFAULT << endl;
            cout << CYAN << "    Inputs        Expected     Actual  Pass?" << endl;
            cout << "---------------   --------    -------  ----" << DEFAULT << endl;
        }
        else if (i == 2)
        {
            cout << YELLOW << "double Wire::getPowerOut()" << DEFAULT << endl;
            cout << CYAN << " Inputs   Expected  Actual  Pass?" << endl;
            cout << "--------  --------  ------  ----" << DEFAULT << endl;
        }
        else
        {
            cout << YELLOW << "double Inverter::getPowerOut()" << DEFAULT << endl;
            cout << CYAN << " Inputs   Expected  Actual  Pass?" << endl;
            cout << "--------  --------  ------  ----" << DEFAULT << endl;
        }
        // Run the 3 different tests on the current component
        for(int j = 0; j<3; j++)
        {
            x = component[j+counter]->getPowerOut();

            if(i == 1) //Special case for the advanced Banks constructor
            {
                double intpart;
                double fractpart = modf (x, &intpart);
                fractpart  = roundf(fractpart * 10000.0)/10000.0; // Round to 4 decimal places
                x = intpart + fractpart;

                // Display the output.
                cout << setw(15) << component[j+counter]->toString() << "    "
                     << setw(7) << expectedDiff[i][j] << "    "
                     << setw(7) << x << "  ";
                dispPass(x == expectedDiff[i][j]);
            }
            else //For all normal cases
            {
                // Display the output.
                cout << setw(7) << component[j+counter]->toString() << "    "
                     << setw(4) << expectedDiff[i][j] << "     "
                     << setw(4) << x << "    ";
                dispPass(x == expectedDiff[i][j]);
            }

        }
        counter += 3;   //Increment to the next type of component
        cout << endl;
	}

    //Delete allocated memory
    for (i = 0; i < NUM_COMPONENTS; i++)
    {
        if (component[i])
        {
            delete component[i];
        }
    }
}

// Testing the Bank classes addAngleLoss() and addOrientationLoss() functions.
// The output of the test will be compared with a precalculated value.
// The following assumptions are made before tests are conducted:
// - Entered power ratings will greater than zero.
// - Orientation will be between 0-359 degrees.
// - Tilt angle will be between 0-90 degress.
// - Optimal angle will be between 0-90 degress.
void testAdditionalBanks()
{
    Bank *banks[NUM_BANKS] = {NULL};
    banks[0] = new Bank(100,20,30,31,'S');
    banks[1] = new Bank(100,90,44,20,'S');
    banks[2] = new Bank(100,180,84,90,'N');

    double expectedDiff[] = {1.7452, 40.6737, 10.4528};    // Exp output for addAngleLoss()
    double expectedDiff2[] = { 3.3333,  15,       0};      // Exp output for addOrientationLoss()

    // Testing addAngleLoss()
    // -----------------------------------------------------------------------
    cout << YELLOW << "double Bank::addAngleLoss() " << DEFAULT << endl;
	cout << CYAN << "    Inputs        Expected    Actual  Pass?" << endl;
    cout << "---------------   --------   -------  ----" << DEFAULT << endl;

    // Increment for the 3 Banks created.
    for (int i = 0; i < NUM_BANKS; i++)
    {
        // Get angle loss.
        double x = banks[i]->addAngleLoss();

        // Round the double value to 4 decimal places.
        double intpart;
        double fractpart = modf (x, &intpart);
        fractpart  = roundf(fractpart * 10000.0)/10000.0;
        x = intpart + fractpart;

		// Display the output.
        cout << setw(15) << banks[i]->toString() << "    "
             << setw(7) << expectedDiff[i] << "   "
             << setw(7) << x << "  ";

       dispPass(x == expectedDiff[i]);
	}
    cout << endl;

    // Testing addOrientationLoss()
    // -----------------------------------------------------------------------
    cout << YELLOW << "double Bank::addOrientationLoss() " << DEFAULT << endl;
	cout << CYAN << "    Inputs        Expected    Actual  Pass?" << endl;
    cout << "---------------   --------   -------  ----" << DEFAULT << endl;

    for (int i = 0; i < NUM_BANKS; i++)
    {
        // Get orientation loss.
        double x = banks[i]->addOrientationLoss();

        // Round the double value to 4 decimal places.
        double intpart;
        double fractpart = modf (x, &intpart);
        fractpart  = roundf(fractpart * 10000.0)/10000.0;
        x = intpart + fractpart;

        //Display the output.
        cout << setw(15) << banks[i]->toString() << "     "
             << setw(6) << expectedDiff2[i] << "    "
             << setw(6) << x << "  ";

       dispPass(x == expectedDiff2[i]);
	}

    //Delete allocated memory
    for (int i = 0; i < NUM_BANKS; i++)
    {
        if (banks[i])
        {
            delete banks[i];
        }
    }
}

