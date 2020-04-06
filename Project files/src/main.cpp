#include <iostream>

#include "storage.h"
#include "mmap.h"
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

template<typename Fun, typename Arg>
Arg findZero(Fun function, Arg low, Arg high, Arg eps)
{
    Arg lowValue = function(low);
    Arg highValue = function(high);
    if (highValue * lowValue < 0)
    {
        Arg mid = (high + low) / 2;
        Arg midValue = function(mid);
        while (std::abs(midValue) > eps)
        {
            if (lowValue * midValue > 0)
            {
                lowValue = midValue;
                low = mid;
            }
            else
            {
                highValue = midValue;
                high = mid;
            }
            mid = (high + low) / 2;
            midValue = function(mid);
        }
        return mid;
    }
    throw Error();
}

template<typename T>
T func1(T x)
{
    return (x - 3) * x * (x - 2);
}

// Функция для вычисления производной в точке
template<typename F>
F derivative(F x)
{
    double dx = 1e-10;
    return (func1(x + dx) - func1(x)) / dx;
}

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

Segment s;

double vertError(double x){
     Point p1 = s.getStart();
     p1.setX(x);
     Point p2 = s.getEnd();

     //s = Segment(&p1,&p2);

     double err = x - p2.getX();
     return err;
}

class vertErrorType{
public:
   vertErrorType(Segment *s){
      m_s = s;
   }
   double operator()(double x){
      Point p2 = m_s->getEnd();
      return x - p2.getX();
   }

private:
   Segment *m_s;
};

class Totals{

public:
   Totals(  const Storage<vertErrorType*> & s){
      m_vertErrs = s;
   }
   double operator()(double x){
      double res = 0;
      return res;
   }
private:
   Storage<vertErrorType*> m_vertErrs;
};


int main()
{
    try
    {
       double x1 = 0, y1 = 0, x2 = 1, y2 =1 ;

       Point a1;
       a1.setX(x1);
       a1.setY(y1);
       Point a2;
       a2.setX(x2);
       a2.setY(y2);
       Point a3;
       a3.setX(6);
       a3.setY(6);


       s = Segment(&a1,&a2);


       Segment s2(&a1,&a2);

       vertErrorType vt(&s2);

       Segment s3(&a2,&a3);

       vertErrorType vt1(&s3);


       Storage<vertErrorType*> s;
       s.add(&vt);
       s.add(&vt1);

       Totals tot(s);
       double res = findZero(tot, -2.0, 2.0, 0.00001);









       //double res = findZero(vertError, -2.0, 2.0, 0.00001);
       res = findZero(vt, -2.0, 2.0, 0.00001);

       std::cout << "res = " << res << "vt1(res) = " << vt1(res) << std::endl;

       std::cout << res << std::endl;

       a1.setX(res);

       res = findZero(vt1, -2.0, 20.0, 0.00001);
       a2.setX(res);

       std::cout << vt1(1) << std::endl;









        std::cout << findZero(func1<double>, -1.0, 1.0, 0.00001) << std::endl;
        std::cout << findZero(func1<double>, 1.0, 2.5, 0.0000001) << std::endl;
        std::cout << derivative(6.0) << std::endl;
        MMap<int, double> mmap;
     
        mmap.add(2, 2.2);
        mmap.add(3, 2.2);
        mmap.add(1, 2.2);
        mmap.add(4, 2.2);

//        mmap.add();

//        Controller controller;
//
//        Storage<double> pointParams;
//        Storage<double> segmentParams;
//        Storage<double> circleParams;
//
//        pointParams.add(1.2);
//        pointParams.add(14.7);
//
//        segmentParams.add(1.6);
//        segmentParams.add(3.2);
//        segmentParams.add(6.4);
//        segmentParams.add(0.8);
//
//        circleParams.add(0);
//        circleParams.add(0);
//        circleParams.add(5.5);
//
//        controller.addPrimitive(P_Point, pointParams);
//        controller.addPrimitive(P_Segment, segmentParams);
//        controller.addPrimitive(P_Circle, circleParams);
//
//        controller.updateView();

    } catch (...)
    {
        std::cout << "Whoops!" << std::endl;
    }

    return 0;
}
