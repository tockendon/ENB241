/* wire.cpp
 * ENB241 Project
 *
 * Banks class header
 * DERIVED CLASS OF Component
 *
 *
 */

#include "wire.h"
#include <stdexcept>
using namespace std;

Wire::Wire(const double powerInput, const double efficiencyLoss)
{
	// Set up variables
	_efficiencyLoss = efficiencyLoss;
	_powerInput = powerInput; // in kW
}

Wire::~Wire()
{

}

double Wire::getPowerOut() const
{
	double totEfficiency = (100 - _efficiencyLoss)/100;
	// Output power = input power * total efficiency
	return _powerInput*totEfficiency;
}

string Wire::toString() const
{
	ostringstream ss;
    ss << _powerInput << " " << _efficiencyLoss;

    return ss.str();    // Return string object inside the stringstream.
}
