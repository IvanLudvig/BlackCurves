#pragma once
#include "Curve.h"
#include "Axis.h"
#include "Cords.h"

class Curves {
public:
	Curves();
	void update();
	void init(float A, float B, float C, float D, float E, float F);
	int getType();
private:
	Curve* curve;
	Cords* cords;
	Axis* axis;
};