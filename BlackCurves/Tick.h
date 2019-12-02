#pragma once
#include <SFML/Graphics.hpp>
#include "Cords.h"
#include "Line.h"
#include <iomanip>
#include <sstream>
#include <Thor/Shapes.hpp>


class Tick
{
public:
	sf::Text text;
	sf::ConvexShape line;
	sf::Vector2f val;

	Tick(sf::Vector2f val, Cords cords, sf::Font& font);
	void draw(sf::RenderWindow& window);
};

