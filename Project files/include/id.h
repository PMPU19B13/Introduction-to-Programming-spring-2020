#pragma once

#include "storage.h"

class ID
{
public:
    ID();

    bool operator==(const ID& id) const;
    bool operator<(const ID& id) const;

private:
    Storage<unsigned char> m_array;
    static size_t m_count;
};
