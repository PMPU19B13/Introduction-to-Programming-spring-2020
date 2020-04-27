#pragma once

template<typename T>
class Stack {
public:
	Stack() {
		
	}
	void add(T b) {
		T *c = new T [s+1];
		for (int i = 0; i < s; i++)
			c[i] = a[i];
		c[s] = b;
		delete[] a;
		a = c;
		s++;
	}
	T peek() {
		return a[s - 1];
	}
	T pop() {
		T r = a[s - 1];
		T *c = new T[s-1];
		for (int i = 0; i < s-1; i++)
			c[i] = a[i];
		delete[] a;
		a = c;
		s--;
		return r;
	}
	bool empty() {
		return s == 0;
	}
private:
	T *a;
	size_t s;
};