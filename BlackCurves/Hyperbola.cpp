#include "Hyperbola.h"


Hyperbola::Hyperbola(Factors* factors)
	:Figure(factors)
{
}

void Hyperbola::build(Factors* factors, Cords cords)
{
	sf::VertexArray v1 = sf::VertexArray(sf::LinesStrip, 501);
	sf::VertexArray v2 = sf::VertexArray(sf::LinesStrip, 501);
	sf::VertexArray v3 = sf::VertexArray(sf::LinesStrip, 501);
	sf::VertexArray v4 = sf::VertexArray(sf::LinesStrip, 501);
	int i = 0;
	int t = 0;
	int k = 0;

	//CORDS.TOWORLD??

	float rangeMin = std::min(factors->toReal(sf::Vector2f(cords.minX(), cords.minY())).x, factors->toReal(sf::Vector2f(cords.minX(), cords.minY())).y);
	rangeMin = std::min(rangeMin, factors->toReal(sf::Vector2f(cords.maxX(), cords.maxY())).x);
	rangeMin = std::min(rangeMin, factors->toReal(sf::Vector2f(cords.maxX(), cords.maxY())).y);

	float rangeMax = std::max(factors->toReal(sf::Vector2f(cords.maxX(), cords.maxY())).x, factors->toReal(sf::Vector2f(cords.maxX(), cords.maxY())).y);
	//rangeMax = (factors->toReal((sf::Vector2f(cords.maxX(), cords.maxY())))).x;
	//rangeMin = (factors->toReal((sf::Vector2f(cords.minX(), cords.minY())))).x;
	rangeMax = std::max(rangeMax, factors->toReal(sf::Vector2f(cords.minX(), cords.minY())).x);
	rangeMax = std::max(rangeMax, factors->toReal(sf::Vector2f(cords.minX(), cords.minY())).y);
	if (rangeMin > rangeMax)
	{
		float t = rangeMin;
		rangeMin = rangeMax;
		rangeMax = t;
	}
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
			if (t == 0)
			{
				v1[i].position = sf::Vector2f(cords.toWorldCords(factors->toReal(sf::Vector2f(x, y1))));
				v2[i].position = sf::Vector2f(cords.toWorldCords(factors->toReal(sf::Vector2f(x, y2))));
				v1[i].color = sf::Color::Black;
				v2[i].color = sf::Color::Black;
				i++;
			}
			else {
				v3[k].position = sf::Vector2f(cords.toWorldCords(factors->toReal(sf::Vector2f(x, y1))));
				v4[k].position = sf::Vector2f(cords.toWorldCords(factors->toReal(sf::Vector2f(x, y2))));
				v3[k].color = sf::Color::Black;
				v4[k].color = sf::Color::Black;
				k++;
			}

		}else {
			t = 1;
		}
	}
	sf::VertexArray v = sf::VertexArray(sf::LinesStrip, 2 * i);
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

	//v[(2 * i)] = v1[(2 * i) - 1];
	vertex = v;
	v.clear();
	v = sf::VertexArray(sf::LinesStrip, 2 * k);
	for (int j = 0; j < k; j++)
	{
		v[j] = v3[k - j - 1];
		//v[j + i].color = sf::Color::Black;
	}
	for (int j = 0; j < k; j++)
	{
		v[j + k] = v4[j];
	}
	vertex1 = v;
}


void Hyperbola::draw(sf::RenderWindow& window)
{
	window.draw(vertex);
	window.draw(vertex1);
}
