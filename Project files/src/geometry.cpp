#include "geometry.h"
#include "storage.h"

Point::Point(double x, double y)
{
    m_x = x;
    m_y = y;
}

void Point::setX(double x)
{
    m_x = x;
}

void Point::setY(double y)
{
    m_y = y;
}

double Point::getX() const
{
    return m_x;
}

double Point::getY() const
{
    return m_y;
}

Storage<double> Point::getParams() const
{
    Storage<double> params;
    params.add(m_x);
    params.add(m_y);
    return params;
}

Segment::Segment()
{
    Point start = Point(0.0, 0.0);
    Point end = Point(0.0, 0.0);

    m_start = &start;
    m_end = &end;
}

Segment::Segment(Point* start, Point* end)
{
    if (start == nullptr || end == nullptr)
        throw BadArgument();

    m_start = start;
    m_end = end;
}

Point Segment::getStart() const
{
    return *m_start;
}

Point Segment::getEnd() const
{
    return *m_end;
}

Storage<double> Segment::getParams() const
{
    Storage<double> params;
    params.add(m_start->getX());
    params.add(m_start->getY());
    params.add(m_end->getX());
    params.add(m_end->getY());
    return params;
}

Circle::Circle()
{
    Point center = Point(0.0, 0.0);
    m_center = &center;
    m_radius = 1;
}

Circle::Circle(Point* center, double radius)
{
    if (center == nullptr)
        throw BadArgument();

    m_center = center;
    m_radius = radius;
}

Storage<double> Circle::getParams() const
{
    Storage<double> params;
    params.add(m_center->getX());
    params.add(m_center->getY());
    params.add(m_radius);
    return params;
}

Point Circle::getCenter() const
{
    return *m_center;
}

double Circle::getRadius() const
{
    return m_radius;
}

std::ostream& operator<<(std::ostream& out, const Point& point)
{
    out << "Point - (" << point.getX() << ", " << point.getY() << ")";
    return out;
}

std::ostream& operator<<(std::ostream& out, const Segment& segment)
{
    out << "Segment - start: (" << segment.getStart().getX() << ", " << segment.getStart().getY() << "), end: ("
        << segment.getEnd().getX() << ", " << segment.getEnd().getY() << ")";
    return out;
}

std::ostream& operator<<(std::ostream& out, const Circle& circle)
{
    out << "Circle - center: (" << circle.getCenter().getX() << ", " << circle.getCenter().getY()
        << "), radius: " << circle.getRadius();
    return out;
}
