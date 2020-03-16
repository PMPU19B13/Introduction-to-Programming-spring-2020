#pragma once

#include "geometry.h"
#include "storage.h"
#include "list.h"
#include "id.h"
#include "pair.h"

enum PrimitiveType
{
    P_Point,
    P_Segment,
    P_Circle
};

enum RequirementType
{
    R_SetConstant,
    R_Horizontal,
    R_Vertical,
    R_Angle,
    R_Distance,
    R_Parallel,
    R_Equal,
    R_IsOn
};

class Controller
{
public:
    Controller();

    ID addPrimitive(PrimitiveType, Storage<double>);
    void removePrimitive(const ID&);

    ID addRequirement(RequirementType, const Storage<ID>&, double* param = nullptr);
    void removeRequirement(ID);

    void readPrimitive(const std::string& fileName);
    void writePrimitive(const std::string& fileName);

    void updateView();

private:
    struct Requirement
    {
        Storage<ID> objects;
        RequirementType type;
        double *param;

        double eval(/*...*/)
        {
            switch (type)
            {
            case R_Vertical:
                // Взять x1 и x2 для отрезка и вернуть квадрат разницы двух значений
                break;
            }
        }
    };

    bool tryAddRequirement(RequirementType, const Storage<ID>&, double* param = nullptr);

    void backupState();
    void restoreState();

    List<Pair<ID, Requirement>> m_requirements;

    List<Pair<ID, Point>> m_points;
    List<Pair<ID, Segment>> m_segments;
    List<Pair<ID, Circle>> m_circles;
};
