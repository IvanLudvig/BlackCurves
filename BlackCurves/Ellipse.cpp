#include "Ellipse.h"

Ellipse::Ellipse(Factors* factors)
	:Figure(factors)
{
}

float normalize(sf::Vector2f v)
{
	return pow(pow(v.x, 2.0f) + pow(v.y, 2.0f), 0.5f);
}
void Ellipse::build(Factors* factors, Cords cords)
{
	sf::VertexArray v1 = sf::VertexArray(sf::LinesStrip, 1001);
	sf::VertexArray v2 = sf::VertexArray(sf::LinesStrip, 1001);

	float rangeMin = (factors->toReal(cords.toWorldCords(sf::Vector2f(cords.minX(), cords.minY())))).x;
	float rangeMax = (factors->toReal(cords.toWorldCords(sf::Vector2f(cords.maxX(), cords.maxX())))).x;
	rangeMax = 0;
	rangeMin = 10000;
	for (float x = cords.minX()*0.8f; x <= cords.maxX()*1.5f; x += (cords.maxX() - cords.minX()) / 10.0f)
	{
		for (float y = cords.minY()*0.8f; y <= cords.maxY()*1.5f; y += (cords.maxY() - cords.minY()) / 10.0f)
		{
			rangeMin = std::min(rangeMin, factors->toLocal((sf::Vector2f(x, y))).x);
			rangeMax = std::max(rangeMax, factors->toLocal((sf::Vector2f(x, y))).x);
		}
	}

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
	vertex = sf::VertexArray(sf::LinesStrip, 2001);
	vertex = v;
}



