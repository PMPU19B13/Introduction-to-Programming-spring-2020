#pragma once

#include "error.h"

class Point
{
public:
    Point(double x = 0, double y = 0);

    void setX(double x);
    void setY(double y);
    double getX();
    double getY();

private:
    double m_x;
    double m_y;
};

class Segment
{
public:
    Segment(Point *start, Point *end);

    Point getStart();

private:
    Point *m_start;
    Point *m_end;
};

class Circle
{
public:
    Circle(Point *center, double radius);

private:
    Point *m_center;
    double m_radius;
};
