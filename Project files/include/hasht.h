#pragma once
#include "storage.h"
#include "list.h"
#include "pair.h"

template<typename K, typename V>
class HashT
{
public:
	HashT() 
	{
		m_storage = Storage<List<Pair<K, V>>>(1000);
	}

	//~HashT();

	void add(const K& key, const V& value);
	
	bool hasKey(const K& key);
	
	const V& getAssoc(const K& key);
	
	size_t size()const { return m_size; }

private:
	size_t m_size;
	Storage<List<Pair<K, V>>> m_storage;
	static size_t hashfun(const K& key) {
		size_t hash = 0;
		unsigned char* pc = (unsigned char*)&key;
		for (size_t k = 0; k < sizeof(key); ++k)
			hash += pc[k];
		return hash;		
	}
};


template<typename K, typename V> void HashT<K, V>::add(const K& key, const V& value) {
	size_t hashfunval = hashfun(key);
	hashfunval %= m_storage.size();
	m_storage[hashfunval].add(Pair<K,V>(key, value));
	++m_size;
}


template<typename K, typename V> bool HashT<K, V>::hasKey(const K& key) {
	size_t hashfunval = hashfun(key);
	hashfunval %= m_storage.size();

	typename List<Pair<K, V>>::Marker m;
	List<Pair<K, V>>& li = m_storage[hashfunval];
	m = li.createMarker();
	
	while (m.hasNext()) {
		if (m.getValue().key == key) return true;
		m.next();
	}
	return false;
}