#pragma once
#include <SFML\System\Vector2.hpp>

class Cords
{
public:
	Cords();
	sf::Vector2f toWorldCords(sf::Vector2f v);
	sf::Vector2f toLocalCords(sf::Vector2f v);
	static float radiansToDegrees(float rad);
	static float Cords::degreesToRadians(float deg);
	void setCenter(sf::Vector2f v);
	void setScale(float newScale);
	void setZoom(float newZoom);
	float getZoom();
	float getScale();
	float maxX();
	float minX();
	float maxY();
	float minY();
	static const int R;

private:
	float scale;
	float zoom;
	sf::Vector2f topRight;
	sf::Vector2f bottomLeft;
	sf::Vector2f center;
};

