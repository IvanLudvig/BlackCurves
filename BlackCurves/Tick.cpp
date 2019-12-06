#include "Tick.h"

Tick::Tick(sf::Vector2f val, Cords cords, sf::Font& font)
{
	text.setFont(font);
	//text.rotate(180);
	text.setFillColor(sf::Color::Black);
	text.setScale(sf::Vector2f(1.0f, -1.0f));
	this->val = val;
	if ((val.x == 0) && (val.y == 0))
	{
		text.setString("0");
		line = thor::Shapes::line(sf::Vector2f(0.0f, 1.0f), sf::Color::Magenta, 1.0f);
		//line.setPosition(-center.x, -center.y);
		line.setPosition(cords.toWorldCords(val));
		//text.setPosition(-center.x, -center.y);
		text.setPosition(cords.toWorldCords(val));
	}
	else if (val.y == 0)
	{
		//line = Line(val.x, 0.5f, true);
		std::stringstream stream;
		stream << std::fixed << std::setprecision(1) << val.x;
		std::string s = stream.str();
		text.setString(s);
		line = thor::Shapes::line(sf::Vector2f(0.0f, 10.0f), sf::Color::Magenta, 1.0f);
		//line.setPosition(cords.toWorldCords(sf::Vector2f(val.x, val.y - (5 / cords.scale))));
		line.setPosition((val.x * cords.scale * cords.zoom), (val.y * cords.scale * cords.zoom) - 5);
		//text.setPosition((val.x*scale)-(text.getGlobalBounds().width/4)-center.x, (val.y*scale)-5-center.y);
		text.setPosition(cords.toWorldCords(sf::Vector2f(val.x - (text.getGlobalBounds().width / (4 * cords.scale * cords.zoom)),
			val.y - (5 / (cords.scale * cords.zoom)))));
	}
	else if (val.x == 0)
	{
		std::stringstream stream;
		stream << std::fixed << std::setprecision(1) << val.y;
		std::string s = stream.str();
		text.setString(s);
		line = Line(-10, 1.0f, 10, 1.0f);
		line = thor::Shapes::line(sf::Vector2f(10.0f, 0.0f), sf::Color::Magenta, 1.0f);
		//line.setPosition((val.x*scale)-center.x-5, (val.y*scale)-center.y);
		line.setPosition(cords.toWorldCords(sf::Vector2f(val.x - (5 / (cords.scale * cords.zoom)), val.y)));
		//text.setPosition((val.x*scale)-center.x+15, val.y*scale + (text.getGlobalBounds().height / 2)-center.y);
		text.setPosition(cords.toWorldCords(sf::Vector2f(val.x + (15 / (cords.scale * cords.zoom)),
			val.y + ((text.getGlobalBounds().height / (2 * cords.zoom * cords.scale))))));
	}
	//text.setFillColor(sf::Color::Black);
	text.setCharacterSize(12);


}


void Tick::draw(sf::RenderWindow& window)
{
	window.draw(text);
	window.draw(line);
	//line.draw(window);
}
