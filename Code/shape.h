#ifndef SHAPE_H
#define SHAPE_H

struct S2d {double x; double y;}; 
struct Carre {S2d C; double d;};
struct Circle {S2d C; double r;};

namespace shape
{
	//Constante
	constexpr double epsil_zero(0.125);
	
	//Prototype
	bool colli_cercle(Circle C1, Circle C2, bool test);
	bool colli_carre(Carre S1, Carre S2,bool test);
	bool colli_carre_cercle(Carre S1, Circle C2, bool test);
}

#endif
