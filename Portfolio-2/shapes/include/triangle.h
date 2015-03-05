/* triangle.h
 * ENB241 Portfolio 2
 *
 * Triangle class header
 *
 *  Student #: n8560641
 *  Name: Terrance Ockendon
 */

#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "fooshape.h"
#include "circle.h"

class Triangle : public fooShape
{
public:

    // a, b, c - edge lengths
    // Constructor
    Triangle(const double a, const double b, const double c);

    // Member functions
    double getArea() const;
    Circle getCircumcircle();

    // Destructor
    ~Triangle();

protected:

    // Member Variables
    double _a;
    double _b;
    double _c;

};


#endif
