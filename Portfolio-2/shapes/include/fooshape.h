/* fooshape.h
 * ENB241 Portfolio 2
 *
 * fooShape class header
 *
 *  Student #: n8560641
 *  Name: Terrance Ockendon
 */

#ifndef _FOOSHAPE_H_
#define _FOOSHAPE_H_

#include "shape.h"

// This class is used to prevent a compound shape being created from compound shapes.

class fooShape : public Shape
{
public:

    // Constructor
    fooShape();

    // Member function
    virtual double getArea() const = 0;

    // Destructor
    virtual ~fooShape();

};

#endif
