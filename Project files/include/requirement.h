#pragma once

#include <math.h>
#include "geometry.h"

class IRequirement
{
public:
	virtual double error() const = 0;
	//virtual double diff() const = 0;
};

class HorizontalRequirement : public IRequirement
{
public:
	HorizontalRequirement(Segment* segment);

	virtual double error() const;

private:
	Segment* m_segment;
};

class VerticalRequirement : public IRequirement
{
public:
	VerticalRequirement(Segment* segment);

	virtual double error() const;

private:
	Segment* m_segment;
};

class PointOnSegmentRequirement : public IRequirement
{
public:
	PointOnSegmentRequirement(Point* point, Segment* segment);

	virtual double error() const;

private:
	Segment* m_segment;
	Point* m_point;
};

class PointOnCircleRequirement : public IRequirement
{
public:
	PointOnCircleRequirement(Point* point, Circle* circle);

	virtual double error() const;

private:
	Point* m_point;
	Circle* m_circle;
};

class AngleRequirement : public IRequirement
{
public:
	AngleRequirement(Segment* segment1, Segment* segment2, double required_angle);

	virtual double error() const;

private:
	Segment* m_segment1;
	Segment* m_segment2;
	double m_required_angle;
};

class ParallelRequirement : public AngleRequirement
{
public:
	ParallelRequirement(Segment* segment1, Segment* segment2);

private:

};

class DistanceRequirement : public IRequirement
{
public:
	DistanceRequirement(Point* point1, Point* point2);

	virtual double error() const;

private:
	Point* m_point1;
	Point* m_point2;
};

template<typename T>
class EqualRequirement : public IRequirement
{
public:
	EqualRequirement(T* primitive1, T* primitive2);

	virtual double error() const;

private:
	T* m_primitive1;
	T* m_primitive2;
};	


HorizontalRequirement::HorizontalRequirement(Segment* segment) : m_segment(segment)
{
}

double HorizontalRequirement::error() const
{
	return abs(m_segment->getEnd().getY() - m_segment->getStart().getY());
}

VerticalRequirement::VerticalRequirement(Segment* segment) : m_segment(segment)
{
}

double VerticalRequirement::error() const
{
		return abs(m_segment->getEnd().getX() - m_segment->getStart().getX());
}

PointOnSegmentRequirement::PointOnSegmentRequirement(Point* point, Segment* segment) : m_point(point),
                                                                                       m_segment(segment)
{
}

double PointOnSegmentRequirement::error() const
{
	double segment_length = sqrt(pow(m_segment->getEnd().getX() - m_segment->getStart().getX(), 2) +
	                             pow(m_segment->getEnd().getY() - m_segment->getStart().getY(), 2));
	double distance_start = sqrt(pow(m_point->getX() - m_segment->getStart().getX(), 2) +
	                             pow(m_point->getY() - m_segment->getStart().getY(), 2));
	double distance_end = sqrt(pow(m_point->getX() - m_segment->getEnd().getX(), 2) +
	                           pow(m_point->getY() - m_segment->getEnd().getY(), 2));
	return distance_start + distance_end - segment_length;
}

PointOnCircleRequirement::PointOnCircleRequirement(Point* point, Circle* circle) : m_point(point), m_circle(circle)
{
}

double PointOnCircleRequirement::error() const
{
	return pow(m_point->getX() - m_circle->getCenter().getX(), 2) +
	       pow(m_point->getY() - m_circle->getCenter().getY(), 2) - pow(m_circle->getRadius(), 2);
}

AngleRequirement::AngleRequirement(Segment* segment1, Segment* segment2, double required_angle) : m_segment1(segment1),
                                                                                                  m_segment2(segment2),
                                                                                                  m_required_angle(
                                                                                                          required_angle)
{
}

double AngleRequirement::error() const
{
	double x1 = m_segment1->getEnd().getX() - m_segment1->getStart().getX();
	double y1 = m_segment1->getEnd().getY() - m_segment1->getStart().getY();
	double x2 = m_segment2->getEnd().getX() - m_segment2->getStart().getX();
	double y2 = m_segment2->getEnd().getY() - m_segment2->getStart().getY();
	return abs(acos(abs(x1 * x2 + y1 * y2) / sqrt((x1 * x1 + y1 * y1) * (x2 * x2 + y2 * y2))) * (180 / M_PI) -
	           m_required_angle);
}

ParallelRequirement::ParallelRequirement(Segment* segment1, Segment* segment2) : AngleRequirement(segment1, segment2, 0)
{
}

DistanceRequirement::DistanceRequirement(Point* point1, Point* point2) : m_point1(point1), m_point2(point2)
{
}

double DistanceRequirement::error() const
{
	return sqrt(pow(m_point2->getX() - m_point1->getX(), 2) + pow(m_point2->getY() - m_point1->getY(), 2));
}

template<typename T>
EqualRequirement<T>::EqualRequirement(T* primitive1, T* primitive2) : m_primitive1(primitive1), m_primitive2(primitive2)
{
}

template<>
double EqualRequirement<Point>::error() const
{
	return sqrt(
	        pow(m_primitive2->getX() - m_primitive1->getX(), 2) + pow(m_primitive2->getY() - m_primitive1->getY(), 2));
}

template<>
double EqualRequirement<Segment>::error() const
{
	double length1 = sqrt(pow(m_primitive1->getEnd().getX() - m_primitive1->getStart().getX(), 2) +
	                      pow(m_primitive1->getEnd().getY() - m_primitive1->getStart().getY(), 2));
	double length2 = sqrt(pow(m_primitive2->getEnd().getX() - m_primitive2->getStart().getX(), 2) +
	                      pow(m_primitive2->getEnd().getY() - m_primitive2->getStart().getY(), 2));
	return abs(length1 - length2);
}

template<>
double EqualRequirement<Circle>::error() const
{
	return abs(m_primitive2->getRadius() - m_primitive1->getRadius());
}
