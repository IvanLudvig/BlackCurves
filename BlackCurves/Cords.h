#pragma once
#include <SFML\System\Vector2.hpp>

class Cords
{
public:
	Cords();
	sf::Vector2f toWorldCords(sf::Vector2f v);
	sf::Vector2f toLocalCords(sf::Vector2f v);
	static float radiansToDegrees(float rad);
	void setCenter(sf::Vector2f v);
	float maxX();
	float minX();
	float maxY();
	float minY();
	static const int R;
	float scale;
	float zoom;
	sf::Vector2f topRight;
	sf::Vector2f bottomLeft;
	sf::Vector2f center;
};

