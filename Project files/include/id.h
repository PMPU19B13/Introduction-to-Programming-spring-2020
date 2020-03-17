#pragma once

#include "storage.h"

class ID
{
public:
    ID();

    friend bool operator==(const ID& id1, const ID& id2);

private:
    Storage<unsigned char> m_array;
    static size_t m_count;
};
