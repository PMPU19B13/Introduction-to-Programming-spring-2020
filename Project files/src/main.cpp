#include <iostream>

#include "storage.h"
#include "controller.h"
#include "error.h"

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
            throw BadArgument();
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

    Rational sum(const Rational& r)
    {
        Rational res;
        res.num = num * r.den + r.num * den;
        res.den = den * r.den;
        return res;
    }


    Rational operator+(const Rational& r)
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

std::ostream& operator<<(std::ostream& ost, const Rational& r)
{
    ost << r.getNum() << "/" << r.getDen();
    return ost;
}

void printContents(Storage<double> s)
{
    for (size_t k = 0; k < s.size(); ++k)
    {
        std::cout << s[k] << std::endl;
        s[k] = s[k] + 34.5 + 7.88;
    }
}


int main()
{
    try
    {
        Controller controller;

        Storage<double> pointParams;
        Storage<double> segmentParams;
        Storage<double> circleParams;

        pointParams.add(1.2);
        pointParams.add(14.7);

        segmentParams.add(1.6);
        segmentParams.add(3.2);
        segmentParams.add(6.4);
        segmentParams.add(0.8);

        circleParams.add(0);
        circleParams.add(0);
        circleParams.add(5.5);

        controller.addPrimitive(P_Point, pointParams);
        controller.addPrimitive(P_Segment, segmentParams);
        controller.addPrimitive(P_Circle, circleParams);

        controller.updateView();

    } catch (...)
    {
        std::cout << "Whoops!" << std::endl;
    }

    return 0;
}
