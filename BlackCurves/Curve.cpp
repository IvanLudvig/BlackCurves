#include <iostream>
#include "Curve.h"

int sgn(float x)
{
	if (x > 0)
	{
		return 1;
	}
	return -1;
}

Curve::Curve(float A, float B, float C, float D, float E, float F, Cords cords)
{
	cs = new Factors(A, B, C, D, E, F);
	//can = cs.canonic();
	float I3 = (A * ((C * F) - (E * E / 4))) 
		- ((B / 2) * ((B * F / 2) - (D * E / 4))) 
		+ ((D / 2) * ((B * E / 4) - (C * D / 2)));
	float I2 = (A * C) - (B * B / 4);
	float I1 = A + C;
	float K = (A * F) - (D * D / 4) + (C * F) - (E * E / 4);

	if (I2 > 0)
	{
		if ((I1 * I3) < 0)
		{
			type = 1;
			figure = new Ellipse(cs);
			//build(cs, cords);
			return;
		}
		else if (I1 == 0)
		{
			type = 5;
		}
		else
		{
			type = 4;
		}
	}
	else if (I2 < 0)
	{
		if (I3 != 0)
		{
			type = 2;
			figure = new Hyperbola(cs);
			//build(cs, cords);
			return;
		}
		else {
			type = 6;
		}
	}
	else {
		if (I3 != 0)
		{
			type = 3;
			figure = new Parabola(cs);
			//build(cs, cords);
			return;
		}
		else {
			if (K > 0)
			{
				type = 9;
			}
			else if (K < 0)
			{
				type = 7;
			}
			else {
				type = 8;
				figure = new LineFigure(cs);
				//build(cs, cords);
				return;
			}
		}
	}

	if ((A == 0) && (B == 0) && (C == 0))
	{
		//type = 0;
		float k = D / E;
		float b = -F * 2 / E;
		std::cout << k << " " << b << std::endl;
		//fig = Line(k, b, 1.5f);
		sf::VertexArray v = sf::VertexArray(sf::LinesStrip, 2);
		v[0].position = sf::Vector2f(800, k * 800);
		v[1].position = sf::Vector2f(-800, -k * 800);
		v[0].color = sf::Color::Black;
		v[1].color = sf::Color::Black;
		//l.init(v);
	}
	else if ((A * C) > 0)
	{
		//type = 1;
	}
	else if ((A * C) < 0)
	{
		//type = 2;
	}
	else
	{
		//type = 3;
	}
	//build(cs, cords);
}

Curve::Curve(int a, int b, int type)
{
}

void Curve::draw(sf::RenderWindow& window)
{
	if ((type == 1) || (type == 2) || (type == 3)) {
		figure->draw(window);
	}
}


void Curve::update(Cords cords)
{
	if ((type == 1) || (type == 2) || (type == 3)) {
		figure->update(cords);
	}
}

int Curve::getType()
{
	return type;
}


