#include <iostream>

#define DEBUG

#include "storage.h"
#include "geometry.h"
#include "ID.h"


int main()
{
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
