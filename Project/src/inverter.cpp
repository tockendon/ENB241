/* inverter.cpp
 * ENB241 Project
 *
 * Inverter class file
 * DERIVED CLASS OF Component
 *
 *
 */

#include "inverter.h"
#include <stdexcept>
using namespace std;

Inverter::Inverter(const double powerInput,const double efficiency)
{
	// Set up variables
    _efficiency = efficiency;
    _powerInput = powerInput;
}

Inverter::~Inverter()
{

}

double Inverter::getPowerOut() const
{
	// Output power = input power * efficiency
    return _powerInput*(_efficiency/100);
}

string Inverter::toString() const
{
	ostringstream ss;
    ss << _powerInput << " " << _efficiency;

    return ss.str();    // Return string object inside the stringstream.
}
