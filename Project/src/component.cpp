/* component.cpp
 * ENB241 Project
 *
 * Component class header
 *
 *
 */

#include "component.h"

Component::Component()
{
}

Component::~Component()
{
}

// Operator overloading for output power
double Component::operator+ (double power)
{
	return(getPowerOut() + power);
}

double Component::operator* (double sunlightHours)
{
	return(getPowerOut() * sunlightHours);
}

