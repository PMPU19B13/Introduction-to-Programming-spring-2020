#ifndef ID_H
#define ID_H
#include "storage.h"

class ID
{
    public:
        ID();

    private:
        Storage<unsigned chars> m_array;
    static size_t count;
};

#endif // ID_H
