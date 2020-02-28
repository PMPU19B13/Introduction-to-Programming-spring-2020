#pragma once
#include "storage.h"

class ID
{
public:
	ID();
	bool is_equal(ID);

private:
	Storage<unsigned char> m_array;
	static size_t count;
};
