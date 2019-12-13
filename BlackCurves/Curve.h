#include "cmath"
#include <Thor/Shapes.hpp>
#include <Ellipse.h>
#include <Hyperbola.h>
#include <Parabola.h>
#include <LineFigure.h>
#include <string.h>
#pragma once

class Curve
{
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
public:
	Curve(float A, float B, float C, float D, float E, float F, Cords cords);
	Curve(int a, int b, int type);
	void draw(sf::RenderWindow& window);
	void update(Cords cords);
	std::string getDescription();

private:
	sf::ConvexShape fig;
	sf::VertexArray vert1, vert2;
	int type;
	std::string stype;
	Factors* cs;
	Figure* figure;
};
