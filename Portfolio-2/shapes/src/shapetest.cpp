/* shapetest.cpp
 * ENB241 Portfolio 2
 *
 * Shape inheritance demonstration
 *
 *  Student #: n8560641
 *  Name: Terrance Ockendon
 */

#include "shape.h"
#include "fooshape.h"
#include "ellipse.h"
#include "circle.h"
#include "triangle.h"
#include "itriangle.h"
#include "etriangle.h"
#include "rectangle.h"
#include "square.h"
#include "compound.h"

#include <iostream>
    using std::cout;
    using std::endl;
	using std::cerr;

const unsigned int NUM_SHAPES = 8;


int main(int argc, char *argv[])
{
    int i;
    Shape *shapes[NUM_SHAPES] = {NULL};

    // Create shapes
    shapes[0] = new Ellipse(2, 0.5);
    shapes[1] = new Circle(1);
    shapes[2] = new Triangle(1, 2, 3);
    shapes[3] = new ITriangle(2, 1);
    shapes[4] = new ETriangle(1);
    shapes[5] = new Rectangle(2, 1);
    shapes[6] = new Square(1);

    // Display area
    cout << endl << "\tSHAPE AREA:" << endl << endl;
    for (i = 0; i < NUM_SHAPES; ++i)
    {
        if (shapes[i])
        {
            cout << "Shape " << i << ": Area = " << shapes[i]->getArea() << endl;
        }
    }



    // DEMONSTRATE ECCENTRICITY FUNCTION FOR ELLIPSE & CIRCLE HERE
    cout << endl << "\tECCENTRICITY FUNCTION FOR ELLIPSE & CIRCLE:" << endl << endl;
    Ellipse *shapes2[2];
    shapes2[0] = new Ellipse(2, 0.5);
    shapes2[1] = new Circle(1);
    cout << "Shape " << "0" << ": Eccentricity = " << shapes2[0]->getEccentricity() << endl;
    cout << "Shape " << "1" << ": Eccentricity = " << shapes2[1]->getEccentricity() << endl;



    // DEMONSTRATE CIRCUMCIRCLE FUNCTION FOR ALL TRIANGLES HERE
    cout << endl << "\tCIRCUMCIRCLE FUNCTION FOR ALL TRIANGLES:" << endl << endl;
    Triangle *shapes3[3];
    shapes3[0] = new Triangle(1, 2, 3);
    shapes3[1] = new ITriangle(2, 1);
    shapes3[2] = new ETriangle(1);
    for(i = 0; i < 3; ++i)
    {
        if (shapes3[i])
        {
            Circle shapes4 = shapes3[i]->getCircumcircle();
            cout << "Shape " << i+2 << ": Circumcircle Area = " << shapes4.getArea() << endl;
        }
    }



    // DEMONSTRATE COMPOUND SHAPES HERE
    cout << endl << "\tCOMPOUND AREA:" << endl << endl;
	fooShape *shapes5[2] = {NULL};
	shapes5[0] = new ITriangle(2, 1);
	shapes5[1] = new Circle(1);
	shapes[7] = new Compound(shapes5[0], shapes5[1]);
    cout << "Shape " << "7" << ": Compound Shape of ITriangle(2, 1) and Circle(1)" << endl;
    cout << "         Compound Shape Area = " << shapes[7]->getArea() << endl;


    cout << endl;

    // deallocate memory
    for (i = 0; i < NUM_SHAPES; ++i)
    {
        if (shapes[i])
        {
            delete shapes[i];
        }
    }

    for (i = 0; i < 2; i++)
    {
		delete shapes2[i];
    }

    for (i = 0; i < 3; i++)
    {
        delete shapes3[i];
    }

    for (i = 0; i < 2; i++)
    {
		delete shapes5[i];
    }

    return 0;
}
