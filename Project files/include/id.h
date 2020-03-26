#pragma once

#include "storage.h"

class ID
{
public:
    ID();

    bool operator==(const ID& id) const;

    bool operator<(const ID& id) const;

    static void initCount(size_t newCount);

    static size_t getLastCount();

private:
    Storage<unsigned char> m_array;
    static size_t m_count;
};
