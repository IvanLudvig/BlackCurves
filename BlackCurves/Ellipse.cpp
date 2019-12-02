#include "Ellipse.h"

Ellipse::Ellipse(Factors* factors)
	:Figure(factors)
{
}
void Ellipse::build(Factors* factors, Cords cords)
{
	sf::VertexArray v1 = sf::VertexArray(sf::LinesStrip, 1001);
	sf::VertexArray v2 = sf::VertexArray(sf::LinesStrip, 1001);
	float rangeMin = factors->toLocal(sf::Vector2f(cords.minX(), cords.minY())).x;
	float rangeMax = factors->toLocal(sf::Vector2f(cords.maxX(), cords.maxY())).x;
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
	sf::VertexArray v = sf::VertexArray(sf::LinesStrip, (2 * i) + 1);
	for (int j = 0; j < i; j++)
	{
		v[j] = v1[j];
		//v[j + i].color = sf::Color::Black;
	}
	for (int j = 0; j < i; j++)
	{
		v[j + i] = v2[i - j - 1];
		//v[j + i].color = sf::Color::Black;
	}
	if (abs(v1[0].position.y - v[(2 * i) - 1].position.y) < 10)
	{
		v[2 * i] = v1[0];
	}
	else
	{
		v[2 * i] = v[(2 * i) - 1];
	}
	v[(2 * i)] = v1[0];
	vertex = v;
}

void Ellipse::update(Cords cords)
{
	build(factors, cords);
}

void Ellipse::draw(sf::RenderWindow& window)
{
	window.draw(vertex);
}
