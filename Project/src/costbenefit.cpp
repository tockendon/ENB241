/* Costbenefit.cpp
 * ENB241 Project
 *
 * CostBenefit class header
 *
 *
 */

#include "costbenefit.h"

#include <iostream>
    using std::cout;	// Allows for output display.
    using std::endl;	// Allows for end of line.

// The following data has been obtained from:
//											 http://www.originenergy.com.au/962/Energy-price-fact-sheets
//											http://shrinkthatfootprint.com/average-electricity-prices-kwh
//											http://about.bnef.com/press-releases/chinas-12gw-solar-market-outstripped-all-expectations-in-2013/
// For simplicity peak and shoulder rate categories have been combined into one category (peak)
const int citys = 9;

// in c/kWh	
const double peakTariff[citys] =
    /*Brisbane (city 0)*/ {34.065,
    /*Sydney   (city 1)*/  38.159,
    /*Canberra (city 2)*/  20.130,
    /*Melbourne(city 3)*/  32.945,
    /*Hobart   (city 4)*/  29.745, // fixed rate for 24 hours of the day
    /*Adelaide (city 5)*/  43.758,
    /*Perth    (city 6)*/  40.309,
    /*Darwin   (city 7)*/  29.990,
	/*Beijing   (city 8)*/ 11.410};

// in c/kWh	
const double offPeakTariff[citys] =
    /*Brisbane (city 0)*/ {21.373,
    /*Sydney   (city 1)*/  18.997,
    /*Canberra (city 2)*/  10.230,
    /*Melbourne(city 3)*/  16.731,
    /*Hobart   (city 4)*/  29.745, // fixed rate for 24 hours of the day
    /*Adelaide (city 5)*/  16.357,
    /*Perth    (city 6)*/  22.190,
    /*Darwin   (city 7)*/  15.373,
	/*Beijing   (city 8)*/ 9.210};

// in c/kWh	
const double feedInTariff[citys] =
    /*Brisbane (city 0)*/ {8,
    /*Sydney   (city 1)*/  6,
    /*Canberra (city 2)*/  6,
    /*Melbourne(city 3)*/  8,
    /*Hobart   (city 4)*/  6, // pays fixed rate for all electricity generated
    /*Adelaide (city 5)*/  7.6,
    /*Perth    (city 6)*/  5.9,
    /*Darwin   (city 7)*/  7, // pays fixed rate for all electricity generated
	/*Beijing   (city 8)*/ 16};
	
const bool fixedGenRate[citys] = 
    /*Brisbane (city 0)*/ {0,
    /*Sydney   (city 1)*/  0,
    /*Canberra (city 2)*/  0,
    /*Melbourne(city 3)*/  0,
    /*Hobart   (city 4)*/  1, // pays fixed rate for all electricity generated
    /*Adelaide (city 5)*/  0,
    /*Perth    (city 6)*/  0,
    /*Darwin   (city 7)*/  1, // pays fixed rate for all electricity generated	
	/*Beijing   (city 8)*/ 0};	

	
CostBenefit::CostBenefit(const Location& location, const double genUsage, const double peakUsage, const double offPeakUsage, const double installCost)
	: _location(location), _genUsage(genUsage), _peakUsage(peakUsage), _offPeakUsage(offPeakUsage), _installCost(installCost)
{
	if(_genUsage<0 || _peakUsage<0 || _offPeakUsage<0 || _installCost<0)
	{
		throw domain_error("Error: One of more of the parameters were entered as negative values. Parameters must be positive");
	}
	
	//sets tariff rate values according to location
	_peakTariff = peakTariff[_location.getCity()];
	_offPeakTariff = offPeakTariff[_location.getCity()];
	_feedInTariff = feedInTariff[_location.getCity()];
	
}

CostBenefit::~CostBenefit()
{

}

double CostBenefit::calcInvestReturn(const double output)
{
	// declare variables
	double savings, income;
	
	if(fixedGenRate[_location.getCity()]) // if Hobart or Darwin - fixed rate for all electricity generated
	{
		savings = 0;
		income = output*_feedInTariff*365/100;
	}
	
	else // for all other cities - rate paid for excess electricity fed into the grid
	{
		if(output > _genUsage) // grid feed in case
		{
			savings = _genUsage*_peakTariff*365/100; // savings is what would have been paid if there was no solar 
			income = (output-_genUsage)*_feedInTariff*365/100;

		}
		else
		{
			savings = output*_peakTariff*365/100; // savings is what would have been paid if there was no solar 
			income = 0; // no excess fed in therefore no income
		}
	}
	_investReturn = savings + income;

	return _investReturn;

}

// Returns the tally of the total return on the investment
double CostBenefit::tallyReturn(double totalInvestReturn)
{
	return totalInvestReturn + _investReturn;
}

//Returns the number of years to recoup the initial system cost. If system cost has not been recouped a zero is returned
int CostBenefit::recoup(double totalInvestReturn, int year)
{
	if(totalInvestReturn>=_installCost)
	{
		return year;
	}
	
	return 0;

}

// calculated the profit or loss over the life of the system 
double CostBenefit::calcProfitLoss(const double totalInvestReturn) const
{
	return totalInvestReturn - _installCost;
}


