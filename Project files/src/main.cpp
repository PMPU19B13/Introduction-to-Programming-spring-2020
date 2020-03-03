#include <iostream>

#include "storage.h"
#include "geometry.h"
#include "id.h"
#include "controller.h"

int main()
{
    try
    {
        Controller c;
        Storage<double> s;
        s.add(0);
        // s.add(1);
        c.addPrimitive(P_Point, s);

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
    intStorage.add(3);
    cout << intStorage.size() << endl;
    */

    Point p(1.0, 1.0);
    ID idp;

    Point p1(1.1, 1.2);
    ID idp1;

    std::cout << "idp.is_equal(idp1) = " << idp.equals(idp1) << std::endl;

    /*
    Storage<Point> pointStorage;
    pointStorage.add(Point(2.3, 4.7));
    */

    return 0;
}
