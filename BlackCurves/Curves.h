#pragma once
#include "Curve.h"
#include "Axis.h"
#include "Cords.h"
#include <string>

class Curves {
public:
	Curves(float A, float B, float C, float D, float E, float F);
	void update();
	void open();
	std::string getDescription();
private:
	Curve* curve;
	Cords* cords;
	Axis* axis;
};