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

	class Marker
	{
	public:

		bool hasNext() const
		{
			// Арифметика через указатели
			return m_marker < m_storage_mark->m_data + m_storage_mark->m_size - 1;
		}

		void next()
		{
			if (hasNext())
				++m_marker;
		}

		List<Pair<K, V>>& getValue()
		{
			// Арифметика через указатели
			if (m_marker >= m_storage_mark->m_data + m_storage_mark->m_size)
				throw Error();

			return *m_marker;
		}

		void remove()
		{
			// Арифметика через указатели
			m_storage_mark->remove(m_marker - m_storage_mark->m_data);
			valid = false;
		}

		bool isValid()
		{
			return valid;
		}

		friend class HashT;

	private:
		bool valid;
		List<Pair<K, V>>* m_marker;
		HashT<K, V>* m_storage_mark;
	};
	 
	Marker createMarker();

private:
	size_t m_size;
	Storage<List<Pair<K, V>>> m_storage;
	//List<Pair<K, V>>* m_data;
	static size_t hashfun(const K& key);
};

template<typename K, typename V>
typename HashT<K,V>::Marker HashT<K, V>::createMarker()
{
	HashT<K, V>::Marker m;
	m.m_marker = &m_storage[0];
	m.m_storage_mark = this;
	m.valid = true;
	return m;
}


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
	double A = 0.6180339887;
	//int N = 1024;
	/*int* p = (int*) &key;
	int hash = N * (*p * A - int(*p * A));
	return hash;*/

	size_t hash = 0;
	unsigned char* pc = (unsigned char*)&key;
	for (size_t k = 0; k < sizeof(key); ++k)
		hash += pc[k] * pow(A, k);
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

template <typename K, typename V>
const V& HashT<K, V>::getAssoc(const K& key)
{
	size_t hash_function_value = hashfun(key);
	hash_function_value %= m_storage.size();

	typename List<Pair<K, V>>::Marker marker;
	marker = m_storage[hash_function_value].createMarker();

	while (marker.isValid())
	{
		if (marker.getValue().key == key)
			return marker.getValue().value;
		marker.next();
	}
}