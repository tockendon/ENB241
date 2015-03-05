/* banks.cpp
 * ENB241 Project
 *
 * Banks class header
 * DERIVED CLASS OF Component
 *
 *
 */
#include <iostream>
#include <cmath>
#include <stdexcept>
using namespace std;

#include "bank.h"

#include <iostream>
    using std::cin;
    using std::cout;    // Allows for output display.
    using std::endl;    // Allows for end of line.

using  namespace std;


Bank::Bank(const double ratedPower, const double efficiencyLoss)
{
    _ratedPower = ratedPower;
    _efficiencyLoss = efficiencyLoss;
    _orientAngle = -1;
}

Bank::Bank(const double ratedPower, const double orientAngle,
           const double tiltAngle, const double optimAngle, const char NS)
{
    _ratedPower = ratedPower;
    _orientAngle = orientAngle;
    _tiltAngle = tiltAngle;
	_optimAngle = optimAngle;
	_NS = NS;

    _efficiencyLoss = addAngleLoss()+addOrientationLoss();
	if(_efficiencyLoss > 100)
	{
		_efficiencyLoss = 100;
	}

}

Bank::~Bank()
{
}

double Bank::getPowerOut() const
{
    // Total rated output power = ratedpower*n1*n2
    return _ratedPower*((100 - _efficiencyLoss)/100);
}

double Bank::addAngleLoss() const
{
	return 100*sin(abs(_optimAngle-_tiltAngle)*PI/180); //in %
}

double Bank::addOrientationLoss() const
{

	// calculation derived from website //http://www.bydsolar.com.au/Tech_Facts.html
	double loss;
	const double maxLoss = 30; // maximum loss due to orientation is 30%

	if (_NS == 'N') // in Northern hemisphere - optimal orientation is South
	{
		if(_orientAngle <180)
		{
			loss = (180-_orientAngle)*maxLoss/180;
		}
		else
		{
			loss = (_orientAngle-180)*maxLoss/180;
		}
	}
	else if (_NS == 'S') // In Southern hemisphere - optimal orientation is North
	{
		if(_orientAngle<180)
		{
			loss = _orientAngle*maxLoss/180;
		}
		else
		{
			loss = (360-_orientAngle)*maxLoss/180;
		}
	}

	return loss;
}

string Bank::toString() const
{
	ostringstream ss;
	if(_orientAngle == -1)
	{
		ss << _ratedPower << " " << _efficiencyLoss;
	}
	else
	{
		ss << _ratedPower << " " << _orientAngle << " "  << _tiltAngle << " " << _optimAngle << " " << _NS;
	}

    return ss.str();    // Return string object inside the stringstream.
}
