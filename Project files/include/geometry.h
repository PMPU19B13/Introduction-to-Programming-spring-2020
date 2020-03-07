#pragma once

#include "error.h"
#include "storage.h"

class Point
{
public:
    Point(double x = 0, double y = 0);

    void setX(double x);
    void setY(double y);
    double getX();
    double getY();

    Storage<double> getParams() const;

private:
    double m_x;
    double m_y;
};

class Segment
{
public:
    Segment();
    Segment(Point* start, Point* end);

    Point& getStart();
    Point& getEnd();

    Storage<double> getParams() const;

private:
    Point* m_start;
    Point* m_end;
};

class Circle
{
public:
    Circle();
    Circle(Point* center, double radius);

    Point& getCenter();
    double getRadius() const;

    Storage<double> getParams() const;

private:
    Point* m_center;
    double m_radius;
};
