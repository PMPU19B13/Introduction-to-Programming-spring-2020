#include <iostream>

#include "storage.h"
#include "list.h"
#include "pair.h"

bool testStorage() {
	Storage<List<Pair<double, int>>> ht;
	List<Pair<double, int>> l;
	l.add(Pair<double, int>(1.1, 1));
	l.add(Pair<double, int>(2.2, 2));
	ht.add(l);
	List<Pair<double, int>> l1 = ht[0];
	
	if (ht.size() != 1)  return false;

	return true;
}

bool stestMarker() {
	Storage<List<Pair<double, int>>> st;//массив списков
	List<Pair<double, int>> l;//первый список
	l.add(Pair<double, int>(1.1, 1));
	l.add(Pair<double, int>(2.2, 2));
	st.add(l);//добавляем первый список в массив
	List<Pair<double, int>> l2;//второй список
	l2.add(Pair<double, int>(3.3, 3));
	l2.add(Pair<double, int>(4.4, 4));
	st.add(l2);//добавляем второй список в массив

	//проверяем маркер
	Storage<List<Pair<double, int>>>::Marker m = st.createMarker();
	std::cout << m.getValue().get(0).value << std::endl;
	m.next();
	std::cout << m.getValue().get(0).value << std::endl;
	return m.isValid();
}

int main() {

	std::cout << "testStorage: " << (testStorage() ? "PASSED" : "FAILED") << std::endl;
	std::cout << "stestMarker: " << (stestMarker() ? "PASSED" : "FAILED") << std::endl;

	return 0;
}