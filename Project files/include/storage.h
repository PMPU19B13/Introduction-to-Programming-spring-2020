#pragma once

#include <cstddef>

template<typename T>
class Storage
{
public:
    Storage();

    void add(T value);

    T get(size_t index);

    size_t size();

private:
    T *m_data;
    size_t m_size;

};
