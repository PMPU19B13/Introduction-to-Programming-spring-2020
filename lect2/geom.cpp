#include <iostream>

using namespace std;

class Error
{
public:
    Error()
    {

    }
};

class Point
{
public:
    double x;
    double y;
    Point(double _x = 0, double _y = 0)
    {
        x = _x;
        y = _y;
        cout << "Point was created" << endl;
    }
};

class Segment
{
private:
    Point *start;
    Point *end;
    //bool valid;

public:
    Segment(Point *st, Point *ed)
    {
        if ((st != nullptr) && (ed != nullptr)) {
            start = st;
            end = ed;
            cout << "Segment was created" << endl;
            //valid = true;
        }
        else {
            cout << "Error" << endl;
            throw(Error());
            //valid = false;
            //exit(1);
        }
    }
    //Segment(double x1 = 0, double y1 = 1, double x2 = 0, double y2 = 1)
    //{
    //    *start = Point(x1, y1);
    //    *end = Point(x2, y2);
    //    cout << "Segment was created" << endl;
    //}

    //bool is_valid()
    //{
    //    return valid;
    //}
};

int main()
{
    Point p1(1, 1);
    Point p2(2, 2);

    try
    {
        Segment s1(&p1, &p2);
        Segment s2(nullptr, &p2);
    }
    catch(double)
    {
        cout << "Double failure" << endl;
    }
    catch(int)
    {
        cout << "Segment creation failure" << endl;
    }
    catch(Error    )
    {
        cout << "ERROR" << endl;
    }
    catch(...)
    {
        cout << "Other failure" << endl;
    }

            //cout << s1.is_valid() << endl;
        //cout << s2.is_valid() << endl;
    return 0;
}
