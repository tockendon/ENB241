/* powersystem.h
 * ENB241 Portfolio 2
 *
 * PowerSystem class header
 * Precondition:    Valid data passed into advanced constructor
                    Number of banks for advanced constructor is greater than 0        
 * Postcondition:   Valid PowerSystem object created
 *
 */

#ifndef _POWERSYSTEM_H_
#define _POWERSYSTEM_H_

#include "component.h"
#include "location.h"
#include "bank.h"
#include "wire.h"
#include "costbenefit.h"
#include "inverter.h"

#include <iomanip>
#include <stdexcept>
#include <new>
#include <vector>
    using std::vector;
#include <string>
    using std::string;
#include <sstream>              // Allows strings to be used like cin/cout.
    using std::istringstream;   // Read from string.
	using std::ostringstream;

#include <iostream>
    using std::cin;
    using std::cout;    // Allows for output display.
    using std::endl;    // Allows for end of line.

using namespace std;

class PowerSystem
{
public:
	// Constructor and Destructor.
    PowerSystem();
    PowerSystem(unsigned int mode);
    PowerSystem(unsigned int mode, unsigned int NUM_BANKS);
    virtual ~PowerSystem();
    void Output();

protected:
    // For simple functionality
    double _orientLoss;
    double _tiltLoss;

    // Common variables for both simple and advanced
    Component *inverter;
    Component* bank;
    Component* wire;
    vector<double> _ratedPower;
    vector<double> _wireLoss;
    vector<Component*> vectorBank;
    vector<Component*> vectorWire;
    double _inverterEfficiency;
    double _paneltimeEfficiency;
    double _sunlightHours;

    // For Advanced functionality
    int _NUM_BANKS;
    CostBenefit* analysis;
    Location *local;
    string _gpsCord;
    vector<double> _orientAngle;
    vector<double> _tiltAngle;
	char _NS;
    double _optimAngle;
    double _genUsage;
    double _peakUsage;
    double _offPeakUsage;
    double _installCost;
};


#endif




