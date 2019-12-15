#include <Thor/Shapes.hpp>
#include <SFML/Graphics.hpp>
#include "Cords.h"

#pragma once
class Line : public sf::ConvexShape
{
public:
	Line(float x1, float y1, float x2, float y2);
	Line(float k, float b);
	Line(float k, float b, float thickness);
	Line(float x, float thickness, bool b);
};

