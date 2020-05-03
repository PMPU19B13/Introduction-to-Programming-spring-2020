#include <iostream>
#include <vector>
#include <list>
#include <map>//обычно на красно-чёрных деревьях
#include <unordered_map>
#include <set>//множество
#include <unordered_set>


bool testMMap() {
	std::multimap<double, int> assoc;//multimap - разрешено повторение ключей
	assoc.insert(std::make_pair(1.2, 3));
	assoc.insert(std::make_pair(1.2, 4));
	assoc.insert(std::make_pair(1.2, 5));

	assoc.insert(std::make_pair(3.1, 33));
	assoc.insert(std::make_pair(3.1, 44));

	std::multimap<double, int>::iterator it = assoc.lower_bound(1.2);
	std::multimap<double, int>::iterator ite = assoc.upper_bound(1.2);
	std::pair<std::multimap<double, int>::iterator, std::multimap<double, int>::iterator> range = assoc.equal_range(1.2);

	for (; it != ite; ++it) {
		std::cout << (*it).first << ' ' << (*it).second << std::endl;
	}
	return true;
}

bool testStdMap() {
	std::map <double, int> assoc;
	assoc[1.2] = 2;
	assoc[3.5] = 4;
	assoc[4.77] = 77;
	int v = assoc[1.2];
	std::cout << v << std::endl;
	std::cout << assoc[1.3] << std::endl;

	for (std::map<double, int>::iterator it = assoc.begin(); it != assoc.end(); ++it) {
		std::cout << (*it).first << (*it).second << std::endl;
	}

	std::map<double, int>::iterator it = assoc.find(1.2);

	std::cout << (it == assoc.end()) << std::endl;

	return true;
}

bool testStd() {
	std::vector<double> vd;
	std::list<double> lt;

	vd.push_back(2);
	vd.push_back(3);
	vd.push_back(1);

	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(1);

	std::cout << vd.front() << std::endl;
	std::cout << vd.back() << std::endl;

	std::cout << lt.front() << std::endl;
	std::cout << lt.back() << std::endl;

	//vd.clear();
	//lt.clear();

	for (std::vector<double>::iterator it = vd.begin(); it != vd.end(); ++it)
	{
		std::cout << *it << std::endl;
	}

	for (auto a : vd) {
		std::cout << a << std::endl;
	}

	for (std::list<double>::iterator it = lt.begin(); it != lt.end(); ++it)
	{
		std::cout << *it << std::endl;
	}

	for (auto a : lt) {
		std::cout << a << std::endl;
	}

	//в обратном порядке
	for (std::vector<double>::reverse_iterator rit = vd.rbegin(); rit != vd.rend(); ++rit) {
		std::cout << *rit << std::endl;
	}

	for (std::list<double>::reverse_iterator rit = lt.rbegin(); rit != lt.rend(); ++rit) {
		std::cout << *rit << std::endl;
	}

	if (vd.size() == 3 && lt.size() == 3) return true;
}

int main() {
	std::cout << (testStd() ? "passed" : "failed") << std::endl;
	std::cout << (testStdMap() ? "passed" : "failed") << std::endl;
	std::cout << (testMMap() ? "passed" : "failed") << std::endl;

	return 0;
}