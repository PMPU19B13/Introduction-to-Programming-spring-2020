#pragma once

#include "storage.h"

class ID
{
public:
    ID();

    bool operator==(const ID& id);

private:
    Storage<unsigned char> m_array;
    static size_t m_count;
};
