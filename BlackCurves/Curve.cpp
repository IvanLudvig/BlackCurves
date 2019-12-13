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

	/*
TYPE:
1 - ellipse
2 - hyperbola
3 - parabola
4 - unreal ellipse (nothing)
5 - point (pair of unreal intersecting lines)
6 - intersecting lines
7 - parallel lines
8 - line
9 - pair of unreal parallel lines
*/

	if (I2 > 0)
	{
		if ((I1 * I3) < 0)
		{
			type = 1;
			figure = new Ellipse(cs);
			stype = "Ellipse";
		}
		else if (I1 == 0)
		{
			type = 5;
			stype = "Pair of unreal intersecting lines (point)";
		}
		else
		{
			type = 4;
			stype = "Unreal ellipse (nothing)";
		}
	}
	else if (I2 < 0)
	{
		if (I3 != 0)
		{
			type = 2;
			figure = new Hyperbola(cs);
			stype = "Hyperbola";
		}
		else {
			type = 6;
			stype = "Pair of intersecting lines";
		}
	}
	else {
		if (I3 != 0)
		{
			type = 3;
			figure = new Parabola(cs);
			stype = "Parabola";
		}
		else {
			if (K > 0)
			{
				type = 9;
				stype = "Pair of unreal parallel lines";
			}
			else if (K < 0)
			{
				type = 7;
				stype = "Pair of parallel lines";
			}
			else {
				type = 8;
				figure = new LineFigure(cs);
				stype = "Line";
			}
		}
	}
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

std::string Curve::getDescription()
{
	std::string description = "";
	description += "Type: " + stype +"\n";
	if ((type == 1) || (type == 2) || (type == 3)) {
		description += figure->canonic->getCanonicalDescription();
	}
	return description;
}


