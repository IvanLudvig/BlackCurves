#pragma once
#include "Figure.h"

class Ellipse :
	public Figure
{
public:
	void draw(sf::RenderWindow& window) override;
	Ellipse(Factors* factors);
	void build(Factors* factors, Cords cords) override;
	void update(Cords cords) override;
};

