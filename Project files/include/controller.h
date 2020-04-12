#pragma once

#include "geometry.h"
#include "storage.h"
#include "list.h"
#include "id.h"
#include "pair.h"
#include "mmapavl.h"

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
	R_PointOnSegment,
	R_PointOnCircle,
	R_Angle,
	R_Parallel,
	R_Distance,
	R_Equal
};


class Controller
{
public:
	Controller();

	ID addPrimitive(PrimitiveType type, Storage<double> params, ID* id = nullptr);
	void removePrimitive(const ID&);

	ID addRequirement(RequirementType, const Storage<ID>&, double* param = nullptr);
	void removeRequirement(const ID&);

	void updateView();

	friend class FileIO;

	Pair<PrimitiveType, Storage<double>> getPrimitiveInfo(ID& id);

	Storage<ID> getAllPrimitiveIDs();

	void readPrimitive(const std::string& fileName);

	void writePrimitive(const std::string& fileName);


private:
	struct Requirement
	{
		Storage<ID> objects;
		RequirementType type;
		double* param;

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

	MMapAVL<ID, Requirement> m_requirements;

	MMapAVL<ID, Point> m_points;
	MMapAVL<ID, Segment> m_segments;
	MMapAVL<ID, Circle> m_circles;
};