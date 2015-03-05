/* inverter.h
 * ENB241 Project
 *
 * Inverter class header
 * DERIVED CLASS OF Component
 * Precondition: 	Valid data passed into constructor
					All doubles passed into constructor must be within accepted bounds	
					Input must be positive, efficiency must be between 0 and 100.		
 * Postcondition: 	Valid Inverter object created
 *
 */

#ifndef _INVERTER_H_
#define _INVERTER_H_

#include "component.h"

class Inverter : public Component
{
public:
	// Constructor and Destructor.
    Inverter(const double powerInput, const double efficiency);
    virtual ~Inverter();
	virtual double getPowerOut() const;
	virtual string toString() const;

protected:
	double _efficiency;
	double _powerInput;
};


#endif


