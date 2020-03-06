#include "geometry.h"
#include "storage.h"

Point::Point(double _x, double _y)
{
    x = _x;
    y = _y;
}

Storage<double> Point::getParams() const
{
    Storage<double> params;
    params.AddElem(x);
    params.AddElem(y);
    return params;
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

Storage<double> Segment::getParams() const
{
    Storage<double> params;
    params.AddElem(start->x);
    params.AddElem(start->y);
    params.AddElem(end->x);
    params.AddElem(end->y);
    return params;

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

Storage<double> Circle::getParams() const
{
    Storage<double> params;
    params.AddElem(center->x);
    params.AddElem(center->y);
    params.AddElem(R);
    return params;
}
