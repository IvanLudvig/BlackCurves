#include "Tick.h"

Tick::Tick(sf::Vector2f val, Cords cords, sf::Font& font)
{
	text.setFont(font);
	text.setFillColor(sf::Color::Black);
	text.setScale(sf::Vector2f(1.0f, -1.0f));
	this->val = val;
	if ((val.x == 0) && (val.y == 0))
	{
		text.setString("0");
		line = thor::Shapes::line(sf::Vector2f(0.0f, 1.0f), sf::Color::Magenta, 1.0f);
		line.setPosition(cords.toWorldCords(val));
		text.setPosition(cords.toWorldCords(val));
	}
	else if (val.y == 0)
	{
		std::stringstream stream;
		stream << std::fixed << std::setprecision(1) << val.x;
		std::string s = stream.str();
		text.setString(s);
		line = thor::Shapes::line(sf::Vector2f(0.0f, 10.0f), sf::Color::Magenta, 1.0f);
		line.setPosition((val.x * cords.getScale() * cords.getZoom()), (val.y * cords.getScale() * cords.getZoom()) - 5);
		text.setPosition(cords.toWorldCords(sf::Vector2f(val.x - (text.getGlobalBounds().width / (4 * cords.getScale() * cords.getZoom())),
			val.y - (5 / (cords.getScale() * cords.getZoom())))));
	}
	else if (val.x == 0)
	{
		std::stringstream stream;
		stream << std::fixed << std::setprecision(1) << val.y;
		std::string s = stream.str();
		text.setString(s);
		line = Line(-10, 1.0f, 10, 1.0f);
		line = thor::Shapes::line(sf::Vector2f(10.0f, 0.0f), sf::Color::Magenta, 1.0f);
		line.setPosition(cords.toWorldCords(sf::Vector2f(val.x - (5 / (cords.getScale() * cords.getZoom())), val.y)));
		text.setPosition(cords.toWorldCords(sf::Vector2f(val.x + (15 / (cords.getScale() * cords.getZoom())),
			val.y + ((text.getGlobalBounds().height / (2 * cords.getZoom() * cords.getScale()))))));
	}
	text.setCharacterSize(12);
}


void Tick::draw(sf::RenderWindow& window)
{
	window.draw(text);
	window.draw(line);
}
