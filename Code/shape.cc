/* Projet Propre en ordre 2023
 * Leo Sierra 341942
 * Alexandros Dellios 355873
*/

#include <cmath>

#include "shape.h"

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
	if (((abs(C2.C.x-S1.C.x) > (S1.d/2)) and (abs(C2.C.y - S1.C.y) - (S1.d/2))) 
			and (L > (C2.r + e0))) return false;
	else if ((abs(C2.C.x - S1.C.x) < ((S1.d/2)+C2.r+e0)) 
				and (abs(C2.C.y - S1.C.y) < ((S1.d/2)+C2.r+e0))) return true;		
	return false;
}
