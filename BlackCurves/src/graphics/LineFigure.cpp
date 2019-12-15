#include "LineFigure.h"


LineFigure::LineFigure(Factors* factors)
	:Figure(factors)
{
}
void LineFigure::build(Factors* factors, Cords cords)
{
	vertex = sf::VertexArray(sf::LinesStrip, 2);
	float k = -canonic->E / canonic->D;
	float b = canonic->F / canonic->E;
	float rangeMax = 0;
	float rangeMin = LLONG_MAX;
	for (float x = cords.minX() * 0.8f; x <= cords.maxX() * 1.5f; x += (cords.maxX() - cords.minX()) / 10.0f)
	{
		for (float y = cords.minY() * 0.8f; y <= cords.maxY() * 1.5f; y += (cords.maxY() - cords.minY()) / 10.0f)
		{
			rangeMin = std::min(rangeMin, factors->toLocal((sf::Vector2f(x, y))).x);
			rangeMax = std::max(rangeMax, factors->toLocal((sf::Vector2f(x, y))).x);
		}
	}
	vertex[0] = cords.toWorldCords(factors->toReal(sf::Vector2f(cords.maxX(), (k*cords.maxX())+b)));
	vertex[1] = cords.toWorldCords(factors->toReal(sf::Vector2f(cords.minX(), (k*cords.minX())+b)));
	vertex[0] = cords.toWorldCords(factors->toReal(sf::Vector2f(rangeMin, 0)));
	vertex[1] = cords.toWorldCords(factors->toReal(sf::Vector2f(rangeMax, 0)));
	//vertex[1] = cords.toWorldCords(factors->toReal(sf::Vector2f(canonic->F, cords.minY())));
	if (canonic->E != 0)
	{
		//vertex[0] = cords.toWorldCords(factors->toReal(sf::Vector2f(cords.maxX(), (-canonic->D / canonic->E) * cords.maxX())));
		//vertex[1] = cords.toWorldCords(factors->toReal(sf::Vector2f(cords.minX(), (-canonic->D / canonic->E) * cords.minX())));
	}
	else {
		//vertex[0] = cords.toWorldCords(factors->toReal(sf::Vector2f(canonic->F, cords.maxY())));
		//vertex[1] = cords.toWorldCords(factors->toReal(sf::Vector2f(canonic->F, cords.minY())));
	}
	vertex[0].color = sf::Color::Black;
	vertex[1].color = sf::Color::Black;
}

std::string LineFigure::getDescription()
{
	return "a";
}


