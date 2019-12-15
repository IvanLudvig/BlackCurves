#include "Axis.h"

Cords oldCords;

Axis::Axis(Cords cords)
{
	if (!font.loadFromFile("consolas.ttf"))
	{
		std::cout << "ERROR: Cannot load font" << std::endl;
	}
	update(cords);
}

int roundToTen(int toRound)
{
	if (toRound % 10 == 0) return toRound;
	return (10 - toRound % 10) + toRound;
}

void Axis::draw(sf::RenderWindow& window)
{
	window.draw(x);
	window.draw(y);
	for (int i = 0; i < ticks.size(); i++) {
		ticks.at(i).draw(window);
	}
}

void Axis::update(Cords cords)
{
	x = Line(0, 0, 1.0f);
	y = Line(0, 1.0f, true);

	x.setFillColor(sf::Color::Magenta);
	y.setFillColor(sf::Color::Magenta);

	float dx = 0.5;
	float dy = 0.5;
	if (((cords.maxX() - cords.minX()) > 10) && ((cords.maxX() - cords.minX()) <= 50))
	{
		dx = 2;
		dy = 2;
	}
	else if (((cords.maxX() - cords.minX()) > 50) && ((cords.maxX() - cords.minX()) <= 100)) {
		dx = 5;
		dy = 5;
	}
	else if (((cords.maxX() - cords.minX()) > 100) && ((cords.maxX() - cords.minX()) <= 200)) {
		dx = 10;
		dy = 10;
	}
	else if (((cords.maxX() - cords.minX()) > 200) && ((cords.maxX() - cords.minX()) <= 500)) {
		dx = 50;
		dy = 50;
	}
	else if (((cords.maxX() - cords.minX()) > 500) && ((cords.maxX() - cords.minX()) <= 1000)) {
		dx = 100;
		dy = 100;
	}
	else {
		dx = ((int)(cords.maxX() - cords.minX()) / 10);
		dy = ((int)(cords.maxY() - cords.minY()) / 10);
		if (dx == 0) {
			dx = 0.5f;
			dy = 0.5f;
		}
	}

	ticks.clear();

	for (float x = 0; x < std::max(std::abs(cords.minX()), std::abs(cords.maxX())) * 1.5; x += dx)
	{
		ticks.push_back(Tick(sf::Vector2f(x, 0), cords, font));
		ticks.push_back(Tick(sf::Vector2f(-x, 0), cords, font));
	}
	for (float y = dy; y < std::max(std::abs(cords.minY()), std::abs(cords.maxY())) * 1.5; y += dy)
	{
		ticks.push_back(Tick(sf::Vector2f(0, y), cords, font));
		ticks.push_back(Tick(sf::Vector2f(0, -y), cords, font));
	}
	oldCords = cords;
}

