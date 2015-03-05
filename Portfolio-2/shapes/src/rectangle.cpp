/* rectangle.cpp
 * ENB241 Portfolio 2
 *
 * Rectangle class implementation
 *
 *  Student #: n8560641
 *  Name: Terrance Ockendon
 */

#include "rectangle.h"

// Constructor
Rectangle::Rectangle(const double l, const double w)
{
    _l = l;
    _w = w;
}

// getArea - Gets area of rectangle
double Rectangle::getArea() const
{
    return _l*_w;
}

// Destructor
Rectangle::~Rectangle()
{
}
