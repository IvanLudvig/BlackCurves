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
	/*
	if (B == 0) {
		if (A == 0)
		{
			if (D == 0)
			{
				if ((C != 0) && (E != 0))
				{
					float y1 = E / (2 * C);
					F -= E * E / (4 * C);
					center.y = y1;
					E = 0;
					return new Factors(A, B, C, D, E, F, angle, center);
				}
			}
		}
		if (C == 0)
		{
			if (E == 0)
			{
				if ((A != 0) && (D != 0))
				{
					float x1 = D / (2 * A);
					F -= D * D / (4 * A);
					//center.x = x1;
					D = pow(A, 0.5f);
					A = 0;
					return new Factors(A, B, C, D, E, F, angle, center);
				}
			}
		}
	}*/
	
	if (B != 0)
	{
		if (A == C)
		{
			angle = Cords::degreesToRadians(45);
		}
		else
		{
			angle = 0.5f * atan(B/(A - C));
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

		B = 2*(this->C -this->A) * sin(angle) * cos(angle);
		B += this->B*((cos(angle) * cos(angle)) - (sin(angle) * sin(angle)));
		//B = 0;
	}

	/*
	if (B != 0)
	{
		if ((D != 0) && (A != 0) && (C != 0) && (E != 0))
		{
			if (D  == (2 * F * (pow(A, 0.5f))))
			{
				D = (D / fabs(D)) * pow(A, 0.5f);
				E = (E/fabs(E))*pow(C, 0.5f);
				A = 0;
				C = 0;
				B = 0;
			}
		}
	}*/
	
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
	/*
	if (B != 0)
	{
		if ((D == 0) && (E == 0))
		{
			D = pow(abs(A), 0.5f);
			E = pow(abs(C), 0.5f);
			A = 0;
			C = 0;
			//B -= 2*D*E;
		}
	}*/

	/*
	if (F != 0)
	{
		A = A / F;
		B = B / F;
		C = C / F;
		D = D / F;
		E = E / F;

		F = 1;
	}
	*/
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
