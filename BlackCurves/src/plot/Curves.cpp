#include <SFML/Graphics.hpp>
#include "Curves.h"


Curves::Curves(float A, float B, float C, float D, float E, float F)
{
	cords = new Cords();
	axis = new Axis(*cords);
	curve = new Curve(A, B, C, D, E, F, *cords);
}

void Curves::update()
{
	cords->setScale(800 / ((cords->maxX() - cords->minX()) * cords->getZoom()));
	curve->update(*cords);
	axis->update(*cords);
}

void Curves::open()
{
	if ((curve->getType() != 1) && (curve->getType() != 2) && (curve->getType() != 3)) {
		return;
	}
	sf::RenderWindow window(sf::VideoMode(1000, 600), "Plot", sf::Style::Close);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	sf::View view = window.getDefaultView();
	view.setSize(800, -480);
	view.setCenter(0, 0);
	window.setView(view);
	update();

	sf::Vector2f oldPos;
	bool moving = false;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == 0) {
					moving = true;
					oldPos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
				}
				break;

			case  sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == 0) {
					moving = false;
				}

				break;
			case sf::Event::MouseMoved:
			{
				if (!moving)
					break;

				const sf::Vector2f newPos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));

				const sf::Vector2f deltaPos = (oldPos)-(newPos);

				view.setCenter(view.getCenter() + deltaPos);
				window.setView(view);

				cords->setCenter(view.getCenter());
				update();
				break;
			}
			case sf::Event::MouseWheelScrolled:
				if (moving)
					break;
				if (event.mouseWheelScroll.delta <= -1)
				{
					cords->setZoom(std::min(15.0f, cords->getZoom() + (cords->getZoom() / 10)));
				}
				else if (event.mouseWheelScroll.delta >= 1)
				{
					cords->setZoom(std::max(.05f, cords->getZoom() - (cords->getZoom() / 10)));
				}
				cords->setCenter(view.getCenter());
				update();
				break;
			}

		window.clear(sf::Color::White);
		axis->draw(window);
		curve->draw(window);
		window.display();
	}
}

std::string Curves::getDescription()
{
	return (curve->getDescription());
}


