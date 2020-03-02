#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "storage.h"
#include "geometry.h"
#include "ID.h"

enum PrimType
{
    P_Point, P_Segment, P_Circle
};

enum ReqType
{
    R_Distance, R_Paral, R_Eq, R_PonC
};

class Controller
{
    public:
        Controller();
        void addPrimitive(PrimType, Storage<double>);
        void delPrimitive(ID);

        void addRequirement(ReqType, ID, ID, double *param = nullptr);
        void delRequirement(ID);

        void UpdateView() {
            //Drawer drawer;
            //for (points)
            //    drawer.drawPrimitive(point)
        }
    private:
        Storage<Point> m_points;
        Storage<Segment> m_segments;
        Storage<Circle> m_circles;
};

#endif // CONTROLLER_H
