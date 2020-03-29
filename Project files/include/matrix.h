#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;


//вектор -> массив
//int* a = vtoi(vector<int> b) - псевдопример
template<typename T>
T* vtoa(vector<T> a) {
	T* b = new T[a.size()];
	for (size_t i = 0; i < a.size(); i++)
		b[i] = a[i];
	return b;
}
template<typename T>
T** vtoa(vector<vector<T>> a) {
	T** b = new T * [a.size()];
	for (size_t i = 0; i < a.size(); i++)
		b[i] = vtoa(a[i]);
	return b;
}

//массив -> вектор
template<typename T, size_t N>
vector<T> atov(T(&a)[N]) {//массив, его размер
	vector<T>b;
	for (size_t i = 0; i < N; i++)
		b.push_back(a[i]);
	return b;
}
template<typename T, size_t N, size_t M>
vector<vector<T>> atov(T(&a)[N][M]) {
	vector<vector<T>> b;
	for (size_t i = 0; i < N; i++)
		b.push_back(atov(a[i]));
	return b;
}

template<class T>
class Matrix {
public:
	T** mx;
	size_t w, h;
	
	//массивом
	template<size_t N, size_t M>
	Matrix(T(&m)[N][M]) {
		mx = new T * [N];
		for (int i = 0; i < N; i++)
			mx[i] = m[i];
		h = sizeof(m) / sizeof(m[0]);
		w = sizeof(m[0]) / sizeof(T);
	};
	//вектором
	Matrix(vector<vector<T>> m) {
		mx = vtoa(m);
		h = m.size();
		w = m[0].size();
	};
	//нулями по размеру w x h
	Matrix(size_t w, size_t h) {
		mx = new T*[h];
		for (int i = 0; i < h; i++) {
			mx[i] = new T[w];
			for (int j = 0; j < h; j++)
				mx[i][j] = 0;
		}
		this->h = h;
		this->w = w;
	};
	
	Matrix& operator= (const Matrix& b) {
		if (this == &b) {
			return *this;
		}
		for (int i = 0; i < h; i++)
			delete[] mx[i];
		delete[]mx;

		mx = new T * [h];
		for (int i = 0; i < h; i++) {
			mx[i] = new T[w];
			for (int j = 0; j < h; j++)
				mx[i][j] = b.mx[i][j];
		}
		w = b.w;
		h = b.h;
		return *this;
	}

	Matrix operator +(const Matrix& b) {
		Matrix r(w, h);
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
				r.mx[i][j] = mx[i][j] + b.mx[i][j];
		return r;
	}
	Matrix operator +(float a) {
		Matrix r(w, h);
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
				mx[i][j] += a;
		return *this;
	}

	Matrix operator -(const Matrix& b){
		Matrix r(w, h);
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
				r.mx[i][j] = mx[i][j] - b.mx[i][j];
		return r;
	}
	Matrix operator -(float a) {
		Matrix r(w, h);
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
				mx[i][j]-=a;
		return *this;
	}

	
	Matrix operator *(const Matrix &b) {
	
		if (w != b.h)
			throw BadArgument();

		vector<vector<T>> r;
		for (size_t i = 0; i < w; i++) {
			vector<T> line;
			for (size_t j = 0; j < b.w; j++) {
				T num = 0;
				for (size_t k = 0; k < b.h; k++)
					num += mx[i][k] * b.mx[k][j];
				line.push_back(num);
			}
			r.push_back(line);
		}
		return r;
	}
	Matrix operator *(float a) {
		Matrix r(w, h);
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
				mx[i][j] *= a;
		return *this;
	}

	//алгоритмическое дополнение по y x
	Matrix algAd(size_t y, size_t x) {
		Matrix r(w-1, h-1);
		bool I = false;
		bool J = false;
		for (int i = 0; i < h; i++) {
			J = false;
			if (i == y) {
				I = true;
				continue;
			}
			for (int j = 0; j < w; j++) {
				if (j == x) {
					J = true;
					continue;
				}
				r.mx[((I) ? -1 : 0) + i][((J) ? -1 : 0) + j] = mx[i][j];
			}
		}
		return r;
	}

	T det (){
		if (w != h) {
			throw BadArgument();
			return NULL;
		}
		if (w == 1)
			return mx[0][0];
		if (w == 2)
			return mx[0][0] * mx[1][1] - mx[1][0] * mx[0][1];
		else {
			T r=0;
			for (size_t i = 0; i < w; i++)
				r += pow(-1, i) * algAd(0, i).det() * mx[0][i];
			return r;
		}
	}

	Matrix transpose() {
		for (int i = 0; i < h; i++)
			for (int j = i; j < w; j++)
				swap(mx[i][j], mx[j][i]);
		return *this;
	}

	Matrix inverse() {
		Matrix r(w, h);
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
				r.mx[i][j] = algAd(i, j).det();
		r.transpose();
		return r * (1.0 / det());
	}
	
	//вывод
	friend std::ostream& operator<< (std::ostream& out, const Matrix& m){
		for (size_t i = 0; i < m.h; i++) {
			for (size_t j = 0; j < m.w; j++) {
				out << m.mx[i][j] << ' ';
			}
			out << endl;
		}
		return out;
	}

	~Matrix () {
		for (int i = 0; i < h; i++)
			delete[] mx[i];
		delete[]mx;
	}
};


template<typename T>
void show(vector<vector<T>> a) {
	for (size_t i = 0; i < a.size(); i++) {
		for (size_t j = 0; j < a.size(); j++) {
			cout << a[i][j] << ' ';
		}
		cout << endl;
	}
}

template<typename T>
void show(vector<T> a) {
	for (size_t i = 0; i < a.size(); i++) {
		cout << a[i] << ' ';
	}
	cout << endl;
}
