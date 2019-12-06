#pragma once
#include "Figure.h"
class LineFigure :
	public Figure
{
public:
	LineFigure(Factors* factors);
	void build(Factors* factors, Cords cords) override;
};

