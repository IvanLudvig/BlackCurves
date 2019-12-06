#include <SFML/Graphics.hpp>
#include "Curve.h"
#include "Axis.h"
#include "Cords.h"
#include "Curves.h"
#include "LineFigure.h"

Cords cords = Cords();
Axis axis(cords);
sf::Text text;
sf::RenderWindow window(sf::VideoMode(1000, 600), "View", sf::Style::Close);

//Curve curve(0, 0, -2, 5 / 2, 20 / 2, 4, cords);
//Curve curve(0.5, 0.2, 0.33, -152, -360, -27, cords); //ellipse
//Curve curve(4, 28, 49, -3, -15, 2, cords);  //parabola
//Curve curve(1, -2, 1, -2, -2, 1, cords);  //parabola
//Curve curve(1, -8, 16, 6, -24, 9, cords);   //line
Curve curve(225, -240, 64, 30, -16, 1, cords);   //line
//Curve curve(25, 0, 0, -30, 0, 9, cords);   //line
//Curve curve(0, 0, 0, 15, -8, 1, cords);   //line
//Curve curve(81, -36, 4, 0, 0, 0, cords);   //2 p lines
//Curve curve(5, 0, -16, -6, 8, -144, cords);
//Curve curve(9, 0, -16, -6, 8, -144, cords);
//Curve curve(17, -9, 1, -3, -1, -3, cords);
//Curve curve(17, -2, 1, -3, -1, -3, cords);
//Curve curve(1, -8, 16, 6, -24, 9, cords);
//Curve curve(5, 12, 10, -6, 4, -1, cords);  //ellipse
//Curve curve(2, 6, 10, 0, 0, -121, cords);
//Curve curve(2, -4, 5, 8, -2, 9, cords);


void Curves::update()
{
	cords.scale = 800 / ((cords.maxX() - cords.minX()) * cords.zoom);
	curve.update(cords);
	axis.update(cords);
}

void Curves::init()
{
	//curve = Curve(4, 28, 49, -3, -15, 2, cords);
	sf::Font font;
	font.loadFromFile("consolas.ttf");
	text.setFont(font);
	text.setString("TYPE: " + std::to_string(curve.type));
	text.setPosition(100, 100);
	text.setColor(sf::Color::Black);
	sf::Vector2f oldPos;
	bool moving = false;

	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	sf::View view = window.getDefaultView();
	view.setSize(800, -480);
	view.setCenter(0, 0);
	window.setView(view);
	//window.close();


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

				cords.setCenter(view.getCenter());
				update();
				break;
			}
			case sf::Event::MouseWheelScrolled:
				if (moving)
					break;
				if (event.mouseWheelScroll.delta <= -1)
				{
					cords.zoom = std::min(15.0f, cords.zoom + (cords.zoom / 10));
				}
				else if (event.mouseWheelScroll.delta >= 1)
				{
					cords.zoom = std::max(.05f, cords.zoom - (cords.zoom / 10));
				}
				cords.setCenter(view.getCenter());
				update();
				break;
			}


		sf::VertexArray line(sf::Lines, 2);
		line[0].position = sf::Vector2f(0, 0);
		line[0].color = sf::Color(100, 0, 200);
		line[1].position = sf::Vector2f(100, 100);
		line[1].color = sf::Color(100, 0, 200);

		window.clear(sf::Color::White);
		axis.draw(window);
		//window.draw(ellipse);
		curve.draw(window);
		//window.draw(text);
		window.display();
	}
}

int Curves::getType()
{
	return curve.getType();
}


