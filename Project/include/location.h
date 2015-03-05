/* location.h
 * ENB241 Portfolio 2
 *
 * Location class header
 * Precondition:    Valid string passed into constructor     
 * Postcondition:   Valid Location object created
 *
 */

#ifndef _LOCATION_H_
#define _LOCATION_H_

#include <string>
    using std::string;

class Location
{
public:
	// Constructor and Destructor.
    Location(const string &location);
    virtual ~Location();
    string toString() const;
    double sunlightHours();
    double optimalAngle() const;
	int getCity() const;
	char getNS() const;
	char optimalOrientation() const;

protected:
    double _latitude;
    double _longitude;
    char _NS;
    char _EW;
	int _city;

};


#endif




