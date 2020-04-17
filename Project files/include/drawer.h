#pragma once

#ifndef __D_H_INCLUDED__
#define __D_H_INCLUDED__

#include <SFML/Graphics.hpp>
#include "controller.h"

class Drawer
{
public:
	sf::RenderWindow window;
	Controller* controller;

	void setController(Controller* co) 
	{
		controller = co;
	}

	Drawer()
	{
		//sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
		window.create(sf::VideoMode(800, 600), "GeomStuf");
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

	void run();

};

#endif

