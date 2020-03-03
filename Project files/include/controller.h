#pragma once

#include "geometry.h"
#include "storage.h"
#include "id.h"

enum PrimitiveType
{
    P_Point, // точка
    P_Segment, // отрезок
    P_Circle // окружность
    // ... ещё?
};

enum RequirementType
{
    R_Distance, // расстояние между объектами
    R_Parallel, // параллельность отрезков
    R_Equal, // равенство объектов
    R_PointOnCircle // точка на окружности
    // ... ещё?
};

class Controller
{
public:
    Controller();

    void addPrimitive(PrimitiveType, Storage<double>);
    void removePrimitive(ID);

    void addRequirement(RequirementType, ID, ID, double *param = nullptr);
    void removeRequirement(ID);

    // TODO: Implement
    void updateView();

private:
    Storage<Point> m_points;
    Storage<Segment> m_segments;
    Storage<Circle> m_circles;
};
