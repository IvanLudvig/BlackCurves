#include "Factors.h"

Factors::Factors(float a, float b, float c, float d, float e, float f, float Angle, sf::Vector2f Center)
{
	A = a;
	B = b;
	C = c;
	D = d;
	E = e;
	F = f;
	angle = Angle;
	center = Center;
	transform.rotate(Cords::radiansToDegrees(angle)).translate(center);
}

Factors Factors::canonic()
{
	sf::Vector2f center(0, 0);
	float angle = 0;
	if (B != 0)
	{
		angle = 0.5 * std::atan(B / (A - C));
		A = A * std::cos(angle) * std::cos(angle);
		C = C * std::cos(angle) * std::cos(angle);

		A += C * std::sin(angle) * std::sin(angle);
		C += A * std::sin(angle) * std::sin(angle);
		A += B * std::cos(angle) * std::sin(angle);
		C -= B * std::cos(angle) * std::sin(angle);

		D = D * std::cos(angle);
		E = E * std::cos(angle);
		D += E * std::cos(angle);
		E -= D * std::sin(angle);

		B = 0;
	}
	if ((A != 0) && (D != 0))
	{
		float x1 = D / A;
		F -= (pow(x1 / 2.0f, 2) * A);
		center.x = x1 / 2.0f;
		D = 0;
	}
	if ((C != 0) && (E != 0))
	{
		float y1 = E / C;
		F -= (pow(y1 / 2.0f, 2) * C);
		center.y = y1 / 2.0f;
		E = 0;
	}
	if (F != 0)
	{
		A = A / F;
		C = C / F;
		F = 1;
	}

	return Factors(A, B, C, D, E, F, angle, center);
}

sf::Vector2f Factors::toReal(sf::Vector2f v)
{
	return transform.transformPoint(v);
}

sf::Vector2f Factors::toLocal(sf::Vector2f v)
{
	return transform.getInverse().transformPoint(v);
}
