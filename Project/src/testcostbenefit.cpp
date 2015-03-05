/* testcostbenefit.cpp
 * ENB241 Propject
 *
 * CostBenefit class testdriver
 *
 */

#include <iostream>
    using std::cout;	// Allows for output display.
    using std::endl;	// Allows for end of line.
	using std::cerr;	// Allows for error output.

#include <iomanip>
    using std::setw;	// Allows set spacing on the display output.

#include <math.h>

#include <costbenefit.h>
#include <location.h>
#include <stdexcept>



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
void testConstructor();
void testCalcInvestReturn();
void testTallyReturn();
void testRecoup();
void testCalcProfitLoss();

int main(int argc, char *argv[])
{
    cout << MAGENTA << "\t\t\t   TestDriver-CostBenefit\n";
	cout << BLUE << "\t  *****************Testing Constructor*****************\n";

    cout << "Constructor is tested implicitly whilst testing the member functions" << endl;
	cout << BLUE << "\t  *****************Testing Constructor exception handling*****************\n";

	testConstructor();
	cout << endl;

	cout << BLUE << "\t  *****************Testing Member Functions*****************\n";

	testCalcInvestReturn();
	cout << endl;


	testTallyReturn();
	cout << endl;

	testRecoup();
	cout << endl;

	testCalcProfitLoss();
	cout << endl;

	cout << MAGENTA << "\t\t\t           END\n" << DEFAULT;

    return 0;
}

// Tests constructor exception handling -
// This tests that an exception is thrown if a negative value is used for any of the electricity usage and cost parameters. These values should be positive.
void testConstructor()
{
	//Attempting to construct with negative value for _genUsage parameter of the constructor.
	cout << YELLOW << "Attempting to construct with one or more negative value" << DEFAULT << endl;
	string actual = "Exception not thrown";
	Location *local[1] = {NULL};
    local[0] = new Location("27.4679 S 153.0278 E"); //Brisbane
	string expected = "Exception thrown";
	try
	{
		CostBenefit testCostBenefit(*local[0], -15, 25, 10, 4000);// negative generate usage
	}
	catch (exception &e)
	{
		actual = "Exception thrown";
		cerr << e.what() << endl;
	}
	cout << CYAN << "Incorrect input                 Expected           Actual     Pass?" << endl;
    cout << "--------------------      --------------      -------------    ----" << DEFAULT << endl;
	cout << setw(10) << "_genUsage negative    "
		<< setw(20) << expected << "    "
		<< setw(15) << actual << "   ";
	dispPass(expected == actual);
	cout << endl;


	// correct construction parameters - all positive values
	actual = "Exception not thrown";
	cout << YELLOW << "Attempting to construct with correct parameters" << DEFAULT << endl;
	// constructing with negative _genUsage
	expected = "Exception not thrown";
	try
	{
		CostBenefit testCostBenefit(*local[0], 15, 25, 10, 4000);// negative generate usage
	}
	catch (exception &e)
	{
		actual = "Exception thrown";
		cerr << e.what() << endl;
	}
	cout << CYAN << "Incorrect input                 Expected           Actual           Pass?" << endl;
    cout << "--------------------      --------------      -------------          ----" << DEFAULT << endl;
	cout << setw(10) << "_genUsage negative    "
		<< setw(20) << expected << "    "
		<< setw(15) << actual << "   ";
	dispPass(expected == actual);
	cout << endl;




}

// Tests investment return function-
// This tests the investement return function by passing in different location objects and different panel outputs
void testCalcInvestReturn()
{
	const int citys = 9;

	Location *local[9] = {NULL};
    local[0] = new Location("27.4679 S 153.0278 E"); //Brisbane
    local[1] = new Location("33.8600 S 151.2111 E"); // Sydney
    local[2] = new Location("35.3075 S 149.1244 E"); //Canberra
    local[3] = new Location("37.8136 S 144.9631 E"); //Melbourne
    local[4] = new Location("42.8806 S 147.3250 E"); //Hobart
    local[5] = new Location("34.9290 S 138.6010 E"); //Adelaide
    local[6] = new Location("31.9522 S 115.8589 E"); //Perth
    local[7] = new Location("12.4500 S 130.8333 E"); //Darwin
	local[8] = new Location("39.2940 N 116.3495 E"); //Beijing


    const double output[] = {0, 5, 10, 15, 20, 25, 30, 35};
    const double expectedInvestReturn[] = {0, 696.40175, 734.7450, 1803.73875, 438.0000, 2673.1505, 2529.9400, 894.2500} ;

    cout << YELLOW << "double CostBenefit::calcInvestReturn(const double output)" << DEFAULT << endl;
	cout << CYAN << "       City              Panel Output      Expected     Actual     Pass?" << endl;
    cout << "--------------------      --------         --------    --------    ----" << DEFAULT << endl;
	double x;
	for (int i = 0; i < (sizeof(output) / sizeof(double)); ++i)
    {
        double hours = local[i]->sunlightHours();
		CostBenefit testCostBenefit(*local[i], 15, 25, 10, 4000);// typical system parameters
        x = testCostBenefit.calcInvestReturn(output[i]);

		// Display the output.
        cout << setw(10) << local[i]->getCity() << "    "
			 << setw(20) << output[i] << "  "
             << setw(15) << expectedInvestReturn[i] << "     "
             << setw(7) << x << "    ";
        dispPass(round(x*100)/100 == round(expectedInvestReturn[i]*100)/100); //rounds to 2 decimal places
	}

	//CostBenefit test(&locations[0],25,25,15,3000);

    for (int j = 0; j < citys; j++)
    {
		delete local[j];
    }
}

