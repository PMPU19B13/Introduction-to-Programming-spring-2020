#include "ID.h"
#include <stdio.h>

size_t ID::count = 0;

ID::ID()
{
	++count;
	char buf[1024];
	snprintf(buf, sizeof(buf), "%d", count);
	for (size_t k = 0; k < 1024; ++k)
		if (buf[k] != 0)
			m_array.AddElem(buf[k]);
		else
			break;
}

bool ID::is_equal(ID id) {
	if (m_array.TotalSize() != id.m_array.TotalSize())
		return false;

	for (size_t k = 0; k < m_array.TotalSize(); ++k)
		if (m_array.GetElemByNum(k) != id.m_array.GetElemByNum(k))
			return false;

	return true;
}
