#include <iostream>

#include "controller.h"
#include "error.h"
#include "drawer.h"

Controller::Controller()
{

}

void Controller::addPrimitive(PrimType pt, Storage<double> params)
{
    switch (pt)
    {
        case P_Point:
            if (params.TotalSize() == 2)
            {
                m_points.AddElem(Point(params[0], params[1]));
            }
            else
                throw(BadArg());
            break;

        case P_Segment:
            if (params.TotalSize() == 4)
            {
                m_points.AddElem(Point(params[0], params[1]));
                Point* st = &m_points[m_points.TotalSize() - 1];
                m_points.AddElem(Point(params.GetElemByNum(2), params.GetElemByNum(3)));
                Point *en = &m_points[m_points.TotalSize() - 1];

                m_segments.AddElem(Segment(st, en));
            }
            else
                throw(BadArg());
            break;

        case P_Circle:
            if (params.TotalSize() == 3)
            {
                m_points.AddElem(Point(params[0], params[1]));
                Point* cen = &m_points[m_points.TotalSize() - 1];

                m_circles.AddElem(Circle(cen, params[2]));
            }
            else
                throw(BadArg());
            break;
    }

}

void Controller::updateView()
{
    Drawer drawer;
    for (size_t i = 0; i < m_points.TotalSize(); ++i)
    {
        drawer.drawPrimitive(P_Point, m_points[i].getParams());
    }
    for (size_t i = 0; i < m_segments.TotalSize(); ++i)
    {
        drawer.drawPrimitive(P_Segment, m_segments[i].getParams());
    }
    for (size_t i = 0; i < m_circles.TotalSize(); ++i)
    {
        drawer.drawPrimitive(P_Circle, m_circles[i].getParams());
    }
}

