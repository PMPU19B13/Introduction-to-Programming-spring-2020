#include <iostream>

#include "drawer.h"

void Drawer::drawPrimitive(PrimitiveType type, Storage<double> params)
{
	switch (type)
	{
	case P_Point:
		if (params.size() != 2)
			throw BadArgument();

		std::cout << "Point - (" << params[0] << ", " << params[1] << ")" << std::endl;
		break;

	case P_Segment:
		if (params.size() != 4)
			throw BadArgument();

		std::cout << "Segment - start: (" << params[0] << ", " << params[1] << "), end: ("
		          << params[2] << ", " << params[3] << ")" << std::endl;
		break;

	case P_Circle:
		if (params.size() != 3)
			throw BadArgument();

		std::cout << "Circle - center: (" << params[0] << ", " << params[1]
		          << "), radius: " << params[2] << std::endl;
		break;

	default:
		std::cerr << "No implementation found!" << std::endl;
		throw BadArgument();
	}
}