// Tests investment return tally function
// This function tests the tally function by creating an CostBenefit object then calling the tally return
// function and passing in a hypothetical total investment return value and comparing this to the hand calculated result
void testTallyReturn()
{
	Location *local[1] = {NULL};
    local[0] = new Location("27.4679 S 153.0278 E"); //Brisbane
	const double totalInvestReturn = 899;
	const double expectedTallyReturn = 2910.06;

	cout << YELLOW << "double CostBenefit::tallyReturn()" << DEFAULT << endl;
	cout << CYAN << "Return for year       Total Return      Expected     Actual     Pass?" << endl;
    cout << "--------------------      --------         --------    --------    ----" << DEFAULT << endl;

        CostBenefit testCostBenefit(*local[0], 15, 25, 10, 4000);// typical system parameters
		double investReturn = testCostBenefit.calcInvestReturn(20); //calcs investment return for yeah with output of 20 kwh
        double x = testCostBenefit.tallyReturn(totalInvestReturn);

		// Display the output.
        cout << setw(10) << testCostBenefit.calcInvestReturn(20) << "    "
			 << setw(20) << totalInvestReturn << "  "
             << setw(15) << expectedTallyReturn << "     "
             << setw(7) << x << "    ";
        dispPass(round(x*100)/100 == round(expectedTallyReturn*100)/100);//rounds to 2 decimal places

	delete local[0];
}

// Tests the recoup function
// Tests function by creating a cost benefit object with an initial cost of $3000, The recoup function is then called with different total
// investment returns and different year values. The results are compared to hand calculated results to determine a pass or a fail
void testRecoup()
{
	Location *local[1] = {NULL};
    local[0] = new Location("27.4679 S 153.0278 E"); //Brisbane
	CostBenefit testCostBenefit(*local[0], 15, 25, 10, 3000);// typical system parameters - install cost of $3000
	int x;

	double totalInvestReturn[] = {500, 1000, 1600, 2400, 3000, 3400, 4000, 4500};
	int year[] = {1, 2, 3, 4, 5, 6, 7, 8};
	int expectedRecoup[] = {0, 0, 0, 0, 5, 6, 7, 8};

	cout << YELLOW << "double CostBenefit::Recoup()" << DEFAULT << endl;
	cout << CYAN << "Install Cost         Investment Return     Expected    Actual    Pass?" << endl;
    cout << "--------------------      --------         --------    --------    ----" << DEFAULT << endl;

	for (int i = 0; i < (sizeof(totalInvestReturn) / sizeof(double)); ++i)
    {

		x = testCostBenefit.recoup(totalInvestReturn[i], year[i]);

		// Display the output.
        cout << setw(10) << "$3000" << "    "
			 << setw(20) << totalInvestReturn[i] << "  "
             << setw(15) << expectedRecoup[i] << "     "
             << setw(7) << x << "    ";
        dispPass(x == expectedRecoup[i]);
	}

	delete local[0];

}

// Tests profit loss function
// Tests function by creating an typical CostBenefit object with a system cost of $3000 and then calling the profit loss function and
// passing in different values of total investment return. The results are then compared with hand calculated results to determine a pass or fail.
void testCalcProfitLoss()
{
	Location *local[1] = {NULL};
    local[0] = new Location("27.4679 S 153.0278 E"); //Brisbane
	CostBenefit testCostBenefit(*local[0], 15, 25, 10, 3000);// typical system parameters - install cost of $3000
	double x;

	double totalInvestReturn[] = {500, 1000, 1600, 2400, 3000, 3400, 4000, 4500};
	int expectedProfitLoss[] = {-2500, -2000, -1400, -600, 0, 400, 1000, 1500};

	cout << YELLOW << "double CostBenefit::calcProfitLoss()" << DEFAULT << endl;
	cout << CYAN << "Install Cost         Investment Return     Expected    Actual    Pass?" << endl;
    cout << "--------------------      --------         --------    --------    ----" << DEFAULT << endl;

	for (int i = 0; i < (sizeof(totalInvestReturn) / sizeof(double)); ++i)
    {

		x = testCostBenefit.calcProfitLoss(totalInvestReturn[i]);

		// Display the output.
        cout << setw(10) << "$3000" << "    "
			 << setw(20) << totalInvestReturn[i] << "  "
             << setw(15) << expectedProfitLoss[i] << "     "
             << setw(7) << x << "    ";
        dispPass(x == expectedProfitLoss[i]);
	}

	delete local[0];

}


