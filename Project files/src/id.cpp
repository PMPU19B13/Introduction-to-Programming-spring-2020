#include "id.h"
#include <cstdio>

size_t ID::m_count = 0;

ID::ID()
{
    ++m_count;
    char buf[1024];

    for (size_t k = 0; k < sizeof(buf); ++k)
        buf[k] = 0;

    snprintf(buf, sizeof(buf), "%zu", m_count);
    for (size_t i = 0; i < 1024; ++i)
        if (buf[i] != 0)
            m_array.add(buf[i]);
        else
            break;
}

bool operator==(const ID& id1, const ID& id2)
{
    if (id1.m_array.size() != id2.m_array.size())
        return false;

    for (size_t k = 0; k < id1.m_array.size(); ++k)
        if (id1.m_array[k] != id2.m_array[k])
            return false;

    return true;
}
