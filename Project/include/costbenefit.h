/* costbenefit.h
 * ENB241 Portfolio 2
 *
 * CostBenefit class header * Component class header
 * Precondition: 	Valid data passed into constructor
					Location object which returns valid city index
					All doubles passed into constructor must be of positive value				
 * Postcondition: 	Valid CostBenefit object created
 *
 */

#ifndef _COSTBENEFIT_H_
#define _COSTBENEFIT_H_

#include "location.h"
#include <stdexcept>
using namespace std;

class CostBenefit
{
public: 
	// Constructor and Destructor.
    CostBenefit(const Location& location, const double genUsage, const double peakUsage, const double offPeakUsage, const double installCost);
    virtual ~CostBenefit();
	double calcInvestReturn(const double output); 
	double tallyReturn(double totalInvestReturn);
	int recoup(double totalInvestReturn, int year);
	double calcProfitLoss(const double totalInvestReturn) const;

private:
	// 
	Location _location;
	double _genUsage, _peakUsage, _offPeakUsage, _installCost;
	double _peakTariff, _offPeakTariff, _feedInTariff;
	double _investReturn;
};


#endif




