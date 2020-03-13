#pragma once

#include "geometry.h"
#include "storage.h"
#include "list.h"
#include "id.h"
#include "pair.h"

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

    ID addPrimitive(PrimitiveType, Storage<double>);
    void removePrimitive(ID);

    void addRequirement(RequirementType, ID, ID, double* param = nullptr);
    void removeRequirement(ID);

    void updateView();

private:
    List<pair<ID, Point>> m_points;
    List<pair<ID, Segment>> m_segments;
    List<pair<ID, Circle>> m_circles;
};
