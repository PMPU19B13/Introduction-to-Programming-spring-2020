#include <iostream>
#include <cstddef>
#include <fstream>

#include "controller.h"
#include "error.h"
#include "drawer.h"
#include "reader.h"

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
	if (m_points.size() != 0)
	{
		List<Pair<ID, Point>>::Marker markerPoint = m_points.createMarker();
		while (true)
		{
			drawer.drawPrimitive(P_Point, markerPoint.getValue().value.getParams());
			if (markerPoint.hasNext())
				markerPoint.next();
			else
				break;
		}
	}

	if (m_segments.size() != 0)
	{
		List<Pair<ID, Segment>>::Marker markerSegment = m_segments.createMarker();
		while (true)
		{
			drawer.drawPrimitive(P_Segment, markerSegment.getValue().value.getParams());
			if (markerSegment.hasNext())
				markerSegment.next();
			else
				break;
		}
	}

	if (m_circles.size() != 0)
	{
		List<Pair<ID, Circle>>::Marker markerCircle = m_circles.createMarker();
		while (true)
		{
			drawer.drawPrimitive(P_Circle, markerCircle.getValue().value.getParams());
			if (markerCircle.hasNext())
				markerCircle.next();
			else
				break;
		}
	}
}

void Controller::updateView(std::fstream& file)
{
	// Создаем объект, отвечающий за рисование
	Drawer drawer;

	// Проходим по всем типам примитивов и рисуем их
	if (m_points.size() != 0)
	{
		List<Pair<ID, Point>>::Marker markerPoint = m_points.createMarker();
		while (true)
		{
			drawer.drawPrimitive(file, P_Point, markerPoint.getValue().value.getParams());
			if (markerPoint.hasNext())
				markerPoint.next();
			else
				break;
		}
	}

	if (m_segments.size() != 0)
	{
		List<Pair<ID, Segment>>::Marker markerSegment = m_segments.createMarker();
		while (true)
		{
			drawer.drawPrimitive(file, P_Segment, markerSegment.getValue().value.getParams());
			if (markerSegment.hasNext())
				markerSegment.next();
			else
				break;
		}
	}

	if (m_circles.size() != 0)
	{
		List<Pair<ID, Circle>>::Marker markerCircle = m_circles.createMarker();
		while (true)
		{
			drawer.drawPrimitive(file, P_Circle, markerCircle.getValue().value.getParams());
			if (markerCircle.hasNext())
				markerCircle.next();
			else
				break;
		}
	}
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

void Controller::readPrimitive()
{
	Reader reader;
	PrimitiveType* type = reader.getType();
	Storage<double> params = reader.getParams();

	if (!(type == nullptr))
		addPrimitive(*type, params);
	else std::cout << "Can't read!" << std::endl;
}

void Controller::readPrimitive(std::fstream& file)
{
	if (!file.is_open())
	{
		std::cout << "File is not open!" << std::endl;
		return;
	}

	Reader reader(file);
	PrimitiveType* type = reader.getType();
	Storage<double> params = reader.getParams();

	if (!(type == nullptr))
		addPrimitive(*type, params);
	else std::cout << "Can't read!" << std::endl;
}

void Controller::updateMemory(std::fstream& file)
{
	if (!file.is_open())
	{
		std::cout << "File is not open!" << std::endl;
		return;
	}

	while (!file.eof())
	{
		readPrimitive(file);

	}
}
