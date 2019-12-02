#include "Factors.h"

Factors::Factors(float a, float b, float c, float d, float e, float f)
{
	A = a;
	B = b;
	C = c;
	D = d;
	E = e;
	F = f;
	transform.rotate(Cords::radiansToDegrees(0));
}

Factors::Factors(float a, float b, float c, float d, float e, float f, float Angle, sf::Vector2f Center)
{
	A = a;
	B = b;
	C = c;
	D = d;
	E = e;
	F = f;
	transform.rotate(Cords::radiansToDegrees(Angle) + 180).translate(Center);
}

Factors* Factors::toCanonic()
{
	sf::Vector2f center(0, 0);
	float angle = 0;
	float A = this->A;
	float B = this->B;
	float C = this->C;
	float D = this->D;
	float E = this->E;
	float F = this->F;

	if (B != 0)
	{
		angle = 0.5 * std::atan(B / (A - C));
		A = A * std::cos(angle) * std::cos(angle);
		C = C * std::cos(angle) * std::cos(angle);

		A += this->C * std::sin(angle) * std::sin(angle);
		C += this->A * std::sin(angle) * std::sin(angle);
		A += this->B * std::cos(angle) * std::sin(angle);
		C -= this->B * std::cos(angle) * std::sin(angle);

		D = this->D * std::cos(angle);
		E = this->E * std::cos(angle);
		D += this->E * std::sin(angle);
		E -= this->D * std::sin(angle);

		B = 0;
	}

	if (A > C)
	{
		float t = A;
		A = C;
		C = t;
		t = D;
		D = E;
		E = t;
		angle -= Cords::degreesToRadians(90 + 180);
	}

	if ((A != 0) && (D != 0))
	{
		float x1 = D / (2 * A);
		F -= D * D / (4 * A);
		center.x = x1;
		D = 0;
	}
	if ((C != 0) && (E != 0))
	{
		float y1 = E / (2 * C);
		F -= E * E / (4 * C);
		center.y = y1;
		E = 0;
	}
	if (F != 0)
	{
		//A = A / F;
		//C = C / F;
		//F = 1;
	}

	return new Factors(A, B, C, D, E, F, angle, center);
}

sf::Vector2f Factors::toReal(sf::Vector2f v)
{
	return transform.transformPoint(v);
}

sf::Vector2f Factors::toLocal(sf::Vector2f v)
{
	return transform.getInverse().transformPoint(v);
}
