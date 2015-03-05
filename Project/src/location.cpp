/* location.cpp
 * ENB241 Project
 *
 * Location class header
 *
 *
 */
 #include <iostream>
 #include <cmath>
 #include <stdexcept>
using namespace std;
#include <string>
    using std::string;
#include <sstream>
    using std::istringstream;
    using std::ostringstream;
#include <iomanip>
    using std::setw;			// Allows set spacing on the display output.
    using std::setfill;			// Allows to zero pad the two digit numbers.

#include "location.h"

// Data obtained from:
//						http://www.bom.gov.au/climate/data/
//						http://frankhaugwitz.info/doks/pv/2008_12_China_Solar_Clean_Energy_Trade_Gov_USA.pdf	

	const int citys = 9;

    const double sunlightMean[citys] =
    /*Brisbane*/ {5.2,
    /*Sydney*/   6.4,
    /*Canberra*/ 7.3,
    /*Melbourne*/6.7,
    /*Hobart*/   6.6,
    /*Adelaide*/ 7.4,
    /*Perth*/    5.6,
    /*Darwin*/   8.3,
	/*Beijing*/	 4.2};
    
	const double gpsDeg[citys][2] =
    {            /*North/South    East/West   */
    /*Brisbane  */ {27.4679, 153.0278},
    /*Sydney    */ {33.8600, 151.2111},
    /*Canberra  */ {35.3075, 149.1244},
    /*Melbourne */ {37.8136, 144.9631},
    /*Hobart    */ {42.8806, 147.3250},
    /*Adelaide  */ {34.9290, 138.6010},
    /*Perth     */ {31.9522, 115.8589},
    /*Darwin    */ {12.4500, 130.8333},
	/*Beijing   */ {39.2940, 116.3495}
	};
	
	
Location::Location(const string &location)
{
    istringstream ss(location);
    ss >> _latitude >> _NS >> _longitude >> _EW;
	_NS = toupper(_NS);
    _EW = toupper(_EW);
	// Gets city index
	for(int i = 0; i < citys; i++)
    {
            if( abs(gpsDeg[i][0] -_latitude) < 2 && abs(gpsDeg[i][1] - _longitude) < 2)
            {
				_city = i;
            } 
    }
}

Location::~Location()
{

}

int Location::getCity() const
{
	return _city;
}

char Location::getNS() const 
{
	return _NS;
}

char Location::optimalOrientation() const
{
	if( _NS == 'N')
		{
			return 'S';
		}
		else
		{
			return 'N';
		}
}

double Location::optimalAngle() const
{
	// equation taken from http://solarpanelsphotovoltaic.net/find-best-solar-panel-angle-tilt-angle/
    double angle;
	if(_latitude<25)
	{
		angle = _latitude*0.87;
	}
	else if(_latitude <50)
	{
		angle = _latitude*0.87 + 3.1;
	}
	else 
	{
		angle = 45;
	}
	
	return angle;
}

double Location::sunlightHours()
{
   return sunlightMean[_city];
}

string Location::toString() const
{
    ostringstream ss;
    ss.precision(7);
    ss << setw(7) << std::left << setfill('0') << _latitude << " "
       << _NS << " " << setw(8) << std::left << setfill('0') << _longitude
       << " " << _EW;

    return ss.str();

}
