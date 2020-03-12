#pragma once

#include <cstddef>
#include "error.h"

template<typename T>
class Storage
{
public:
    Storage();
    Storage(const Storage<T>& original);

    ~Storage();

    Storage& operator=(const Storage<T>& original);

    T& operator[](size_t index);

    void add(T value);

    void insert(size_t index, T value);
    void remove(size_t index);

    T get(size_t index) const;
    void set(size_t index, T value);

    size_t size() const;

private:
    T* m_data;
    size_t m_size;

};

template<typename T>
Storage<T>::Storage()
{
    m_data = nullptr;
    m_size = 0;
}

template<typename T>
Storage<T>::Storage(const Storage<T>& original)
{
    m_size = original.size();
    m_data = new T[m_size];
    for (size_t i = 0; i < m_size; ++i)
        m_data[i] = original.get(i);
}

template<typename T>
Storage<T>::~Storage()
{
    if (m_data != nullptr)
        delete[] m_data;
}

template<typename T>
Storage<T>& Storage<T>::operator=(const Storage<T>& original)
{
    m_size = original.size();
    if (m_data != nullptr)
        delete[] m_data;
    m_data = new T[m_size];
    for (size_t i = 0; i < m_size; ++i)
        m_data[i] = original.get(i);
}

template<typename T>
T& Storage<T>::operator[](size_t index)
{
    if (index >= m_size)
        throw BadArgument();

    return m_data[index];
}

template<typename T>
void Storage<T>::add(T value)
{
    if (m_data == nullptr)
    {
        m_data = new T[1];
        m_data[0] = value;
        m_size = 1;
    }
    else
    {
        T* buffer = new T[m_size + 1];
        for (size_t i = 0; i < m_size; i++)
            buffer[i] = m_data[i];
        buffer[m_size] = value;
        delete[] m_data;
        m_data = buffer;
        ++m_size;
    }
};

template<typename T>
void Storage<T>::insert(size_t index, T value)
{
    if (index <= m_size)
    {
        T* temp = new T[m_size + 1];
        for (size_t i = 0; i < index; ++i)
        {
            temp[i] = m_data[i];
        }
        temp[index] = value;
        for (size_t i = index; i < m_size + 1; ++i)
        {
            temp[i + 1] = m_data[i];
        }
        delete[] m_data;
        m_data = temp;
        ++m_size;
    }
    else
        throw BadArgument();
};

template<typename T>
void Storage<T>::remove(size_t index)
{
    if (index < m_size)
    {
        T* temp = new T[m_size - 1];
        for (size_t i = 0; i < index; i++)
        {
            temp[i] = m_data[i];
        }
        for (size_t i = index; i < m_size - 1; i++)
        {
            temp[i] = m_data[i+1];
        }
        delete[] m_data;
        m_data = temp;
        --m_size;
    }
    else
        throw BadArgument();
};

template<typename T>
T Storage<T>::get(size_t index) const
{
    if (index >= m_size)
        throw BadArgument();

    return m_data[index];
};

template<typename T>
void Storage<T>::set(size_t index, T value)
{
    if (index < m_size)
        m_data[index] = value;
}

template<typename T>
size_t Storage<T>::size() const
{
    return m_size;
};