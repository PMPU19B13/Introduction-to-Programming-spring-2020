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

	bool operator<(const Pair& pair) {
		if (value < pair.value) return true;
		return false;
	}

	bool operator>(const Pair& pair) {
		if (value > pair.value) return true;
		return false;
	}

    K key;
    V value;
};