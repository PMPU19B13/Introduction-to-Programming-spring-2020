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
	void readPrimitive();
	void readPrimitive(std::fstream& file);
    void removePrimitive(ID);

    ID addRequirement(RequirementType, ID, ID, double* param = nullptr);
    void removeRequirement(ID);

    void updateView();
	void updateView(std::fstream& file);
	void updateMemory(std::fstream& file);

private:
    struct Requirement {
        Storage<ID> objects;
        RequirementType type;
    };

    List<Pair<ID, Requirement>> m_requirements;

    List<Pair<ID, Point>> m_points;
    List<Pair<ID, Segment>> m_segments;
    List<Pair<ID, Circle>> m_circles;
};
