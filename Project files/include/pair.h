#pragma once

template<typename K, typename V>
class Pair
{
public:
	Pair()
	{
	}

	Pair(const K& _key, const V& _value) : key(_key), value(_value)
	{
	}

	K key;
	V value;
};