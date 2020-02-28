#include <iostream>
#include "storage.h"
#include "geometry.h"

using namespace std;

int main()
{

    Storage<double> storage;
    storage.AddElem(4.5);
    cout << storage.TotalSize() << endl;

    Storage<int> intStorage;
    intStorage.AddElem(3);
    cout << intStorage.TotalSize() << endl;

    Storage<Point> pointStorage;
    pointStorage.AddElem(Point(2.3, 4.7));

    return 0;
}
