#include "Cords.h"


const int Cords::R = 10;
const double pi = 3.14159265;

Cords::Cords()
{
	scale = 10;
	zoom = 1;
	topRight = sf::Vector2f(40, 24);
	bottomLeft = sf::Vector2f(-40, -24);
	center = sf::Vector2f(0, 0);
}

sf::Vector2f Cords::toWorldCords(sf::Vector2f v)
{
	sf::Vector2f res = (v)*scale * zoom;
	//res -= center;
	return res;
}

sf::Vector2f Cords::toLocalCords(sf::Vector2f v)
{
	sf::Vector2f res = v;
	//res += center/(scale*zoom);
	//res += center;
	res = v / (scale * zoom);
	return res;
}

float Cords::radiansToDegrees(float rad)
{
	return rad * 180 / (pi);
}
float Cords::degreesToRadians(float deg)
{
	return deg * pi / 180;
}

void Cords::setCenter(sf::Vector2f v)
{
	center = v;
}

void Cords::setScale(float newScale)
{
	scale = newScale;
}

void Cords::setZoom(float newZoom)
{
	zoom = newZoom;
}

float Cords::getZoom()
{
	return zoom;
}

float Cords::getScale()
{
	return scale;
}

float Cords::maxX()
{
	return ((topRight.x * zoom + toLocalCords(center).x));
}

float Cords::minX()
{
	return ((bottomLeft.x * zoom + toLocalCords(center).x));
}

float Cords::maxY()
{
	return ((topRight.y * zoom + toLocalCords(center).y));
}

float Cords::minY()
{
	return ((bottomLeft.y * zoom + toLocalCords(center).y));
}


