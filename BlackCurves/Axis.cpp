#include "Axis.h"

Cords oldCords;

Axis::Axis(Cords cords)
{
	if (!font.loadFromFile("consolas.ttf"))
	{
		//std::cout << "ERROR: Cannot load font" << std::endl;
	}


	update(cords);
	//y = thor::Shapes::line(sf::Vector2f(0, y2), sf::Color(255, 0, 0), 1.0f);
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
	//x.draw(window);
	//y.draw(window);
	for (int i = 0; i < ticks.size(); i++) {
		ticks.at(i).draw(window);
	}
}

void Axis::update(Cords cords)
{/*
	if ( ((oldCords.maxX*1.5) <= cords.maxX) || ((oldCords.maxY * 1.5) <= cords.maxY)
		|| ((oldCords.minX * 1.5) <= cords.minX) || ((oldCords.maxY * 1.5) <= cords.maxY))
	{

	}*/
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
	}/*
	dx = (cords.maxX() - cords.minX());
	dy = (cords.maxY() - cords.minY());
	if ((dx == 0) || (dy == 0))
	{
		return;
	}
	float mx = 1.0f;
	while (dx < 10)
	{
		dx *= 10;
		mx *= 10;
		std::cout << dx << std::endl;
	}
	float my = 1.0f;
	while (dy < 10)
	{
		dy *= 10;
		my *= 10;
	}
	dx = roundToTen(static_cast<int>(dx*mx))/(mx*mx*10);
	dy = roundToTen(static_cast<int>(dy*my))/(my*my*10);*/
	ticks.clear();
	//std::cout << "x1, x2: " << x1 << ", " << x2 << std::endl;
	std::cout << "dx, dy: " << dx << ", " << dy << std::endl;
	//int i = 0; i < 10; i++
	//std::cout << dx <<" "<<x2<<" "<< dy<<" "<<y2 << std::endl;
	//ticks.push_back(Tick(sf::Vector2f(100, 0)));
	for (float x = 0; x < std::max(std::abs(cords.minX()), std::abs(cords.maxX())) * 1.5; x += dx)
	{
		ticks.push_back(Tick(sf::Vector2f(x, 0), cords, font));
		ticks.push_back(Tick(sf::Vector2f(-x, 0), cords, font));
		//std::cout << x << " ";
	}
	for (float y = dy; y < std::max(std::abs(cords.minY()), std::abs(cords.maxY())) * 1.5; y += dy)
	{
		ticks.push_back(Tick(sf::Vector2f(0, y), cords, font));
		ticks.push_back(Tick(sf::Vector2f(0, -y), cords, font));
	}
	oldCords = cords;
}

