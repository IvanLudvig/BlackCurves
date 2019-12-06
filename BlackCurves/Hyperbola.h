#pragma once
#include "Figure.h"
class Hyperbola :
	public Figure
{
public:
	sf::VertexArray vertex1;
	void draw(sf::RenderWindow& window) override;
	Hyperbola(Factors* factors);
	void build(Factors* factors, Cords cords) override;
};

