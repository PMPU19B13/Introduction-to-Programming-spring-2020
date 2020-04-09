#pragma once

#include "controller.h"

class Drawer
{
public:
	void drawPrimitive(PrimitiveType type, const Storage<double>& params);
};
