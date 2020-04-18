#include <iostream>
#include <SFML/Graphics.hpp>

#include "drawer.h"


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


void Drawer::run() {
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
			switch (event.type)
			{
			case(sf::Event::Closed):
				window.close();
				break;
			case(sf::Event::Resized):
			{
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
				break;
			}
			case(sf::Event::MouseButtonPressed): {
				sf::Vector2f xy = pxToWorld(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
				if (event.mouseButton.button == sf::Mouse::Left) {
					pointMove = controller->checkNearPoint(xy.x, xy.y);
					circleChange = controller->checkNearCircle(xy.x, xy.y);
					segmentMove = controller->checkNearSegment(xy.x, xy.y);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
					Storage<double> xy_;
					xy_.add(xy.x);
					xy_.add(xy.y);
					controller->addPrimitive(P_Point, xy_);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
					Storage<double> xyr_;
					xyr_.add(xy.x);
					xyr_.add(xy.y);
					xyr_.add(30);
					controller->addPrimitive(P_Circle, xyr_);
				}

			}
											   break;
			case(sf::Event::MouseMoved): {
				sf::Vector2f xy = pxToWorld(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
				if (pointMove != nullptr) {
					pointMove->setX(xy.x);
					pointMove->setY(xy.y);
				}
				if (circleChange != nullptr) {
					circleChange->setRadius(
						pow(pow(circleChange->getCenter().getX() - xy.x, 2) + pow(circleChange->getCenter().getY() - xy.y, 2), 0.5));
				}
				if (segmentMove.key != nullptr && segmentMove.value != nullptr) {
					segmentMove.value->move(xy.x - segmentMove.key->getX(), xy.y - segmentMove.key->getY());
					segmentMove.key->setX(xy.x);
					segmentMove.key->setY(xy.y);
				}
				break;
			}
			case(sf::Event::MouseButtonReleased):
				pointMove = nullptr;
				circleChange = nullptr;
				delete segmentMove.key;
				segmentMove.key = nullptr;
				segmentMove.value = nullptr;
				break;
			default:
				break;
			}




		window.clear();
		controller->updateView();
		window.draw(text);
		window.display();
	}
}


/*void Drawer::run() //old version of run (from the lecture)
{
	while (window.isOpen()) 
	{
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
			controller->updateView();
			window.display();
		}
	}

}
*/
