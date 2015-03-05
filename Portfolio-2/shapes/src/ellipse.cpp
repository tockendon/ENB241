/* ellipse.cpp
 * ENB241 Portfolio 2
 *
 * Ellipse class implementation
 *
 *  Student #: n8560641
 *  Name: Terrance Ockendon
 */

#include <cmath>
#include "ellipse.h"

// Constructor
Ellipse::Ellipse(const double a, const double b)
{
    _a = a;
    _b = b;
}

// getArea -  Gets area of ellipse
double Ellipse::getArea() const
{
    return PI*_a*_b;
}

// getEccentricity - Gets eccentricity of ellipse
double Ellipse::getEccentricity() const
{
    return sqrt((pow(_a,2)-pow(_b,2))/pow(_a,2));
}

// Deconstructor
Ellipse::~Ellipse()
{
}
