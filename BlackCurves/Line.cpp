#include "Line.h"

Line::Line(float x1, float y1, float x2, float y2)
	: sf::ConvexShape(thor::Shapes::line(sf::Vector2f(x2 - x1, y2 - y1), sf::Color(0, 0, 0), 1.0f))
{
	this->setPosition(0, 0);
}

Line::Line(float k, float b)
	: sf::ConvexShape(thor::Shapes::line(sf::Vector2f(Cords::R * 800, Cords::R* k * 800), sf::Color(0, 0, 0), 1.0f))
{
	this->setPosition((Cords::R / 2) * (-800), ((Cords::R / 2) * (-800) * k) + b);
}

Line::Line(float k, float b, float thickness)
	: sf::ConvexShape(thor::Shapes::line(sf::Vector2f(Cords::R * 800, Cords::R* k * 800), sf::Color(0, 0, 0), thickness))
{
	this->setPosition((Cords::R / 2) * (-800), ((Cords::R / 2) * (-800) * k) + b);
}

Line::Line(float x, float thickness, bool b)
	: sf::ConvexShape(thor::Shapes::line(sf::Vector2f(0, Cords::R * 800), sf::Color(0, 0, 0), thickness))
{
	this->setPosition(x, ((Cords::R / 2) * (-800)));
}