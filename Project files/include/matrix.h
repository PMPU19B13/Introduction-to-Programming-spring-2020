#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "error.h"

//методы преобразования массив <-> вектор
///////////////////////////////////////////////////////////////////////////////////////////////////
//вектор -> массив
//int* a = vtoa(vector<int> b) - псевдопример
template<typename T>
T* vtoa(std::vector<T> a);
template<typename T>
T** vtoa(std::vector<std::vector<T>> a);

//массив -> вектор
template<typename T, size_t N>
std::vector<T> atov(T(& a)[N]);
template<typename T, size_t N, size_t M>
std::vector<std::vector<T>> atov(T(& a)[N][M]);
///////////////////////////////////////////////////////////////////////////////////////////////////
/*
Класс Матрица:
Мaтрицу можно инициализировать: массивом, вектором, нулями (размером width x height).
Над матрицами можно выполнять операции: + - * как с другими матрицами так и с числами.
А также transpose(), det(), algAd(i,j)(по сути вычеркнутая строка и столбец i j), inverse().
+ плюшка: вывод с <<
****************************************Example****************************************************
int a[2][2] = {{1,2},{2,3}};
vector<vector<int>> b{{ 1,2,5 },{ 4,6,0 }};
int c[3][2] = {{1,2},{1,2},{1,2}};
Matrix<int> A(a);
Matrix<int> B(b);
Matrix<int> C(c);
cout << (B*C+A*2).det();
*/
template<class T>
class Matrix
{
private:
	T** matrix;
	size_t width, height;//размеры матрицы
public:
	template<size_t N, size_t M>
	Matrix(T(& m)[N][M]);// инициализация массивом

	Matrix(std::vector<std::vector<T>> m);// инициализация вектором

	Matrix(size_t w, size_t h);//инициализация нулями по размеру w x h

	Matrix(const Matrix& b);//копирка

	Matrix& operator=(const Matrix& b);

	Matrix operator+(const Matrix& b);
	Matrix operator+(double a);

	Matrix operator-(const Matrix& b);
	Matrix operator-(double a);

	Matrix operator*(const Matrix& b);
	Matrix operator*(double a);

	Matrix algAd(size_t y, size_t x);//алгоритмическое дополнение по y x

	T det();//определитель

	template<typename S>
	friend std::ostream& operator<<(std::ostream& out, const Matrix<S>& m);

	Matrix transpose();//транспонирование

	Matrix inverse();//обратная матрица

	~Matrix();
};

template<class T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& m);//вывод

///////////////////////////////////WARNING!METHODS_ARE_HERE!////////////////////////////////////////
template<typename T>
T* vtoa(std::vector<T> a)
{
	T* b = new T[a.size()];
	for (size_t i = 0; i < a.size(); i++)
		b[i] = a[i];
	return b;
}

template<typename T>
T** vtoa(std::vector<std::vector<T>> a)
{
	T** b = new T* [a.size()];
	for (size_t i = 0; i < a.size(); i++)
		b[i] = vtoa(a[i]);
	return b;
}

//массив -> вектор
template<typename T, size_t N>
std::vector<T> atov(T(& a)[N])
{
	std::vector<T> b;
	for (size_t i = 0; i < N; i++)
		b.push_back(a[i]);
	return b;
}

template<typename T, size_t N, size_t M>
std::vector<std::vector<T>> atov(T(& a)[N][M])
{
	std::vector<std::vector<T>> b;
	for (size_t i = 0; i < N; i++)
		b.push_back(atov(a[i]));
	return b;
}

template<class T>
template<size_t N, size_t M>
Matrix<T>::Matrix(T(& m)[N][M])
{
	matrix = new T* [N];
	for (int i = 0; i < N; i++)
	{
		matrix[i] = new T[M];
		for (int j = 0; j < M; j++)
			matrix[i][j] = m[i][j];
	}

	height = sizeof(m) / sizeof(m[0]);
	width = sizeof(m[0]) / sizeof(T);
};

template<class T>
Matrix<T>::Matrix(std::vector<std::vector<T>> m)
{
	matrix = vtoa(m);
	height = m.size();
	width = m[0].size();
};

template<class T>
Matrix<T>::Matrix(size_t w, size_t h)
{
	matrix = new T* [h];
	for (int i = 0; i < h; i++)
	{
		matrix[i] = new T[w];
		for (int j = 0; j < w; j++)
			matrix[i][j] = 0;
	}
	this->height = h;
	this->width = w;
};

template<class T>
Matrix<T>::Matrix(const Matrix& b)
{
	matrix = new T* [b.height];
	for (int i = 0; i < b.height; i++)
	{
		matrix[i] = new T[b.width];
		for (int j = 0; j < b.width; j++)
			matrix[i][j] = b.matrix[i][j];
	}
	width = b.width;
	height = b.height;
}

