#pragma once

#include "geometry.h"
#include "storage.h"
#include "ID.h"
#include "drawer.h"

enum PrimType
{
    P_Point, // точка
    P_Segment, // отрезок
    P_Circle // окружность
    // ... ещё?
};

enum ReqType
{
    R_Distance, // расстояние между объектами
    R_Paral, // параллельность отрезков
    R_Eq, // равенство объектов
    R_PonC // точка на окружности
    // ... ещё?
};

class Controller
{
public:
    Controller();

    void addPrimitive(PrimType, Storage<double>);
    void delPrimitive(ID);

    void addRequirement(ReqType, ID, ID, double *param = nullptr);
    void delRequirement(ID);

    void updateView()
    {
//        Drawer drawer;
//        for (point in m_points)
//            drawer.drawPrimitive(point);
//        for (segment in m_segments)
//            drawer.drawPrimitive(segment);
//        for (circle in m_circles)
//            drawer.drawPrimitive(circle);
    }

private:
    Storage<Point> m_points;
    Storage<Segment> m_segments;
    Storage<Circle> m_circles;
};
