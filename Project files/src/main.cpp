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

/*int main() {
	return 0;
}*/