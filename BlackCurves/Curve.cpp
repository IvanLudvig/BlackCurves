#include <iostream>
#include "Curve.h"

int sgn(float x)
{
	if (x > 0)
	{
		return 1;
	}
	return -1;
}

Curve::Curve(float A, float B, float C, float D, float E, float F, Cords cords)
{
	cs = new Factors(A, B, C, D, E, F);
	//can = cs.canonic();
	float I3 = (A * ((C * F) - (E * E / 4))) 
		- ((B / 2) * ((B * F / 2) - (D * E / 4))) 
		+ ((D / 2) * ((B * E / 4) - (C * D / 2)));
	float I2 = (A * C) - (B * B / 4);
	float I1 = A + C;
	float K = (A * F) - (D * D / 4) + (C * F) - (E * E / 4);

	if (I2 > 0)
	{
		if ((I1 * I3) < 0)
		{
			type = 1;
			figure = new Ellipse(cs);
			build(cs, cords);
			return;
		}
		else if (I1 == 0)
		{
			type = 5;
		}
		else
		{
			type = 4;
		}
	}
	else if (I2 < 0)
	{
		if (I3 != 0)
		{
			type = 2;
			figure = new Hyperbola(cs);
			build(cs, cords);
			return;
		}
		else {
			type = 6;
		}
	}
	else {
		if (I3 != 0)
		{
			type = 3;
		}
		else {
			if (K > 0)
			{
				type = 9;
			}
			else if (K < 0)
			{
				type = 7;
			}
			else {
				type = 8;
			}
		}
	}

	if ((A == 0) && (B == 0) && (C == 0))
	{
		//type = 0;
		float k = D / E;
		float b = -F * 2 / E;
		std::cout << k << " " << b << std::endl;
		//fig = Line(k, b, 1.5f);
		sf::VertexArray v = sf::VertexArray(sf::LinesStrip, 2);
		v[0].position = sf::Vector2f(800, k * 800);
		v[1].position = sf::Vector2f(-800, -k * 800);
		v[0].color = sf::Color::Black;
		v[1].color = sf::Color::Black;
		//l.init(v);
	}
	else if ((A * C) > 0)
	{
		//type = 1;
	}
	else if ((A * C) < 0)
	{
		//type = 2;
	}
	else
	{
		//type = 3;
	}
	build(cs, cords);
}

Curve::Curve(int a, int b, int type)
{
}


