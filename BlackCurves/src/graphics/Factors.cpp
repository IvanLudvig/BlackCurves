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

Factors::Factors(float a, float b, float c, float d, float e, float f, float Angle, float Angle1, sf::Vector2f Center)
{
	A = a;
	B = b;
	C = c;
	D = d;
	E = e;
	F = f;
	transform.rotate(Cords::radiansToDegrees(Angle)).translate(Center).rotate(Cords::radiansToDegrees(Angle1));
}

Factors* Factors::toCanonic()
{
	sf::Vector2f center(0, 0);
	float angle = 0;
	float angle1 = 0;
	float A = this->A;
	float B = this->B;
	float C = this->C;
	float D = this->D;
	float E = this->E;
	float F = this->F;

	if (B != 0)
	{
		if (A == C)
		{
			angle = Cords::degreesToRadians(45);
		}
		else
		{
			angle = 0.5f * atan(B / (A - C));
		}

		A = A * cos(angle) * cos(angle);
		C = C * cos(angle) * cos(angle);

		A += this->C * sin(angle) * sin(angle);
		C += this->A * sin(angle) * sin(angle);
		A += this->B * cos(angle) * sin(angle);
		C -= this->B * cos(angle) * sin(angle);

		D = this->D * cos(angle);
		E = this->E * cos(angle);
		D += this->E * sin(angle);
		E -= this->D * sin(angle);

		B = 0;
	}

	if ((A != 0) && (D != 0))
	{
		float x1 = D / (2 * A);
		F -= D * D / (4 * A);
		center.x = -x1;
		D = 0;
	}
	if ((C != 0) && (E != 0))
	{
		float y1 = E / (2 * C);
		F -= E * E / (4 * C);
		center.y = -y1;
		E = 0;
	}


	if (A > C)
	{
		float t = A;
		A = C;
		C = t;
		t = D;
		D = E;
		E = t;
		angle1 = Cords::degreesToRadians(90);
	}

	if ((A == 0) && (C != 0) && (D != 0) && (E == 0) && (F == 0))
	{
		D = D / C;
		C = 1;
	}


	if (F != 0)
	{
		A = A / -F;
		B = B / -F;
		C = C / -F;
		D = D / -F;
		E = E / -F;

		F = -1;
	}

	return new Factors(A, B, C, D, E, F, angle, angle1, center);
}

sf::Vector2f Factors::toReal(sf::Vector2f v)
{
	return transform.transformPoint(v);
}

sf::Vector2f Factors::toLocal(sf::Vector2f v)
{
	return transform.getInverse().transformPoint(v);
}

std::string Factors::formatFloat(float n)
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(2) << n;
	std::string s = ss.str();
	return s;
}

std::string Factors::floatSign(float n)
{
	return n >= 0 ? "+" : "-";
}

std::string Factors::formatVector(sf::Vector2f v)
{
	return "(" + formatFloat(v.x) + ", " + formatFloat(v.y) + ")";
}

std::string Factors::formatFloatwithSign(float n)
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(2) << fabs(n);
	std::string s = floatSign(n);
	s += ss.str();
	return s;
}

std::string Factors::getCanonicalDescription(int type)
{
	std::setw(2);
	std::setprecision(5);
	std::string description = "";

	if ((type == 1) || (type == 2))
	{
		description += " x^2/" + formatFloat(1 / A) + " ";
		description += floatSign(1 / C) + " y^2/" + formatFloat(abs(1 / C)) + " ";
		description += "= " + formatFloat(-F);
	}
	else if (type == 3)
	{
		description += "y = ";
		description += "2*" + formatFloat(-D / 2) + " x";
	}

	return description;
}
