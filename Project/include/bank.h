/* banks.h
 * ENB241 Project
 *
 * Banks class header
 * DERIVED CLASS OF Component
 * Precondition: 	Valid data passed into constructor
					All doubles passed into constructor must be within accepted bounds
					Basic: Input must be positive, efficiency must be between 0 and 100.
					Advanced: Input must be positive, orientation must be between 0 and 359,
							  tilt must be between 0 and 90.
 * Postcondition: 	Valid Bank object created
 *
 */

#ifndef _BANK_H_
#define _BANK_H_

#include "component.h"
#include "location.h"

const double PI = 3.14159265;

class Bank : public Component
{
public:
	// Basic Constructor.
    Bank(const double ratedPower, const double efficiencyLoss);
    // Advanced Constructor.
    Bank(const double ratedPower, const double orientAngle,
          const double tiltAngle, const double optimAngle, const char NS);
    virtual ~Bank();

	virtual double getPowerOut() const;
	double addAngleLoss() const;
	double addOrientationLoss() const;
	virtual string toString() const;

protected:
  
	char _NS;
	double _efficiencyLoss;
	double _ratedPower;
    double _orientAngle;
    double _tiltAngle;
    double _optimAngle;
};


#endif



