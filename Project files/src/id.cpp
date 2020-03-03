#include "id.h"
#include <cstdio>

size_t ID::m_count = 0;

ID::ID()
{
    ++m_count;
    char buf[1024];
    snprintf(buf, sizeof(buf), "%d", m_count);
    for (size_t k = 0; k < 1024; ++k)
        if (buf[k] != 0)
            m_array.add(buf[k]);
        else
            break;
}

bool ID::equals(ID id)
{
    if (m_array.size() != id.m_array.size())
        return false;

    for (size_t k = 0; k < m_array.size(); ++k)
        if (m_array.get(k) != id.m_array.get(k))
            return false;

    return true;
}
