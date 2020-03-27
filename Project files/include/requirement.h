#pragma once

#include "geometry.h"

class IRequirement
{
public:
	virtual double error() const = 0;
};

class HorizontalRequirement
{
public:
	HorizontalRequirement(Segment* segment) :m_segment(segment)
	{
	}

	virtual double error() const
	{
		return std::abs(m_segment->getEnd().getY() - m_segment->getStart().getY());
	}

private:
	Segment* m_segment;
};

class VerticalRequirement
{
public:
	VerticalRequirement(Segment* segment) :m_segment(segment)
	{
	}

	virtual double error() const
	{
		return std::abs(m_segment->getEnd().getX() - m_segment->getStart().getX());
	}

private:
	Segment* m_segment;
};

class PointOnSegmentRequirement
{
public:
	PointOnSegmentRequirement(Point* point, Segment* segment) :m_point(point), m_segment(segment) 
	{
	}

	virtual double error() const
	{
		return std::abs(m_point->getX() - m_segment->getEnd().getX()) / (m_point->getX() - m_segment->getStart().getX());
	}

private:
	Segment* m_segment;
	Point* m_point;
};
