#include <iostream>

#include "storage.h"
#include "mmap.h"
#include "requirement.h"
#include "controller.h"
#include "error.h"

class WithName
{
public:
    virtual const char* getName() const = 0;
};

class Person : public WithName
{
public:
    Person(const char* name, int height) : m_name(name), m_height(height)
    {
    }
    virtual const char* getName() const
    {
        return m_name;
    }
        int getHeight() const
    {
        return m_height;
    }

private:
    const char* m_name;
    int m_height;
};

class Student : public Person
{
public:
    Student() : Person("John", 160)
    {
    }
    int getGroup() const
    {
        return m_group_number;
    }

private:
    int m_group_number;
};

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
template <typename Fun, typename Arg>
Arg derivative(Fun function, Arg x)
{
    double dx = 1e-5;
    return (function(x + dx) - function(x)) / dx;
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

template<typename Fun, typename Arg>
Arg NewtMeth(Fun function, Arg low, Arg high, Arg eps)
{   
        double x = (low + high) / 2; 
        double  min = 1000000;
        for (int i = low; i < high; i++)
                if (min > derivative(function,i))
                {
                      min = derivative(function,i);
                }
        double  x0 = -1000, x1;
	x1 = x - function(x) / derivative(function,x);
        while (abs(function(x1) / min) > eps)
        {
                  x0 = x1;
                        x1 = x0 - function(x0) / derivative(function,x0);
        }
        return(x1);
}


void sayHello(WithName* p)
{
    std::cout << "Hello " << p->getName() << std::endl;
}

void getErr(IRequirement* req)
{
    std::cout << "Error now " << req->error() << std::endl;
}

#include <SFML/Graphics.hpp>
#include "matrix.h"
#include <string>
using namespace std;
int main()
{
	setlocale(LC_ALL, "rus");
	Controller c;

	Storage<double> s;
	s.add(0);
	s.add(0);
	s.add(30);

	c.addPrimitive(P_Circle, s);
	s.add(60);
	c.addPrimitive(P_Segment, s);

	while (c.updateView()) {};//!DON NOT REMOVE!

	return 0;
}
