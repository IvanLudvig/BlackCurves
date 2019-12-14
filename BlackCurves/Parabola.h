#pragma once
#include "Figure.h"
class Parabola :
	public Figure
{
public:
	Parabola(Factors* factors);
	void build(Factors* factors, Cords cords) override;
	std::string getDescription() override;
};

