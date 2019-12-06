#pragma once
#include <SFML/Graphics.hpp>
#include "Cords.h"
#include <cmath>

class Factors
{
public:
	float A, B, C, D, E, F;
	//float angle;
	//sf::Vector2f center;
	sf::Transform transform;
	Factors(float a, float b, float c, float d, float e, float f);
	Factors(float a, float b, float c, float d, float e, float f, float Angle, float Angle1, sf::Vector2f Center);
	Factors* toCanonic();
	sf::Vector2f toReal(sf::Vector2f v);
	sf::Vector2f toLocal(sf::Vector2f v);
};

