/* rectangle.h
 * ENB241 Portfolio 2
 *
 * Rectangle class header
 *
 *  Student #: n8560641
 *  Name: Terrance Ockendon
 */

#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

#include "fooshape.h"

class Rectangle : public fooShape
{
public:

    // l - length, w - width
    // Constructor
    Rectangle(const double l, const double w);

    // Member function
    virtual double getArea() const;

    // Destructor
    ~Rectangle();

protected:

    // Member variables
    double _l;
    double _w;

};


#endif
