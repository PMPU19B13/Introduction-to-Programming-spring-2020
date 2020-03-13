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
        {
            // Добавляем точку
            ID id;
            m_points.add(Pair<ID, Point>(id, Point(params[0], params[1])));
            return id;
        }
        else
            throw BadArgument();
        break;

    case P_Segment:
        // Проверяем параметры
        if (params.size() == 4)
        {
            ID id1;
            // Добавляем точки, определяющие отрезок
            m_points.add(Pair<ID, Point>(id1, Point(params[0], params[1])));
            Point* start = &(m_points[m_points.size() - 1].value);

            ID id2;
            m_points.add(Pair<ID, Point>(id2, Point(params[2], params[3])));
            Point* end = &(m_points[m_points.size() - 1].value);

            // И сам отрезок
            ID id3;
            m_segments.add(Pair<ID, Segment>(id3, Segment(start, end)));
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
            ID id1;
            m_points.add(Pair<ID, Point>(id1, Point(params[0], params[1])));
            Point* center = &(m_points[m_points.size() - 1].value);

            // И саму окружность
            ID id2;
            m_circles.add(Pair<ID, Circle>(id2, Circle(center, params[2])));
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
        drawer.drawPrimitive(P_Point, m_points[i].value.getParams());

    for (size_t i = 0; i < m_segments.size(); ++i)
        drawer.drawPrimitive(P_Segment, m_segments[i].value.getParams());

    for (size_t i = 0; i < m_circles.size(); ++i)
        drawer.drawPrimitive(P_Circle, m_circles[i].value.getParams());
}

void Controller::removePrimitive(ID id)
{
    List<Pair<ID, Point>>::Marker marker = m_points.createMarker();

    while (marker.hasNext())
    {
        if (marker.getValue().key.equals(id))
        {
            // remove point from m_points
            return;
        }
        marker.next();
    }

    // Закончить реализацию
}