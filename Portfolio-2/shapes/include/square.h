/* square.h
 * ENB241 Portfolio 2
 *
 * Square class header
 *
 *  Student #: n8560641
 *  Name: Terrance Ockendon
 */

#ifndef _SQUARE_H_
#define _SQUARE_H_

#include "rectangle.h"

// Square class is derived from the rectangle class.
// Square constructor takes an 'l' edge length which becomes
// both inputs for the edge length and width of the rectangle class.

class Square : public Rectangle
{
public:

    // l - edge length
    // Constructor
    Square(const double l);

    // Destructor
    virtual ~Square();

};


#endif
