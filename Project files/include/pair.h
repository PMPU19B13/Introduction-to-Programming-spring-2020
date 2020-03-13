#pragma once

// TODO: Поменять на <K, V>
template<typename K, typename T>
// TODO: pair -> Pair
class pair
{
public:
    pair()
    {
    }

    pair(const K& _k, const T& _t) : k(_k), t(_t)
    {
    }

    K k;
    T t;
};