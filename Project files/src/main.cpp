#include <iostream>
#include <sstream>

#include "storage.h"
#include "mmap.h"
#include "requirement.h"
#include "controller.h"
#include "drawer.h"
#include "error.h"
#include "FileIO.h"
#include "drawer.h"
#include <SFML/Graphics.hpp>
#include "matrix.h"
#include <string>
#include "id.h"
#include "hasht.h"
#include "stack.h"

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
template<typename Fun, typename Arg>
Arg derivative(Fun function, Arg x)
{
	double dx = 1e-5;
	return (function(x + dx) - function(x)) / dx;
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
	double min = 1000000;
	for (int i = low; i < high; i++)
		if (min > derivative(function, i))
		{
			min = derivative(function, i);
		}
	double x0 = -1000, x1;
	x1 = x - function(x) / derivative(function, x);
	while (abs(function(x1) / min) > eps)
	{
		x0 = x1;
		x1 = x0 - function(x0) / derivative(function, x0);
	}
	return x1;
}

void getErr(IRequirement* req)
{
	std::cout << "Error now " << req->error() << std::endl;
}

Segment s;

double verticalError(double x)
{
	Point p1 = s.getStart();
	p1.setX(x);
	Point p2 = s.getEnd();

	//s = Segment(&p1, &p2);

	double err = x - p2.getX();
	return err;
}

class verticalErrorType
{
public:
	verticalErrorType(Segment* segment = nullptr) : m_segment(segment)
	{
	}

	double operator()(double x)
	{
		Point p2 = m_segment->getEnd();
		return x - p2.getX();
	}

private:
	Segment* m_segment;
};

class Totals
{
public:
	Totals(const Storage<verticalErrorType>& s)
	{
		m_vertErrs = s;
	}
	double operator()(double x)
	{
		/*double res = 0;
		Storage<verticalErrorType>::Marker marker = m_vertErrs.createMarker();
		for (; marker.isValid(); marker.next())
		{
			res += marker.getValue()(x);
		}
		return res;
		*/
	}
	
private:
	Storage<verticalErrorType> m_vertErrs;
};
template<typename T>
Storage<T> create() {
	Storage<T> a;
	a.add(-1);
	return a;
}

#include <vector>
using namespace std;
int main()
{
	try{
		Storage<int>a = create<int>();
		a.add(1);
		a.add(2);
		a.add(3);

		Storage<int>b = a;

		for (Storage<int>::iterator i = b.begin();i!=b.end();i++)
			cout << *i << endl;
	
	}
	catch (...)
	{
		std::cout << "Whoops!" << std::endl;
	}

	return 0;
}
