#include "drawer.h"

void Drawer::drawPrimitive(PrimType pt, Storage<double> params)
{
	if (pt == P_Point)
	{
		std::cout << "Point: " << params[0] << '-' << params[1] << '\n';
	}
	if (pt == P_Segment)
	{
		std::cout << "Segment start: " << params[0] << '-' << params[1] << "; end: " << params[2] << '-' << params[3] << '\n';
	}
	if (pt == P_Circle)
	{
		std::cout << "Circle center: " << params[0] << '-' << params[1] << "; radius: " << params[2] << '\n';
	}
}
