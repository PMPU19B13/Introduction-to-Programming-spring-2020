#include <iostream>

#define DEBUG

#include "storage.h"
#include "geometry.h"
#include "ID.h"
#include "controller.h"

int main()
{
    try
    {
        Controller c;
        Storage<double> s;
        s.AddElem(0);
        s.AddElem(1);
        c.addPrimitive(P_Point, s);

        Storage<double> d;
        d.AddElem(0);
        d.AddElem(1);
        d.AddElem(4);
        d.AddElem(5);

        c.addPrimitive(P_Segment, d);

        c.updateView();

    } catch (Error)
    {
        
    } catch (BadArg)
    {
        std::cout << "Whoops!" << std::endl;
    }

    /*
    Storage<double> storage;
    storage.AddElem(4.5);
    cout << storage.TotalSize() << endl;

    Storage<int> intStorage;
    intStorage.AddElem(3);
    cout << intStorage.TotalSize() << endl;
    */

    Point p(1.0, 1.0);
    ID idp;

    Point p1(1.1, 1.2);
    ID idp1;

    std::cout << "idp.is_equal(idp1) = " << idp.is_equal(idp1) << std::endl;

    /*
    Storage<Point> pointStorage;
    pointStorage.AddElem(Point(2.3, 4.7));
    */

    return 0;
}
