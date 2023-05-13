/* Projet Propre en ordre 2023
 * shape.cc
 * Leo Sierra 341942
 * Alexandros Dellios 355873
 * ALEXANDROS : 100%
*/

#include <cmath>
#include "shape.h"
#include "graphic.h"

using namespace std;

bool shape::colli_cercle(Cercle C1, Cercle C2, bool test)
{
	double e0;
	if (test == false) e0=shape::epsil_zero;
	else e0=0;

	double D (sqrt(pow((C2.C.x - C1.C.x),2)+pow((C2.C.y - C1.C.y),2)));
	
	if (D < ((C1.r + C2.r) + e0)) return true;
	return false;
}

bool shape::colli_carre(Carre S1, Carre S2, bool test)
{
	double e0;
	if (test == false) e0=shape::epsil_zero;
	else e0=0;

	if (((abs(S2.C.x - S1.C.x)) < ((S1.d/2)+(S2.d/2)+e0)) and 
		((abs(S2.C.y - S1.C.y)) < ((S1.d/2)+(S2.d/2)+e0))) return true;
	return false;
}

bool shape::colli_carre_cercle(Carre S1, Cercle C2, bool test)
{  
	double e0;
	if (test == false) e0=shape::epsil_zero;
	else e0=0;

	double L(sqrt(pow((abs(C2.C.x - S1.C.x)-(S1.d/2)),2)+
			pow(abs(C2.C.y -S1.C.y)-(S1.d/2),2)));
	if (((abs(C2.C.x-S1.C.x) > (S1.d/2)) and (abs(C2.C.y - S1.C.y) > (S1.d/2))) 
			and (L > (C2.r + e0))) return false;
	else if ((abs(C2.C.x - S1.C.x) < ((S1.d/2)+C2.r+e0)) 
				and (abs(C2.C.y - S1.C.y) < ((S1.d/2)+C2.r+e0))) return true;		
	return false;
}

void shape::draw_robotNeut(double rayon, double xc, double yc, double alpha, 
							bool panne, bool collision)
{
	if (panne == true){
		graphic_draw_circle(rayon,xc,yc,ORANGE,UNFILLED,WHITE,1,alpha);
	}
	else if (collision == true){
		graphic_draw_circle(rayon,xc,yc,PURPLE,UNFILLED,WHITE,1,alpha);
	}
	else graphic_draw_circle(rayon,xc,yc,BLACK,UNFILLED,WHITE,1,alpha);
}

void shape::draw_robotRep(double rayon, double xc, double yc)
{
	graphic_draw_circle(rayon,xc,yc,BLACK,FILLED,GREEN,3,0);
}

void shape::draw_robotSpa(double rayon, double xc, double yc)
{
	graphic_draw_circle(rayon,xc,yc,LIGHT_BLUE,UNFILLED,WHITE,2,0);
}
void shape::draw_parti(double cote, double xc, double yc)
{
	graphic_draw_square(cote,xc,yc,RED,FILLED,GREY);
}

double shape::s2d_norm(S2d co)
{
	double norme (sqrt((co.x*co.x)+(co.y*co.y)));
	return norme;	
}

double shape::s2d_prod_scal(S2d v1, S2d v2)
{
	double scal (v1.x * v2.x + v1.y * v2.y);
	return scal;
}

void shape::s2d_add_scaled_vector(S2d& pos, const S2d& pos_to_goal, double scaling)
{
	pos.x += pos_to_goal.x * scaling;
	pos.y += pos_to_goal.y * scaling;
}

S2d operator -(S2d p1, S2d p2)
{
	S2d temp = {0.,0.};
	temp.x = p1.x - p2.x;
	temp.y = p1.y - p2.y;
	return temp;
}
