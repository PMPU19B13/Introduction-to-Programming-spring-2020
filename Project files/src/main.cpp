#include <iostream>

#define DEBUG

#include "storage.h"
#include "geometry.h"
#include "ID.h"
#include "controller.h"

void printContents(Storage<double> s)
{
    for (size_t k = 0; k < s.TotalSize(); ++k)
        std::cout << s.GetElemByNum(k) << std::endl;
}


int main()
{
//    int a = 123456;
//    int &ra = a;
//    int *pa = &a;


//    std::cout << a << std::endl;
//    std::cout << ra << std::endl;
//    std::cout << *pa << std::endl;

    try
    {
        while (true)
        {
            Storage<double> s;
            s.AddElem(0);
            s.AddElem(1);
            printContents(s);
        }
//        Controller c;
//            c.addPrimitive(P_Point, s);

//            s.AddElem(1);
//            s.AddElem(4);
//
        Storage<double> d;
        d.AddElem(0);
        d.AddElem(1);
        d.AddElem(4);
        d.AddElem(5);

        printContents(d);
//            c.addPrimitive(P_Segment, d);
//            c.updateView();

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
