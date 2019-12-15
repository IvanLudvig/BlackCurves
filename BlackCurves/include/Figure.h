#pragma once
#include <SFML/Graphics.hpp>
#include <Cords.h>
#include <Factors.h>
#include <string>

class Figure
{
public:
	//struct Curve::coef cs;
	sf::VertexArray vertex;
	Factors* factors;
	Factors* canonic;
	Figure(Factors* f);
	virtual void draw(sf::RenderWindow& window);
	virtual void build(Factors* factors, Cords cords) = 0;
	virtual void update(Cords cords);
	virtual std::string getDescription() = 0;
};

