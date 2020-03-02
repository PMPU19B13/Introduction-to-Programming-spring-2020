#pragma once
#include "error.h"

using namespace std;

class Point
{
public:
	double x;
	double y;
	Point(double _x = 0, double _y = 0);
};

class Segment
{
public:
	Segment(Point* st, Point* ed);
	Point getStart();
private:
	Point* start;
	Point* end;
};

class Circle
{
public:
	Circle(Point* c, double r);
	Point getStart();
private:
	Point* center;
	double R;
};
