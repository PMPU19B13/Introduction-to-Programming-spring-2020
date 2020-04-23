#include <iostream>

#include "hasht.h"
#include "id.h"

bool testHashT() {
	HashT<ID, int> ht;
	ID id1 = ID();
	ID id2 = ID();
	ID id3 = ID();
	ht.add(id1, 1);
	ht.add(id2, 2);
	ht.add(id3, 3);
	std::cout << ht.getAssoc(id1) << std::endl;
	std::cout << ht.getAssoc(id2) << std::endl;
	std::cout << ht.getAssoc(id3) << std::endl;

	if (ht.size() != 3)  return false;

	return true;
}

bool testMarker() {
	HashT<ID, int> ht;
	ID id1 = ID();
	ID id2 = ID();
	ID id3 = ID();
	ht.add(id1, 1);
	ht.add(id2, 2);
	ht.add(id3, 3);
	HashT<ID, int>::Marker m = ht.createMarker();
	//std::cout << m.getValue().get(0).value << std::endl;
	return m.isValid();
}

int main() {

	std::cout << "testHashT: " << (testHashT() ? "PASSED" : "FAILED") << std::endl;
	std::cout << "testMarker: " << (testMarker() ? "PASSED" : "FAILED") << std::endl;
	
	return 0;
}