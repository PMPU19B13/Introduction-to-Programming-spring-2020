#include <iostream>

#define DEBUG

#include "storage.h"
#include "geometry.h"
#include "ID.h"
#include "controller.h"

class Rational
{
public:
    Rational(int n = 0, unsigned d = 1) : num(n), den(d)
    {}

    void setNum(int n)
    {
        num = n;
    }

    void setDen(int d)
    {
        if (d == 0)
            throw BadArg();
        den = d;
    }

    int getNum() const
    {
        return num;
    }

    unsigned getDen() const
    {
        return den;
    }

    Rational sum(const Rational &r)
    {
        Rational res;
        res.num = num * r.den + r.num * den;
        res.den = den * r.den;
        return res;
    }


    Rational operator+(const Rational &r)
    {
        Rational res;
        res.num = num * r.den + r.num * den;
        res.den = den * r.den;
        return res;
    }

private:
    int num;
    unsigned den;
};

std::ostream &operator<<(std::ostream &ost, const Rational &r)
{
    ost << r.getNum() << "/" << r.getDen();
    return ost;
}

void printContents(Storage<double> s)
{
    for (size_t k = 0; k < s.TotalSize(); ++k)
    {
        std::cout << s[k] << std::endl;
        s[k] = s[k] + 34.5 + 7.88;
    }
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
        Rational r1;
        r1.setDen(3);
        r1.setNum(23);

        Rational r2;
        r2.setDen(23);
        r2.setNum(3);

        Rational r3 = r1.sum(r2);

        Rational r4 = r1 + r2;
        r4 = r1.operator+(r2);

        std::cout << r4;
        std::cout << std::endl;

        std::cout << r4 << std::endl;
//        operator<<(operator<<(std::cout, r4), std::endl);

        int a = 3, b = 33;

        int c = a + b;
        Storage<double> d;
        Storage<double> f;


//        while (false)
//        {
        if (true)
        {
            Storage<double> s;
            s.AddElem(0);
            s.AddElem(1);
            printContents(s);
            f = d = s;
            f.operator=(d.operator=(s));
        }

        Storage<Storage<double>>

//        }
//        Controller c;
//            c.addPrimitive(P_Point, s);

//            s.AddElem(1);
//            s.AddElem(4);
//
//        d.AddElem(0);
//        d.AddElem(1);
//        d.AddElem(4);
//        d.AddElem(5);

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
