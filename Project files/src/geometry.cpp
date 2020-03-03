#include "geometry.h"

Point::Point(double x, double y)
{
    m_x = x;
    m_y = y;
}

void Point::setX(double x) {
    m_x = x;
}

void Point::setY(double y) {
    m_y = y;
}

double Point::getX() {
    return m_x;
}

double Point::getY() {
    return m_y;
}

Segment::Segment(Point *start, Point *end)
{
    if ((start != nullptr) && (end != nullptr))
    {
        m_start = start;
        m_end = end;
    }
    else
    {
        throw (Error());
    }
}

Point Segment::getStart()
{
    return *m_start;
}

Circle::Circle(Point *p, double r)
{

}
