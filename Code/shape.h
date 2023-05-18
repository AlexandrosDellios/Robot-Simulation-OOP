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
						bool panne, bool collision);
	void draw_robotRep(double rayon, double xc, double yc);
	void draw_robotSpa(double rayon, double xc, double yc);
	void draw_parti(double cote, double xc, double yc);
	
	double s2d_norm(S2d co);
	double s2d_prod_scal(S2d v1, S2d v2);
	void s2d_add_scaled_vector(S2d& pos, const S2d& pos_to_goal, double scaling);
}

S2d operator- (S2d p1, S2d p2);
bool operator == (S2d p1, S2d p2);

#endif
