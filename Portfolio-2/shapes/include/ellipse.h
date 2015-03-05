/* ellipse.h
 * ENB241 Portfolio 2
 *
 * Ellipse class header
 *
 *  Student #: n8560641
 *  Name: Terrance Ockendon
 */

#ifndef _ELLIPSE_H_
#define _ELLIPSE_H_

#include "fooshape.h"

const double PI = 3.141593;

class Ellipse : public fooShape
{
public:

    // a - semi-major axis, b - semi-minor axis
    // Constructor
    Ellipse(const double a, const double b);

    // Member functions
    virtual double getArea() const;
    virtual double getEccentricity() const;

    // Destructor
    virtual ~Ellipse();

protected:

    // Member variables
    double _a;
    double _b;

};


#endif
