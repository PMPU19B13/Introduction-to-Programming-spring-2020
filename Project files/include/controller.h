#pragma once

#include "geometry.h"
#include "storage.h"
#include "id.h"

enum PrimitiveType
{
    P_Point, // Точка
    P_Segment, // Отрезок
    P_Circle // Окружность
};

enum RequirementType
{
    R_Distance, // Расстояние между объектами
    R_Parallel, // Параллельность отрезков
    R_Equal, // Равенство объектов
    R_PointOnCircle // Точка на окружности
};

class Controller
{
public:
    Controller();

    void addPrimitive(PrimitiveType, Storage<double>);
    void removePrimitive(ID);

    void addRequirement(RequirementType, ID, ID, double* param = nullptr);
    void removeRequirement(ID);


    void updateView();

private:
    Storage<Point> m_points;
    Storage<Segment> m_segments;
    Storage<Circle> m_circles;
};
