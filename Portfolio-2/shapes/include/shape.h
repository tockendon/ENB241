/* shape.h
 * ENB241 Portfolio 2
 *
 * Shape class header
 *
 *     DO NOT MODIFY
 */

#ifndef _SHAPE_H_
#define _SHAPE_H_


class Shape
{
public:
    Shape();
    ~Shape();

    virtual double getArea() const = 0;
};

#endif
