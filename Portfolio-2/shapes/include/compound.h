/* compound.h
 * ENB241 Portfolio 2
 *
 * Compound Shape class header
 *
 *  Student #: n8560641
 *  Name: Terrance Ockendon
 */

#ifndef _COMPOUND_H_
#define _COMPOUND_H_

#include "shape.h"
#include "fooshape.h"

// Compound class take inputs of any shape object excluding compound shapes.
// The two shapes areas are then calculated.

class Compound : public Shape
{
public:

    // poly1 and poly2 - shape objects
    // Constructor
    Compound(fooShape *poly1, fooShape *poly2);

    // Member functions
    double getArea() const;

    //Destructor
    ~Compound();

protected:
    Shape *_poly1;
    Shape *_poly2;
};


#endif
