#ifndef SHAPE_H
#define SHAPE_H



//Constante
constexpr double epsil_zero(0.125);

struct S2d {double x; double y;}; 
struct carre {S2d C; double d;};
struct circle {S2d C; double r;};

//Prototype
bool colli_cercle(circle C1, circle C2, bool test);
bool colli_carre(carre S1, carre S2,bool test);
bool colli_carre_cercle(S2d C1, double d1, S2d C2, double r2,bool test);


#endif
