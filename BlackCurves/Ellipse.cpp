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

	float rangeMax = 0;
	float rangeMin = LLONG_MAX;
	for (float x = cords.minX() - abs(cords.minX() / 5); x <= cords.maxX() + abs(cords.maxX() / 5); x += (cords.maxX() - cords.minX()) / 10.0f)
	{
		for (float y = cords.minY() - abs(cords.minY() / 5); y <= cords.maxY() + abs(cords.maxY() / 5); y += (cords.maxY() - cords.minY()) / 10.0f)
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
	if (pow(pow(abs(v1[0].position.y - v[(2 * i) - 1].position.y), 2)+ pow(abs(v1[0].position.x - v[(2 * i) - 1].position.x), 0.5), 2) < 
		((cords.maxX()-cords.maxX())/10))
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

std::string Ellipse::getDescription()
{
	std::string s = "";
	sf::Vector2f center = canonic->toReal(sf::Vector2f(0, 0));
	float c = pow((1/canonic->C) + (1/canonic->A), 0.5);
	s += "a = " + factors->formatFloat(pow((1 / canonic->A), 0.5)) +
		"\nb = " + factors->formatFloat(pow((1 / canonic->C), 0.5)) +
		"\nc = " + factors->formatFloat(c) +
		"\ne = " + factors->formatFloat(c / pow(canonic->A, 0.5)) +
		"\n";
	s += "Center: " + factors->formatVector(center) + "\n";
	sf::Vector2f f1 = canonic->toReal(sf::Vector2f(c, 0));
	sf::Vector2f f2 = canonic->toReal(sf::Vector2f(-c, 0));
	s += "Focal points: " + factors->formatVector(f1) + ", " + factors->formatVector(f2) + "\n";
	return s;
}