template<class T>
Matrix<T>& Matrix<T>::operator=(const Matrix& b)
{
	if (this == &b)
	{
		return *this;
	}
	for (int i = 0; i < height; i++)
		delete[] matrix[i];
	delete[]matrix;

	matrix = new T* [b.height];
	for (int i = 0; i < b.height; i++)
	{
		matrix[i] = new T[b.width];
		for (int j = 0; j < b.width; j++)
			matrix[i][j] = b.matrix[i][j];
	}
	width = b.width;
	height = b.height;
	return *this;
}

template<class T>
Matrix<T> Matrix<T>::operator+(const Matrix& b)
{
	//ПРОВЕРКА НА ОДИНАКОВЫЕ РАЗМЕРЫ
	if (width != b.width || height != b.height)
		throw BadArgument();
	Matrix r(width, height);
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			r.matrix[i][j] = matrix[i][j] + b.matrix[i][j];
	return r;
}

template<class T>
Matrix<T> Matrix<T>::operator+(double a)
{
	Matrix r(width, height);
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			matrix[i][j] += a;
	return r;
}

template<class T>
Matrix<T> Matrix<T>::operator-(const Matrix& b)
{
	if (width != b.width || height != b.height)
		throw BadArgument();
	Matrix r(width, height);
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			r.matrix[i][j] = matrix[i][j] - b.matrix[i][j];
	return r;
}

template<class T>
Matrix<T> Matrix<T>::operator-(double a)
{
	Matrix r(width, height);
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			matrix[i][j] -= a;
	return *this;
}

template<class T>
Matrix<T> Matrix<T>::operator*(const Matrix& b)
{
	//ПРОВЕРКА НА ВОЗМОЖНОСТЬ УМНОЖЕНИЯ
	if (width != b.height)
		throw BadArgument();

	Matrix r(b.width, height);
	for (size_t i = 0; i < height; i++)
		for (size_t j = 0; j < b.width; j++)
			for (size_t k = 0; k < b.height; k++)
				r.matrix[i][j] += matrix[i][k] * b.matrix[k][j];

	return r;
}

template<class T>
Matrix<T> Matrix<T>::operator*(double a)
{
	Matrix r(width, height);
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			r.matrix[i][j] = matrix[i][j] * a;
	return r;
}

template<class T>
Matrix<T> Matrix<T>::algAd(size_t y, size_t x)
{
	Matrix r(width - 1, height - 1);
	bool I = false;
	bool J = false;
	for (int i = 0; i < height; i++)
	{
		J = false;
		if (i == y)
		{
			I = true;
			continue;
		}
		for (int j = 0; j < width; j++)
		{
			if (j == x)
			{
				J = true;
				continue;
			}
			r.matrix[((I) ? -1 : 0) + i][((J) ? -1 : 0) + j] = matrix[i][j];
		}
	}
	return r;
}

template<class T>
T Matrix<T>::det()
{
	if (width != height)
	{
		throw BadArgument();
		return NULL;
	}
	if (width == 1)
		return matrix[0][0];
	if (width == 2)
		return matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
	else
	{
		T r = 0;
		for (size_t i = 0; i < width; i++)
			r += pow(-1, i) * algAd(0, i).det() * matrix[0][i];
		return r;
	}
}

template<class T>
Matrix<T> Matrix<T>::transpose()
{
	for (int i = 0; i < height; i++)
		for (int j = i; j < width; j++)
			std::swap(matrix[i][j], matrix[j][i]);
	return *this;
}

template<class T>
Matrix<T> Matrix<T>::inverse()
{
	Matrix r(width, height);
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			r.matrix[i][j] = pow(-1, i + j) * algAd(i, j).det();
	r.transpose();
	return r * (1.0 / det());
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& m)
{
	for (size_t i = 0; i < m.height; i++)
	{
		for (size_t j = 0; j < m.width; j++)
		{
			out << m.matrix[i][j] << ' ';
		}
		out << std::endl;
	}
	return out;
}

template<class T>
Matrix<T>::~Matrix()
{
	for (int i = 0; i < height; i++)
		delete[] matrix[i];
	delete[]matrix;
}

//методы вывода
/////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
void show(std::vector<std::vector<T>> a)
{
	for (size_t i = 0; i < a.size(); i++)
	{
		for (size_t j = 0; j < a.size(); j++)
		{
			std::cout << a[i][j] << ' ';
		}
		std::cout << std::endl;
	}
}

template<typename T>
void show(std::vector<T> a)
{
	for (size_t i = 0; i < a.size(); i++)
	{
		std::cout << a[i] << ' ';
	}
	std::cout << std::endl;
}
/////////////////////////////////////////////////////////////////////////////////////////
