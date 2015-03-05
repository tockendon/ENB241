/* itriangle.h
 * ENB241 Portfolio 2
 *
 * Isosceles Triangle class header
 *
 *  Student #: n8560641
 *  Name: Terrance Ockendon
 */

#ifndef _ITRIANGLE_H_
#define _ITRIANGLE_H_

#include "triangle.h"

// ITriangle class is derived from the Triangle class.
// ITrianle constructor takes inputs of lengths 'a' and 'b' which become
// the inputs for the Triangle class where 'a' is mapped to two sides
// and 'b' mapped to one side of the triangle class.

class ITriangle : public Triangle
{
public:

    // a - length of identical edges, b - base width
    // Constructor
    ITriangle(const double a, const double b);

    // Destructor
    ~ITriangle();
};


#endif
