#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Thor/Shapes.hpp>
#include "Line.h"
#include "Tick.h"
#pragma once


class Axis
{
public:
	sf::ConvexShape x, y;
	sf::Font font;
	std::vector<Tick> ticks;
	Axis(Cords cords);
	void draw(sf::RenderWindow& window);
	void update(Cords cords);
};

