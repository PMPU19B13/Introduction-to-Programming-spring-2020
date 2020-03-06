#include <iostream>
#include <drawer.h>

#include "controller.h"

Controller::Controller() = default;

void Controller::addPrimitive(PrimitiveType type, Storage<double> params)
{
    switch (type)
    {
        case P_Point:
            if (params.size() == 2)
                m_points.add(Point(params.get(0), params.get(1)));
            else
                throw BadArg();
            break;

        case P_Segment:
            if (params.size() == 4)
            {
                m_points.add(Point(params.get(0), params.get(1)));
                Point start = m_points.get(m_points.size() - 1);
                m_points.add(Point(params.get(2), params.get(3)));
                Point end = m_points.get(m_points.size() - 1);

                m_segments.add(Segment(&start, &end));
            }
            else
                throw BadArg();
            break;

        case P_Circle:
            if (params.size() == 3)
            {
                m_points.add(Point(params.get(0), params.get(1)));
                Point center = m_points.get(m_points.size() - 1);

                m_circles.add(Circle(&center, params.get(2)));
            }
            else
                throw BadArg();
            break;

        default:
            std::cerr << "No implementation found!" << std::endl;
            throw BadArg();
            break;
    }

}

void Controller::updateView()
{
    Drawer drawer;
    for (int i = 0; i < m_points.size(); ++i)
    {
//        drawer.drawPrimitive(m_points.get(i));
    }
    for (int i = 0; i < m_segments.size(); ++i)
    {
//        drawer.drawPrimitive(m_segments.get(i));
    }
    for (int i = 0; i < m_circles.size(); ++i)
    {
//        drawer.drawPrimitive(m_circles.get(i));
    }
}
