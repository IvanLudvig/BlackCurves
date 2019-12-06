#include "Figure.h"


Figure::Figure(Factors* f)
{
	factors = f;
	canonic = Factors(f->A, f->B, f->C, f->D, f->E, f->F).toCanonic();
}

void Figure::update(Cords cords)
{
	build(canonic, cords);
}

void Figure::draw(sf::RenderWindow& window)
{
	window.draw(vertex);
}
