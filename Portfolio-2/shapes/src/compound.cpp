/* compound.cpp
 * ENB241 Portfolio 2
 *
 * Compound class implementation
 *
 *  Student #: n8560641
 *  Name: Terrance Ockendon
 */
#include <iostream>
#include "compound.h"

// Constructor
Compound::Compound(fooShape *poly1, fooShape *poly2)
{
    _poly1 = poly1;
    _poly2 = poly2;
}

// getArea - Gets area of two shapes and returns the sum of both areas.
double Compound::getArea() const
{
    return _poly1->getArea()+_poly2->getArea();
}

// Destructor
Compound::~Compound()
{
}
