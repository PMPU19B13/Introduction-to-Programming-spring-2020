#include "geometry.h"

Point::Point(double _x, double _y)
{
    x = _x;
    y = _y;
}

Segment::Segment(Point *st, Point *ed)
{
    if ((st != nullptr) && (ed != nullptr))
    {
        start = st;
        end = ed;
    }
    else
    {
        throw (Error());
    }
}

Point Segment::getStart()
{
    return *start;
}

Circle::Circle(Point* p, double r)
{
    if (p != nullptr)
    {
        center = p;
        R = r;
    }
    else
    {
        throw (Error());
    }
}