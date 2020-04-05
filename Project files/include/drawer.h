#pragma once

#ifndef __D_H_INCLUDED__
#define __D_H_INCLUDED__

#include <SFML/Graphics.hpp>
#include "controller.h"

class Drawer
{
public:
	sf::RenderWindow window;

	Drawer()
	{
		window.create(sf::VideoMode(800, 600), "GeomStuf");
		window.clear();
		window.display();
	};

	sf::Vector2f worldToPx(sf::Vector2f w)
	{
		w.x += window.getSize().x / 2;
		w.y += window.getSize().y / 2;
		return w;
	}

	void drawPrimitive(PrimitiveType type, const Storage<double>& params);

	~Drawer()
	{
		std::cout << "Dis" << std::endl;
	}


};

#endif

