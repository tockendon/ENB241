/* wire.h
 * ENB241 Project
 *
 * Wire class header
 * DERIVED CLASS OF Component
 * Precondition: 	Valid data passed into constructor
					All doubles passed into constructor must be within accepted bounds	
					Input must be positive, efficiency must be between 0 and 100.		
 * Postcondition: 	Valid Wire object created
 *
 */

#ifndef _WIRE_H_
#define _WIRE_H_

#include "component.h"

class Wire : public Component
{
public:
	// Constructor and Destructor.
    Wire(const double powerInput, const double efficiencyLoss);
    virtual ~Wire();
	virtual double getPowerOut() const;
	virtual string toString() const;

protected:
	double _efficiencyLoss;
	double _powerInput;

};


#endif



