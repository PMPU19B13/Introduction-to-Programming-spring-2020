#include <iostream>

#include "storage.h"
#include "mmap.h"
#include "requirement.h"
#include "controller.h"
#include "error.h"
#include "FileIO.h"

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

class Street : public WithName
{
public:
	Street(const char* Sname = "Botanicheskaya") : m_Sname(Sname)
	{
	}

	virtual const char* getName() const
	{
		return m_Sname;
	}

private:
	const char* m_Sname;
	int m_numHouse;
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
template<typename Fun, typename Arg>
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

void sayHello(WithName* p)
{
	std::cout << "Hello " << p->getName() << std::endl;
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
		double res = 0;
		Storage<verticalErrorType>::Marker marker = m_vertErrs.createMarker();
		for (; marker.hasNext(); marker.next())
		{
			res += marker.getValue()(x);
		}
		return res;
	}
	
private:
	Storage<verticalErrorType> m_vertErrs;
};

int main()
{
	try
	{
		double x1 = 0, y1 = 0, x2 = 1, y2 = 1, x3 = 6, y3 = 6;
		Point a1;
		a1.setX(x1);
		a1.setY(y1);
		Point a2;
		a2.setX(x2);
		a2.setY(y2);
		Point a3;
		a3.setX(x3);
		a3.setY(y3);

		Segment s2(&a1, &a2);
		verticalErrorType vt(&s2);

		Segment s3(&a2, &a3);
		verticalErrorType vt1(&s3);

		Storage<verticalErrorType> stor;
		stor.add(vt);
		stor.add(vt1);
		Totals tot(stor);
		double reztot = findZero(tot, -2.0, 10.0, 0.00001);
		std::cout << "reztot = " << reztot << std::endl;

		//double res =  findZero(vertError, -2.0, 2.0, 0.00001);
		double res = findZero(vt, -2.0, 2.0, 0.00001);
		std::cout << "res = " << res << std::endl;
		a1.setX(res);

		res = findZero(vt1, -2.0, 20.0, 0.00001);
		a2.setX(res);
		std::cout << "res = " << res << std::endl;


		Person p("Mary", 163);
		Student stu;
		Street st;
		sayHello(&p);
		sayHello(&stu);
		sayHello(&st);

		std::cout << "Student's name is " << stu.getName() << std::endl;
		std::cout << "Student's height is " << stu.getHeight() << std::endl;

		Point p1, p2(1, 1), p3(1, 0), p4(2, 1);
		Segment se(&p3, &p4);
		HorizontalRequirement hr(&se);
		PointOnSegmentRequirement pos(&p1, &se);

		std::cout << hr.error() << std::endl;
		std::cout << pos.error() << std::endl;

		/*
		IRequirement* ptrreq = (IRequirement*)&hr;
		std::cout << ptrreq->error() << std::endl;
		ptrreq = (IRequirement*)&pos;
		std::cout << ptrreq->error() << std::endl;
		*/

		getErr((IRequirement*)&hr);
		getErr((IRequirement*)&pos);

		std::cout << findZero(func1<double>, -1.0, 1.0, 0.00001) << std::endl;
		std::cout << findZero(func1<double>, 1.0, 2.5, 0.0000001) << std::endl;
		std::cout << derivative(func1<double>, 8.0) << std::endl;
		std::cout << NewtMeth(func1<double>, 1.5, 2.5, 0.0000001) << std::endl;
		MMap<int, double> mmap;
		//	mmap.add();

		//	Controller controller;
		//
		//	Storage<double> pointParams;
		//	Storage<double> segmentParams;
		//	Storage<double> circleParams;
		//
		//	pointParams.add(1.2);
		//	pointParams.add(14.7);
		//
		//	segmentParams.add(1.6);
		//	segmentParams.add(3.2);
		//	segmentParams.add(6.4);
		//	segmentParams.add(0.8);
		//
		//	circleParams.add(0);
		//	circleParams.add(0);
		//	circleParams.add(5.5);
		//
		//	controller.addPrimitive(P_Point, pointParams);
		//	controller.addPrimitive(P_Segment, segmentParams);
		//	controller.addPrimitive(P_Circle, circleParams);
		//
		//	controller.updateView();

	}
	catch (...)
	{
		std::cout << "Whoops!" << std::endl;
	}

	return 0;
}
