/* triangle.cpp
 * ENB241 Portfolio 2
 *
 * Triangle class implementation
 *
 *  Student #: n8560641
 *  Name: Terrance Ockendon
 */

#include <cmath>
#include "triangle.h"

// Constructor
Triangle::Triangle(const double a, const double b, const double c)
{
    _a = a;
    _b = b;
    _c = c;
}

// getArea - Gets the area of a triangle
double Triangle::getArea() const
{
    double s;
    s = ((_a + _b +_c )/2);
    return sqrt(s * (s - _a) * (s - _b) * (s -_c ));
}

// getCircumcircle - returns the cumcircle area of for the triangle
Circle Triangle::getCircumcircle()
{
    double circRadius;
    circRadius = (_a*_b*_c)/(4*Triangle::getArea());
    Circle temp(circRadius);
    return temp;
}

// Destructor
Triangle::~Triangle()
{
}
