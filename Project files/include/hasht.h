#pragma once

#include "storage.h"
#include "list.h"
#include "pair.h"

template<typename K, typename V>
class HashT
{
public:
	HashT();

	//~HashT();

	void add(const K& key, const V& value);

	bool hasKey(const K& key);

	const V& getAssoc(const K& key);

	size_t size() const;

private:
	size_t m_size;
	Storage<List<Pair<K, V>>> m_storage;
	static size_t hashfun(const K& key);
};


template<typename K, typename V>
HashT<K, V>::HashT()
{
	m_storage = Storage<List<Pair<K, V>>>(1000);
	m_size = 0;
}

template<typename K, typename V>
size_t HashT<K, V>::size() const
{
	return m_size;
}

template<typename K, typename V>
size_t HashT<K, V>::hashfun(const K& key)
{
	size_t hash = 0;
	unsigned char* pc = (unsigned char*) &key;
	for (size_t k = 0; k < sizeof(key); ++k)
		hash += pc[k];
	return hash;
}

template<typename K, typename V>
void HashT<K, V>::add(const K& key, const V& value)
{
	size_t hash_function_value = hashfun(key);
	hash_function_value %= m_storage.size();
	m_storage[hash_function_value].add(Pair<K, V>(key, value));
	++m_size;
}

template<typename K, typename V>
bool HashT<K, V>::hasKey(const K& key)
{
	size_t hash_function_value = hashfun(key);
	hash_function_value %= m_storage.size();

	typename List<Pair<K, V>>::Marker marker;
	marker = m_storage[hash_function_value].createMarker();

	while (marker.isValid())
	{
		if (marker.getValue().key == key)
			return true;
		marker.next();
	}
	return false;
}
