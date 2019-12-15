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

		}
		else {
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

std::string Hyperbola::getDescription()
{
	std::string s = "";
	sf::Vector2f center = canonic->toReal(sf::Vector2f(0, 0));
	float c = pow(pow(1 / canonic->C, 2) + pow(1 / canonic->A, 2), 0.5);
	s += "a = " + factors->formatFloat(pow((1 / canonic->A), 0.5)) +
		"\nb = " + factors->formatFloat(pow(abs(1 / canonic->C), 0.5)) +
		"\nc = " + factors->formatFloat(c) +
		"\ne = " + factors->formatFloat(c / pow(canonic->A, 0.5)) +
		"\n";
	s += "Center: " + factors->formatVector(center) + "\n";
	sf::Vector2f v1 = canonic->toReal(sf::Vector2f(pow(canonic->A, 0.5), 0));
	sf::Vector2f v2 = canonic->toReal(sf::Vector2f(-pow(canonic->A, 0.5), 0));
	s += "Vertices: " + factors->formatVector(v1) + ", " + factors->formatVector(v2) + "\n";
	sf::Vector2f f1 = canonic->toReal(sf::Vector2f(c, 0));
	sf::Vector2f f2 = canonic->toReal(sf::Vector2f(-c, 0));
	s += "Focal points: " + factors->formatVector(f1) + ", " + factors->formatVector(f2) + "\n";
	return s;
}


void Hyperbola::draw(sf::RenderWindow& window)
{
	window.draw(vertex);
	window.draw(vertex1);
}
