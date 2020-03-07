#include "storage.h"

template<typename T>
Storage<T>::Storage()
{
    m_data = nullptr;
    m_size = 0;
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
        T *buf = new T[m_size + 1];
        for (size_t i = 0; i < m_size; i++)
        {
            buf[i] = m_data[i];
        }
        buf[m_size] = value;
        delete[] m_data;
        m_data = buf;
        m_size++;
    }
};
template<typename T>
T Storage<T>::get(size_t index)
{
    return m_data[index];
};

template<typename T>
size_t Storage<T>::size()
{
    return m_size;
};
