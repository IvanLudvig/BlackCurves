#include "Parabola.h"

Parabola::Parabola(Factors* factors)
	:Figure(factors)
{
}
void Parabola::build(Factors* factors, Cords cords)
{
	sf::VertexArray v1 = sf::VertexArray(sf::LinesStrip, 1001);
	sf::VertexArray v2 = sf::VertexArray(sf::LinesStrip, 1001);
	float rangeMin = std::min(factors->toReal(sf::Vector2f(cords.minX(), cords.minY())).x, factors->toReal(sf::Vector2f(cords.minX(), cords.minY())).y);
	rangeMin = std::min(rangeMin, factors->toReal(sf::Vector2f(cords.maxX(), cords.maxY())).x);
	rangeMin = std::min(rangeMin, factors->toReal(sf::Vector2f(cords.maxX(), cords.maxY())).y);

	float rangeMax = std::max(factors->toReal(sf::Vector2f(cords.maxX(), cords.maxY())).x, factors->toReal(sf::Vector2f(cords.maxX(), cords.maxY())).y);
	rangeMax = std::max(rangeMax, factors->toReal(sf::Vector2f(cords.minX(), cords.minY())).x);
	rangeMax = std::max(rangeMax, factors->toReal(sf::Vector2f(cords.minX(), cords.minY())).y);
	if (rangeMin > rangeMax)
	{
		float t = rangeMin;
		rangeMin = rangeMax;
		rangeMax = t;
	}
	//rangeMax = cords.maxX();
	//rangeMin = cords.minX();
	int i = 0;
	for (float x = rangeMin; x < rangeMax; x += (rangeMax - rangeMin) / (500.0f))
	{
		float a = factors->C;
		float b = (factors->B * x) + factors->E;
		float C = factors->F + (factors->A * x * x) + (factors->D * x);
		float D2 = (b * b) - (4 * a * C);
		//std::cout << x <<" " << D2 << std::endl;
		if (D2 >= 0)
		{
			float y1 = (-b + sqrt(D2)) / (2 * a);
			float y2 = (-b - sqrt(D2)) / (2 * a);
			v1[i].position = sf::Vector2f(cords.toWorldCords(factors->toReal(sf::Vector2f(x, y1))));
			v2[i].position = sf::Vector2f(cords.toWorldCords(factors->toReal(sf::Vector2f(x, y2))));
			v1[i].color = sf::Color::Black;
			v2[i].color = sf::Color::Black;
			i++;
		}
	}
	sf::VertexArray v = sf::VertexArray(sf::LinesStrip, 2 * i);
	for (int j = 0; j < i; j++)
	{
		v[j] = v1[i - j - 1];
		//v[j + i].color = sf::Color::Black;
	}
	for (int j = 0; j < i; j++)
	{
		v[j + i] = v2[j];
		//v[j + i].color = sf::Color::Black;
	}

	vertex = sf::VertexArray(sf::LinesStrip, 2001);
	vertex = v;
}

