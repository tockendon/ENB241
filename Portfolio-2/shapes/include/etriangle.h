/* etriangle.h
 * ENB241 Portfolio 2
 *
 * Equilateral Triangle class header
 *
 *  Student #: n8560641
 *  Name: Terrance Ockendon
 */

#ifndef _ETRIANGLE_H_
#define _ETRIANGLE_H_

#include "triangle.h"

// ETriangle class is derived from the triangle class.
// ETriangle constructor takes a side of 'l' length which becomes
// the inputs for all sides of the triangle class.

class ETriangle : public Triangle
{
public:

    // l - edge length
    // Constructor
    ETriangle(const double l);

    //Destructor
    virtual ~ETriangle();

};


#endif
