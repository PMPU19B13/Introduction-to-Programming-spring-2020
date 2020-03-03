#include <iostream>

#include "controller.h"

Controller::Controller()
{

}

void Controller::addPrimitive(PrimitiveType type, Storage<double> params)
{
    switch (type)
    {
        case P_Point:
            break;

        case P_Segment:
            break;

        case P_Circle:
            break;

        default:
            std::cerr << "No implementation found!" << std::endl;
            throw BadArg();
            break;
    }

}

void Controller::updateView()
{
//        Drawer drawer;
//        for (point in m_points)
//            drawer.drawPrimitive(point);
//        for (segment in m_segments)
//            drawer.drawPrimitive(segment);
//        for (circle in m_circles)
//            drawer.drawPrimitive(circle);
}
