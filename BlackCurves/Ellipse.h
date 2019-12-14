#pragma once
#include "Figure.h"

class Ellipse :
	public Figure
{
public:
	Ellipse(Factors* factors);
	void build(Factors* factors, Cords cords) override;
	std::string getDescription() override;
};

