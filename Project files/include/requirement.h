#pragma once

#include <math.h>
#include "geometry.h"

class IRequirement
{
public:
	virtual double error() const = 0;
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
	AngleRequirement(Segment* segment1, Segment* segment2);

	virtual double error() const;

private:
	Segment* m_segment1;
	Segment* m_segment2;
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

class EqualRequirement : public IRequirement
{
public:
	EqualRequirement(Segment* segment1, Segment* segment2);

	EqualRequirement(Circle* circle1, Circle* circle2);

	EqualRequirement(Point* point1, Point* point2);

	virtual double error() const;

private:
	Segment* m_segment1;
	Segment* m_segment2;
	Circle* m_circle1;
	Circle* m_circle2;
	Point* m_point1;
	Point* m_point2;
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

AngleRequirement::AngleRequirement(Segment* segment1, Segment* segment2) : m_segment1(segment1), m_segment2(segment2)
{
}

double AngleRequirement::error() const
{
	double x1 = m_segment1->getEnd().getX() - m_segment1->getStart().getX();
	double y1 = m_segment1->getEnd().getY() - m_segment1->getStart().getY();
	double x2 = m_segment2->getEnd().getX() - m_segment2->getStart().getX();
	double y2 = m_segment2->getEnd().getY() - m_segment2->getStart().getY();
	return acos(abs(x1 * x2 + y1 * y2) / sqrt((x1 * x1 + y1 * y1) * (x2 * x2 + y2 * y2)));
}

ParallelRequirement::ParallelRequirement(Segment* segment1, Segment* segment2) : AngleRequirement(segment1, segment2)
{
}

DistanceRequirement::DistanceRequirement(Point* point1, Point* point2) : m_point1(point1), m_point2(point2)
{
}

double DistanceRequirement::error() const
{
	return sqrt(pow(m_point2->getX() - m_point1->getX(), 2) + pow(m_point2->getY() - m_point1->getY(), 2));
}

EqualRequirement::EqualRequirement(Segment* segment1, Segment* segment2) : m_segment1(segment1), m_segment2(segment2),
                                                                           m_circle1(nullptr), m_circle2(nullptr),
                                                                           m_point1(nullptr), m_point2(nullptr)
{
}

EqualRequirement::EqualRequirement(Circle* circle1, Circle* circle2) : m_segment1(nullptr), m_segment2(nullptr),
                                                                       m_circle1(circle1), m_circle2(circle2),
                                                                       m_point1(nullptr), m_point2(nullptr)
{
}

EqualRequirement::EqualRequirement(Point* point1, Point* point2) : m_segment1(nullptr), m_segment2(nullptr),
                                                                   m_circle1(nullptr), m_circle2(nullptr),
                                                                   m_point1(point1), m_point2(point2)
{
}

double EqualRequirement::error() const
{
	if (m_segment1 != nullptr && m_segment2 != nullptr)
	{
		double length1 = sqrt(pow(m_segment1->getEnd().getX() - m_segment1->getStart().getX(), 2) +
		                      pow(m_segment1->getEnd().getY() - m_segment1->getStart().getY(), 2));
		double length2 = sqrt(pow(m_segment2->getEnd().getX() - m_segment2->getStart().getX(), 2) +
		                      pow(m_segment2->getEnd().getY() - m_segment2->getStart().getY(), 2));
		return abs(length1 - length2);
	}

	if (m_circle1 != nullptr && m_circle2 != nullptr)
	{
		return abs(m_circle1->getRadius() - m_circle2->getRadius());
	}

	if (m_point1 != nullptr && m_point2 != nullptr)
	{
		return abs(m_point2->getX() - m_point1->getX()) + abs(m_point2->getY() - m_point1->getY());
	}
}
