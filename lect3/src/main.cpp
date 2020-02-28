#include <iostream>
#include "storage.h"
#include "geometry.h"

using namespace std;

int main()
{
	Storage<double> storage;
	storage.AddElem(1.1);
	storage.AddElem(2.2);
	storage.AddElem(3);
	storage.AddElem(4);
	storage.AddElem(5);

	Storage<int> intStorage;
	intStorage.AddElem(3);
	intStorage.AddElem(45);

	Storage<Point> pointStorage;
	pointStorage.AddElem(Point(2.3, 4.7));
	pointStorage.AddElem(Point(1.3, 12.3));

	Point p1(2, 45.4);
	Point p2(21.2, 45.1);

	Segment s1(&p1, &p2);

	Point p = s1.getStart();

	cout << "total size: " << storage.TotalSize() << endl;
	cout << (testStorage4() ? "CORRECT" : "FAILURE") << endl;
	return 0;
}