void Curve::build(Factors* c, Cords cords)
{
	if (type == 1)
	{
		figure->build(cs, cords);
		return;
	}
	sf::VertexArray v1, v2, v3, v4;

	if ((type == 1) || (type == 3) || (type==7))
	{
		v1 = sf::VertexArray(sf::LinesStrip, 1001);
		v2 = sf::VertexArray(sf::LinesStrip, 1001);
	}
	else if ((type == 2)||(type==6))
	{
		v1 = sf::VertexArray(sf::LinesStrip, 1001);
		v2 = sf::VertexArray(sf::LinesStrip, 1001);
		v3 = sf::VertexArray(sf::LinesStrip, 1001);
		v4 = sf::VertexArray(sf::LinesStrip, 1001);
	}
	int i = 0;
	int t = 0;
	int k = 0;

	float rangeMin = c->toLocal(sf::Vector2f(cords.minX(), cords.minY())).x;
	float rangeMax = c->toLocal(sf::Vector2f(cords.maxX(), cords.maxY())).x;
	if (rangeMin > rangeMax)
	{
		float t = rangeMin;
		rangeMin = rangeMax;
		rangeMax = t;
	}
	//rangeMax = cords.maxX();
	//rangeMin = cords.minX();
	for (float x = rangeMin; x < rangeMax; x += (rangeMax - rangeMin) / (500.0f))
	{
		float a = c->C;
		float b = (c->B * x) + c->E;
		float C = c->F + (c->A * x * x) + (c->D * x);
		float D2 = (b * b) - (4 * a * C);
		//std::cout << x <<" " << D2 << std::endl;
		if (D2 >= 0)
		{
			float y1 = (-b + sqrt(D2)) / (2 * a);
			float y2 = (-b - sqrt(D2)) / (2 * a);
			if (type == 2)
			{
				if (t == 0)
				{

					v1[i].position = sf::Vector2f(cords.toWorldCords(c->toReal(sf::Vector2f(x, y1))));
					v2[i].position = sf::Vector2f(cords.toWorldCords(c->toReal(sf::Vector2f(x, y2))));
					v1[i].color = sf::Color::Black;
					v2[i].color = sf::Color::Black;
					i++;
				}
				else {
					v3[k].position = sf::Vector2f(cords.toWorldCords(c->toReal(sf::Vector2f(x, y1))));
					v4[k].position = sf::Vector2f(cords.toWorldCords(c->toReal(sf::Vector2f(x, y2))));
					v3[k].color = sf::Color::Black;
					v4[k].color = sf::Color::Black;
					k++;
				}
			}
			else {
				v1[i].position = sf::Vector2f(cords.toWorldCords(c->toReal(sf::Vector2f(x, y1))));
				v2[i].position = sf::Vector2f(cords.toWorldCords(c->toReal(sf::Vector2f(x, y2))));
				v1[i].color = sf::Color::Black;
				v2[i].color = sf::Color::Black;
				i++;
			}

			//std::cout << x << " " << y1<<", "<<y2 << std::endl;
		}
		else {
			t = 1;
		}
	}
	//struct lines res;
	if ((type == 1))
	{
		sf::VertexArray v = sf::VertexArray(sf::LinesStrip, (2 * i) + 1);
		for (int j = 0; j < i; j++)
		{
			v[j] = v1[j];
			//v[j + i].color = sf::Color::Black;
		}
		for (int j = 0; j < i; j++)
		{
			v[j + i] = v2[i - j - 1];
			//v[j + i].color = sf::Color::Black;
		}
		if (abs(v1[0].position.y - v[(2 * i) - 1].position.y) < 10)
		{
			v[2 * i] = v1[0];
		}
		else
		{
			v[2 * i] = v[(2 * i) - 1];
		}
		v[(2 * i)] = v1[0];
		vert1 = v;


	}
	else if (type == 2)
	{
		sf::VertexArray v = sf::VertexArray(sf::LinesStrip, 2 * i);
		for (int j = 0; j < i; j++)
		{
			v[j] = v1[j];
			//v[j + i].color = sf::Color::Black;
		}
		for (int j = 0; j < i; j++)
		{
			v[j + i] = v2[i - j - 1];
			//v[j + i].color = sf::Color::Black;
		}

		//v[(2 * i)] = v1[(2 * i) - 1];
		vert1 = v;
		/*
		for (int j = 0; j < 2*i; j++)
		{
			std::cout <<"vert1:"<< vert1[j].position.x << " " << vert1[j].position.y << std::endl;
		}*/
		//std::cout << "END"<<std::endl;
		v.clear();
		v = sf::VertexArray(sf::LinesStrip, 2 * k);
		for (int j = 0; j < k; j++)
		{
			v[j] = v3[k - j - 1];
			//v[j + i].color = sf::Color::Black;
		}
		for (int j = 0; j < k; j++)
		{
			v[j + k] = v4[j];
			//v[j + i].color = sf::Color::Black;
		}
		//v[(2 * k)] = v3[0];
		vert2 = v;
		/*
		for (int j = 0; j < k*2; j++)
		{
			std::cout<<"vert 2:" << vert2[j].position.x << " " << vert2[j].position.y << std::endl;
		}*/
	}
	else if (type == 3) {
		sf::VertexArray v = sf::VertexArray(sf::LinesStrip, 2 * i);
		for (int j = 0; j < i; j++)
		{
			v[j] = v1[i - j - 1];
			//v[j + i].color = sf::Color::Black;
		}
		for (int j = 0; j < i; j++)
		{
			v[j + i] = v2[j];
			//v[j + i].color = sf::Color::Black;
		}


		vert1 = v;
	}
}


void Curve::draw(sf::RenderWindow& window)
{
	figure->draw(window);
}


void Curve::update(Cords cords)
{
	figure->update(cords);
}

int Curve::getType()
{
	return type;
}


