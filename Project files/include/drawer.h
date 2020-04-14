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

	void run() {
		while (window.isOpen()) {
			sf::Event event;
			while (window.pollEvent(event)) 
			{
				switch (event.type) 
				{
				case sf::Event::Closed: 
				{
					window.close();
					break; 
				}

				case sf::Event::Resized: 
				{
					sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
					window.setView(sf::View(visibleArea));
					break; 
				}
				case sf::Event::KeyPressed:
				{
					Storage<double> pointParams;
					Storage<double> segmentParams;
					Storage<double> circleParams;

					pointParams.add(1.2);
					pointParams.add(14.7);

					segmentParams.add(1.6);
					segmentParams.add(3.2);
					segmentParams.add(6.4);
					segmentParams.add(0.8);

					circleParams.add(0);
					circleParams.add(0);
					circleParams.add(5.5);

					controller->addPrimitive(P_Point, pointParams);
					controller->addPrimitive(P_Segment, segmentParams);
					controller->addPrimitive(P_Circle, circleParams);
				}
				}

				window.clear();
				//Обновить содержимое окна
				controller->updateView();
				window.display();
			}
		}

	}

};

#endif

