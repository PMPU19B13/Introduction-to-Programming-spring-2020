#pragma once

#include "geometry.h"
#include "storage.h"
#include "storageli.h"
#include "ID.h"

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

    void updateView();
   
private:
    StorageLi<Point> m_points;
    StorageLi<Segment> m_segments;
    StorageLi<Circle> m_circles;
};
