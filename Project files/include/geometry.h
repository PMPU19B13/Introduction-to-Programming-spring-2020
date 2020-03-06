#pragma once

#include "error.h"
#include "storage.h"

class Point
{
public:
    double x;
    double y;

    Point(double _x = 0, double _y = 0);
    Storage<double> getParams() const; //{ x, y }
};

class Segment
{
public:
    Segment();
    Segment(Point *st, Point *ed);

    Point getStart();
    Point getEnd();
    Storage<double> getParams() const; //{ st_x, st_y, en_x, en_y}

private:
    Point *start;
    Point *end;
};

class Circle
{
public:
    Circle();
    Circle(Point* p, double r);

    Point getCenter();
    double getRadius();
    Storage<double> getParams() const; //{ cen_x, cen_y, rad }

private:
    Point *center;
    double R;
};
