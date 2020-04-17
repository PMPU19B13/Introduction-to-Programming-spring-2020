#pragma once

#include <cmath>

class Drawer;

#ifndef __C_H_INCLUDED__
#define __C_H_INCLUDED__

#include "geometry.h"
#include "storage.h"
#include "list.h"
#include "id.h"
#include "mmapavl.h"
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
	Drawer* drawer;

	Controller();

	ID addPrimitive(PrimitiveType type, Storage<double> params, ID* id = nullptr);
	void removePrimitive(const ID&);

	ID addRequirement(RequirementType, const Storage<ID>&, double* param = nullptr);
	void removeRequirement(const ID&);

	void readPrimitive(const std::string& fileName);

	void writePrimitive(const std::string& fileName);
  
	Pair<PrimitiveType, Storage<double>> getPrimitiveInfo(ID& id);
  
	friend class FileIO;
  
	void setDrawer(Drawer* dr)
	{
		drawer = dr;
	}

	Storage<ID> getAllPrimitiveIDs();

	void updateView();

	Point* checkNearPoint(float x, float y) {
		float minDis = -1;
		Point* p = nullptr;
		List<Pair<ID, Point>>::Marker markerPoint = m_points.createMarker();
		while (markerPoint.isValid())
		{
			Storage<double> xy = markerPoint.getValue().value.getParams();
			float dis = pow(pow(xy[0] - x, 2) + pow(xy[1]-y, 2), 0.5);
			if (dis < 10 && (minDis = -1 || dis < minDis)) {
				minDis = dis;
				p = &(markerPoint.getValue().value);
			}
			markerPoint.next();
		}
		return p;
	}

	template<typename T>
	T min(T a, T b) {
		return (a < b) ? a : b;
	}
	template<typename T>
	T max(T a, T b) {
		return (a > b) ? a : b;
	}

	Circle* checkNearCircle(float x, float y) {
		float minDelta = -1;
		Circle* p = nullptr;
		List<Pair<ID, Circle>>::Marker markerCircle = m_circles.createMarker();
		while (markerCircle.isValid())
		{
			Storage<double> xyr = markerCircle.getValue().value.getParams();
			float dis = pow(pow(xyr[0] - x, 2) + pow(xyr[1] - y, 2), 0.5);
			if (abs(dis - xyr[2]) < 5 && ((abs(dis - xyr[2])<minDelta)||minDelta==-1)) {
				minDelta = dis;
				p = &(markerCircle.getValue().value);
			}
			markerCircle.next();
		}
		return p;
	}

	Pair<Point*,Segment*> checkNearSegment(float x, float y) {
		float minDelta = -1;
		Point* p = new Point(x, y);
		Segment* s = nullptr;
		List<Pair<ID, Segment>>::Marker markerSegment = m_segments.createMarker();
		while (markerSegment.isValid())
		{
			Storage<double> xyXY = markerSegment.getValue().value.getParams();
			if(//если точка вне отрезка, но дельта вершин более пяти
				((x<min(xyXY[0],xyXY[2]) || x>max(xyXY[0],xyXY[2])) && abs(xyXY[0]-xyXY[2])>5) 
				|| 
				((y<min(xyXY[1],xyXY[3]) || y>max(xyXY[1],xyXY[3])) && abs(xyXY[1]-xyXY[3])>5)
				) {
				markerSegment.next();
				continue;
			}
			int n[] = { -(xyXY[3] - xyXY[1]),xyXY[2] - xyXY[0] };
			double dis = ((x - xyXY[0]) * n[0] + (y - xyXY[1]) * n[1]) / pow(n[0] * n[0] + n[1] * n[1], 0.5);
			if (abs(dis) < 5 && (dis < minDelta || minDelta == -1)) {
				minDelta = abs(dis);
				s = &(markerSegment.getValue().value);
			}
			markerSegment.next();
		}
		Pair<Point*, Segment*> pair(p,s);
		return pair;
	}

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

#endif
