#include "Figure.h"


Figure::Figure(Factors* f)
{
	factors = f;
	canonic = Factors(f->A, f->B, f->C, f->D, f->E, f->F).toCanonic();
}
