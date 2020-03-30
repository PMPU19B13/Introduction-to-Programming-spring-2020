#pragma once

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


HorizontalRequirement::HorizontalRequirement(Segment* segment) : m_segment(segment)
{
}

double HorizontalRequirement::error() const
{
    return std::abs(m_segment->getEnd().getY() - m_segment->getStart().getY());
}

VerticalRequirement::VerticalRequirement(Segment* segment) : m_segment(segment)
{
}

double VerticalRequirement::error() const
{
    return std::abs(m_segment->getEnd().getX() - m_segment->getStart().getX());
}

PointOnSegmentRequirement::PointOnSegmentRequirement(Point* point, Segment* segment) : m_point(point), m_segment(segment)
{
}

double PointOnSegmentRequirement::error() const
{
    return std::abs(m_point->getX() - m_segment->getEnd().getX()) / (m_point->getX() - m_segment->getStart().getX());
}
