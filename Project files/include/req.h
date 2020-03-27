#pragma once

#include"geometry.h"

class IReq {
public:
	virtual double error() = 0;
};
class HorizReq {
public:
	HorizReq(Segment* s) :m_s(s) {}
	virtual double error() { return std::abs(m_s->getEnd().getY() - m_s->getStart().getY());}
private:
	Segment* m_s;
};

class VertReq {
public:
	VertReq(Segment* s) :m_s(s) {}
	virtual double error() { return std::abs(m_s->getEnd().getX() - m_s->getStart().getX()); }
private:
	Segment* m_s;
};

class PointOnSegReq {
public:
	PointOnSegReq(Point* p, Segment* s) :m_p(p), m_s(s) {}
	virtual double error() {
		return std::abs(m_p->getX() - m_s->getEnd().getX()) / (m_p->getX() - m_s->getStart().getX());
	};
private:
	Segment* m_s;
	Point* m_p;
};
