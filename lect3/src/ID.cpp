#include "ID.h"

size_t ID::count = 0;

ID::ID()
{
    ++count;
}
