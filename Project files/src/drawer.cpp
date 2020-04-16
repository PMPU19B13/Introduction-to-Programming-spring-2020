#include <iostream>
#include <SFML/Graphics.hpp>

#include "drawer.h"

void Drawer::run() {
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

				segmentParams.add(0.0);
				segmentParams.add(0.0);
				segmentParams.add(100.0);
				segmentParams.add(100.0);

				circleParams.add(0.0);
				circleParams.add(0.0);
				circleParams.add(200.0);

				controller->addPrimitive(P_Point, pointParams);
				controller->addPrimitive(P_Segment, segmentParams);
				controller->addPrimitive(P_Circle, circleParams);
			}
			default:
				break;
			}

			window.clear();
			//Обновить содержимое окна
			controller->updateView();
			window.display();
		}
	}

}

void Drawer::drawPrimitive(PrimitiveType type, const Storage<double>& params)
{
	switch (type)
	{
	case P_Point:
{
		if (params.size() != 2)
			throw BadArgument();

		sf::CircleShape shape(100.f);
		shape.setPosition(worldToPx(sf::Vector2f(params[0], params[1])));
		shape.setRadius(2);
		shape.setFillColor(sf::Color::Green);
		shape.setOrigin(shape.getRadius(), shape.getRadius());
		window.draw(shape);

		break;
	}
	case P_Segment:
	{
		if (params.size() != 4)
			throw BadArgument();

		sf::VertexArray shape(sf::LinesStrip, 2);

		shape[0].color = sf::Color::White;
		shape[0].position = worldToPx(sf::Vector2f(params[0], params[1]));
		shape[1].position = worldToPx(sf::Vector2f(params[2], params[3]));
		shape[1].color = sf::Color::White;

		window.draw(shape);

		break;
	}
	case P_Circle:
	{
		if (params.size() != 3)
			throw BadArgument();

		sf::CircleShape shape(100.f);
		shape.setFillColor(sf::Color(0, 0, 0, 0));
		shape.setPosition(worldToPx(sf::Vector2f(params[0], params[1])));
		shape.setRadius(params[2]);
		shape.setOutlineColor(sf::Color::Green);
		shape.setOutlineThickness(1);
		shape.setOrigin(shape.getRadius(), shape.getRadius());
		window.draw(shape);

		break;
	}
	default:
		std::cerr << "No implementation found!" << std::endl;
		throw BadArgument();
	}
}
