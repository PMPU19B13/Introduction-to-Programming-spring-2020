#pragma once

#ifndef __D_H_INCLUDED__
#define __D_H_INCLUDED__

#include <SFML/Graphics.hpp>
#include "controller.h"

class Drawer
{
public:
	sf::RenderWindow window;
	Controller *controller;

	sf::Text text;

	Drawer()
	{
		//sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
		window.create(sf::VideoMode(800, 600), "GeomStuf");
		window.setFramerateLimit(60);
		//text.setFont(font);
		text.setString("Hello world");
		text.setCharacterSize(24); 
		text.setFillColor(sf::Color::White);
		text.setStyle(sf::Text::Bold);
		text.setPosition(0, 0);
	};

	sf::Vector2f worldToPx(sf::Vector2f w)
	{
		w.x += window.getSize().x / 2.0;
		w.y += window.getSize().y / 2.0;
		return w;
	}
	sf::Vector2f pxToWorld(sf::Vector2f w)
	{
		w.x -= window.getSize().x / 2.0;
		w.y -= window.getSize().y / 2.0;
		return w;
	}

	void drawPrimitive(PrimitiveType type, const Storage<double>& params);

	void run();

	void setController(Controller *c) {	controller = c;}

	~Drawer()
	{
		std::cout << "Dis drawer!" << std::endl;
	}

};

#endif

