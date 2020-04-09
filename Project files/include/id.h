#pragma once

#include "storage.h"

class ID
{
public:
    ID();
    ID(char* temp);
    
    bool operator==(const ID& id) const;
    bool operator<(const ID& id) const;
    
    static void initCount(size_t newCount);

    static size_t getLastCount();
    
    friend std::ostream& operator<<(std::ostream& out, const ID& id);

private:
    Storage<unsigned char> m_array;
    static size_t m_count;
};
