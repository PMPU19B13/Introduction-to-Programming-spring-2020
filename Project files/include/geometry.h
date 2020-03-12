#pragma once

#include <iostream>
#include "error.h"
#include "storage.h"

class Point
{
public:
    Point(double x = 0, double y = 0);

    void setX(double x);
    void setY(double y);
    double getX() const;
    double getY() const;

    Storage<double> getParams() const;

private:
    double m_x;
    double m_y;
};

std::ostream& operator<<(std::ostream& out, const Point& point);

class Segment
{
public:
    Segment();
    Segment(Point* start, Point* end);

    Point getStart() const;
    Point getEnd() const;

    Storage<double> getParams() const;

private:
    Point* m_start;
    Point* m_end;
};

std::ostream& operator<<(std::ostream& out, const Segment& segment);

class Circle
{
public:
    Circle();
    Circle(Point* center, double radius);

    Point getCenter() const;
    double getRadius() const;

    Storage<double> getParams() const;

private:
    Point* m_center;
    double m_radius;
};

std::ostream& operator<<(std::ostream& out, const Circle& circle);
