/* circle.h
 * ENB241 Portfolio 2
 *
 * Circle class header
 *
 *  Student #: n8560641
 *  Name: Terrance Ockendon
 */

#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include "ellipse.h"

// Circle class is derived from the elipse class.
// Circle constructor takes an 'r' radius which becomes
// both inputs for the ellipse class.

class Circle : public Ellipse
{
public:
    // r - radius
    // Constructor
    Circle(const double r);

    // Destructor
    virtual ~Circle();
};


#endif
