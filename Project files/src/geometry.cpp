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

Segment::Segment() = default;


Point Segment::getStart()
{
    return *start;
}

Point Segment::getEnd()
{
    return *end;
}

Circle::Circle() = default;

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

Point Circle::getCenter()
{
    return *center;
}

double Circle::getRadius()
{
    return R;
}
