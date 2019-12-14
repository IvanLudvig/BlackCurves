#include "Parabola.h"

Parabola::Parabola(Factors* factors)
	:Figure(factors)
{
}
void Parabola::build(Factors* factors, Cords cords)
{
	sf::VertexArray v1 = sf::VertexArray(sf::LinesStrip, 1001);
	sf::VertexArray v2 = sf::VertexArray(sf::LinesStrip, 1001);
	float rangeMax = 0;
	float rangeMin = LLONG_MAX;
	for (float x = cords.minX() - abs(cords.minX()/5); x <= cords.maxX()+ abs(cords.maxX() / 5); x += (cords.maxX() - cords.minX()) / 10.0f)
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

std::string Parabola::getDescription()
{
	std::string s = "";
	float c = pow(pow(canonic->C, 2) + pow(canonic->A, 2), 0.5);
	s += "p = " + factors->formatFloat(canonic->D/2) +
		"\ne = " + "1" +
		"\n";
	sf::Vector2f v1 = canonic->toReal(sf::Vector2f(0, 0));
	s += "Vertex: " + factors->formatVector(v1) + "\n";
	sf::Vector2f f1 = canonic->toReal(sf::Vector2f(canonic->D/4, 0));
	s += "Focal point: " + factors->formatVector(f1) + "\n";
	return s;
}

