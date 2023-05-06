/* Projet Propre en ordre 2023
 * shape.h
 * Leo Sierra 341942
 * Alexandros Dellios 355873
*/

#ifndef SHAPE_H
#define SHAPE_H

struct S2d {double x; double y;}; 
struct Carre {S2d C; double d;};
struct Cercle {S2d C; double r;};

namespace shape
{
	//Constante
	constexpr double epsil_zero(0.125);
	
	//Prototype
	bool colli_carre(Carre S1, Carre S2,bool test);
	bool colli_cercle(Cercle C1, Cercle C2, bool test);
	bool colli_carre_cercle(Carre S1, Cercle C2, bool test);
	void draw_robotNeut(double rayon, double xc, double yc, double alpha, 
						bool panne);
	void draw_robotRep(double rayon, double xc, double yc);
	void draw_robotSpa(double rayon, double xc, double yc);
	void draw_parti(double cote, double xc, double yc);
	
}

#endif
