#pragma once

#include "storage.h"

class ID
{
public:
    ID();

    bool equals(const ID&) const;

private:
    Storage<unsigned char> m_array;
    static size_t m_count;
};
