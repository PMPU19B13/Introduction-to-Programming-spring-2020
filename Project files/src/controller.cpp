#include <iostream>
#include <cstddef>

#include "controller.h"
#include "error.h"
#include "drawer.h"

Controller::Controller()
{

}

ID Controller::addPrimitive(PrimitiveType type, Storage<double> params)
{
    switch (type)
    {
    case P_Point:
        // Проверяем параметры
        if (params.size() == 2)
            // Добавляем точку
            m_points.add(Point(params[0], params[1]));
            return ID();
            else
            throw BadArgument();
        break;

    case P_Segment:
        // Проверяем параметры
        if (params.size() == 4)
        {
            // Добавляем точки, определяющие отрезок
            m_points.add(Point(params[0], params[1]));
            Point* start = &m_points[m_points.size() - 1];
            m_points.add(Point(params.get(2), params.get(3)));
            Point* end = &m_points[m_points.size() - 1];

            // И сам отрезок
            m_segments.add(Segment(start, end));
            return ID();
        }
        else
            throw BadArgument();
        break;

    case P_Circle:
        // Проверяем параметры
        if (params.size() == 3)
        {
            // Добавляем центр окружности
            m_points.add(Point(params[0], params[1]));
            Point* center = &m_points[m_points.size() - 1];

            // И саму окружность
            m_circles.add(Circle(center, params[2]));
            return ID();
        }
        else
            throw BadArgument();
        break;

    default:
        // Выводим ошибку в случае отсутствия реализации для типа
        std::cerr << "No implementation found!" << std::endl;
        throw BadArgument();
    }

}

void Controller::updateView()
{
    // Создаем объект, отвечающий за рисование
    Drawer drawer;

    // Проходим по всем типам примитивов и рисуем их
    for (size_t i = 0; i < m_points.size(); ++i)
        drawer.drawPrimitive(P_Point, m_points[i].getParams());

    for (size_t i = 0; i < m_segments.size(); ++i)
        drawer.drawPrimitive(P_Segment, m_segments[i].getParams());

    for (size_t i = 0; i < m_circles.size(); ++i)
        drawer.drawPrimitive(P_Circle, m_circles[i].getParams());
}
