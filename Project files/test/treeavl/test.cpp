#include <iostream>

#include "mmapavl.h"

bool testTreeAvlAdd() {
	MMapAVL<double, int> mmap;
	mmap.add(1.2, 20);
	mmap.add(1.35, 35);
	mmap.add(1.15, 15);
	mmap.add(1.06, 6);
	mmap.add(1.43, 43);

	if ( mmap.size() != 5 )  return false;
	
	return true;
}

bool testTreeAvlMarker() {
	MMapAVL<double, int> mmap;
	mmap.add(1.2, 20);
	mmap.add(1.35, 35);
	mmap.add(1.15, 15);
	mmap.add(1.06, 6);
	mmap.add(1.43, 43);
	
	if ( mmap.size() != 5 )  return false;

	MMapAVL<double, int>::Marker marker = mmap.createMarker();
	if (!marker.isValid()) return false;
	size_t count = 1;
	Pair<double, int> v = marker.getValue();
	while (true) {
		if (marker.hasNext(mmap)) {
			std::cout << v.value << ' ';
			marker.next(mmap);
			++count;

			Pair<double, int> vnext = marker.getValue();
			if (vnext < v) return false;
			v = vnext;
		}
		else
			break;
	}
	std::cout << v.value << std::endl;
	if ( count != mmap.size()  ) return false;

	//удаление узла без потомков
	marker.remove(mmap);

	marker = mmap.createMarker();
	count = 1;
	v = marker.getValue();
	/*while (true) {
		if (marker.hasNext(mmap)) {
			std::cout << v.value << ' ';
			marker.next(mmap);
			++count;

			Pair<double, int> vnext = marker.getValue();
			if (vnext < v) return false;
			v = vnext;
		}
		else
			break;
	}
	std::cout << v.value << std::endl;
	if (count != mmap.size()) return false;
	mmap.add(1.43, 43);

	//удаление промежуточного узла
	marker = mmap.createMarker();
	//marker.next(mmap);
	marker.next(mmap);
	marker.remove(mmap);
	marker = mmap.createMarker();
	count = 1;
	v = marker.getValue();
	while (true) {
		if (marker.hasNext(mmap)) {
			std::cout << v.value << ' ';
			marker.next(mmap);
			++count;

			Pair<double, int> vnext = marker.getValue();
			if (vnext < v) return false;
			v = vnext;
		}
		else
			break;
	}
	std::cout << v.value << std::endl;
	if (count != mmap.size()) return false;
	mmap.add(1.15, 15);

	//удаление промежуточного узла
	marker = mmap.createMarker();
	marker.next(mmap);
	marker.next(mmap);
	marker.next(mmap);
	marker.remove(mmap);
	marker = mmap.createMarker();
	count = 1;
	v = marker.getValue();
	while (true) {
		if (marker.hasNext(mmap)) {
			std::cout << v.value << ' ';
			marker.next(mmap);
			++count;

			Pair<double, int> vnext = marker.getValue();
			if (vnext < v) return false;
			v = vnext;
		}
		else
			break;
	}
	std::cout << v.value << std::endl;
	if (count != mmap.size()) return false;
	mmap.add(1.35, 35);
	*/
	//удаление корневого узла
	marker = mmap.createMarker();
	marker.next(mmap);
	marker.next(mmap);
	marker.remove(mmap);
	marker = mmap.createMarker();
	count = 1;
	v = marker.getValue();
	while (true) {
		if (marker.hasNext(mmap)) {
			std::cout << v.value << ' ';
			marker.next(mmap);
			++count;

			Pair<double, int> vnext = marker.getValue();
			if (vnext < v) return false;
			v = vnext;
		}
		else
			break;
	}
	std::cout << v.value << std::endl;
	if (count != mmap.size()) return false;
	mmap.add(1.2, 20);


	marker = mmap.createMarker();
	count = 1;
	v = marker.getValue();
	while (true) {
		if (marker.hasNext(mmap)) {
			std::cout << v.value << ' ';
			marker.next(mmap);
			++count;

			Pair<double, int> vnext = marker.getValue();
			if (vnext < v) return false;
			v = vnext;
		}
		else
			break;
	}
	std::cout << v.value << std::endl;
	if (count != mmap.size()) return false;
	return true;
}

 
int main() {
	std::cout << "testTreeAvlAdd() " << (testTreeAvlAdd() ? "PASSED" : "FAILED") << std::endl;
	std::cout << "testTreeAvlMarker() " << (testTreeAvlMarker() ? "PASSED" : "FAILED") << std::endl;

	return 0;
}