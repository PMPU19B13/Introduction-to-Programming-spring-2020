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
    R_SetConstant,
    R_Horizontal,
    R_Vertical,
    R_Angle,
    R_Distance, // Расстояние между объектами
    R_Parallel, // Параллельность отрезков
    R_Equal, // Равенство объектов
    R_IsOn
};

class Controller
{
public:
    Controller();

    ID addPrimitive(PrimitiveType, Storage<double>);
    void removePrimitive(ID);

    ID addRequirement(RequirementType, ID, ID, double* param = nullptr);
    void removeRequirement(ID);

    void updateView();

private:
    struct Requirement {
        Storage<ID> objects;
        RequirementType type;
    };
    List<pair<ID, Requirement>> m_requirements;

    List<pair<ID, Point>> m_points;
    List<pair<ID, Segment>> m_segments;
    List<pair<ID, Circle>> m_circles;
};
