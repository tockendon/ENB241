/* component.h
 * ENB241 Portfolio 2
 *
 * Component class header
 * Precondition:    Void       
 * Postcondition:   Valid Component object created
 *
 */

#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include <string>
    using std::string;
#include <sstream>              // Allows strings to be used like cin/cout.
    using std::istringstream;   // Read from string.
	using std::ostringstream;

class Component
{
public:
	// Constructor and Destructor.
    Component();
    virtual ~Component();
    virtual string toString() const = 0;
    virtual double getPowerOut() const = 0;
    double operator+ (double power);
    double operator* (double power);
};


#endif




