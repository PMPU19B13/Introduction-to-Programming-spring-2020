#pragma once

#include "controller.h"
#include "fstream"

class Drawer
{
public:
    void drawPrimitive(PrimitiveType type, Storage<double> params);
	void drawPrimitive(std::fstream& file, PrimitiveType type, Storage<double> params);
};
