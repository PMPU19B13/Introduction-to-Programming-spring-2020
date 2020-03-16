#include <iostream>
#include <cstddef>
#include <fstream>

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
    List<Pair<ID, Point>>::Marker markerPoint = m_points.createMarker();
    while (markerPoint.isValid())
    {
        drawer.drawPrimitive(P_Point, markerPoint.getValue().value.getParams());
        markerPoint.next();
    }

    List<Pair<ID, Segment>>::Marker markerSegment = m_segments.createMarker();
    while (markerSegment.isValid())
    {
        drawer.drawPrimitive(P_Segment, markerSegment.getValue().value.getParams());
        markerSegment.next();
    }

    List<Pair<ID, Circle>>::Marker markerCircle = m_circles.createMarker();
    while (markerCircle.isValid())
    {
        drawer.drawPrimitive(P_Circle, markerCircle.getValue().value.getParams());
        markerCircle.next();
    }
}

void Controller::removePrimitive(const ID& id)
{
    List<Pair<ID, Point>>::Marker pointMarker = m_points.createMarker();
    while (pointMarker.isValid())
    {
        if (pointMarker.getValue().key.equals(id))
        {
            pointMarker.remove();
            return;
        }
        pointMarker.next();
    }

    List<Pair<ID, Segment>>::Marker segmentMarker = m_segments.createMarker();
    while (segmentMarker.isValid())
    {
        if (segmentMarker.getValue().key.equals(id))
        {
            segmentMarker.remove();
            return;
        }
        segmentMarker.next();
    }

    List<Pair<ID, Circle>>::Marker circleMarker = m_circles.createMarker();
    while (circleMarker.isValid())
    {
        if (circleMarker.getValue().key.equals(id))
        {
            circleMarker.remove();
            return;
        }
        circleMarker.next();
    }

    // Закончить реализацию
}

void Controller::readPrimitive(const std::string& fileName)
{
    std::ifstream file;

    file.open(fileName);

    if (!file.is_open())
    {
        return;
    }

    std::string typeName;

    while (!file.eof())
    {
        file >> typeName;

        if (typeName == "Point")
        {
            std::string temp;
            double x;
            double y;

            // Point { x 12.9 y 16.5 }
            file >> temp >> temp >> x >> temp >> y >> temp;

            Storage<double> args;
            args.add(x);
            args.add(y);

            addPrimitive(P_Point, args);
        }
        else if (typeName == "Segment")
        {
            std::string temp;
            double x1;
            double y1;
            double x2;
            double y2;

            // Segment { start { x 15 y 10 } end { x 16 y 17 } }
            file >> temp >> temp >> temp >> temp >> x1 >> temp >> y1
                 >> temp >> temp >> temp >> temp >> x2 >> temp >> y2 >> temp >> temp;

            Storage<double> args;
            args.add(x1);
            args.add(y1);
            args.add(x2);
            args.add(y2);

            addPrimitive(P_Segment, args);
        }
        else if (typeName == "Circle")
        {
            std::string temp;
            double xCenter;
            double yCenter;
            double radius;

            // Circle { center { x 16 y 17 } radius 4 }
            file >> temp >> temp >> temp >> temp >> xCenter >> temp >> yCenter
                 >> temp >> temp >> radius >> temp;

            Storage<double> args;
            args.add(xCenter);
            args.add(yCenter);
            args.add(radius);

            addPrimitive(P_Circle, args);
        }
        else
        {
            file.close();
            throw Error();
        }
    }

    file.close();
}

void Controller::writePrimitive(const std::string& fileName)
{
    std::ofstream file;

    file.open(fileName);

    if (!file.is_open())
    {
        return;
    }

    List<Pair<ID, Point>>::Marker pointMarker = m_points.createMarker();
    while (pointMarker.isValid())
    {
        Storage<double> args = pointMarker.getValue().value.getParams();
        file << "Point { x " << args[0] << " y " << args[1] << " }" << std::endl;
        pointMarker.next();
    }

    List<Pair<ID, Segment>>::Marker segmentMarker = m_segments.createMarker();
    while (segmentMarker.isValid())
    {
        Storage<double> args = segmentMarker.getValue().value.getParams();
        file << "Segment { start { x " << args[0] << " y " << args[1] << " } end { x "
             << args[2] << " y " << args[3] << " } }" << std::endl;
        segmentMarker.next();
    }

    List<Pair<ID, Circle>>::Marker circleMarker = m_circles.createMarker();
    while (circleMarker.isValid())
    {
        Storage<double> args = circleMarker.getValue().value.getParams();
        file << "Circle { center { x " << args[0] << " y " << args[1] << " } radius "
             << args[2] << " }" << std::endl;
        circleMarker.next();
    }

    file.close();
}