#include <iostream>
#include "shape.h"
#include <cmath>

using namespace std;


bool colli_cercle(circle C1, circle C2){
	double D (sqrt(pow((C2.C.x - C1.C.x),2)+pow((C2.C.y - C1.C.y),2)));
	if (D < ((C1.r + C2.r) + epsil_zero)){
		return true;
	}
	return false;
}

bool colli_carre(carre S1, carre S2){
	if (((abs(S2.C.x - S2.C.x)) < ((S1.d/2)+(S2.d/2)+epsil_zero)) and 
	((abs(S2.C.y - S1.C.y)) < ((S1.d/2)+(S2.d/2)+epsil_zero))){
		return true;
	}
	return false;
}

bool colli_carre_cercle(carre S1, circle C2){    // colli_...cle(centre carre, d1, centre cercle, r2)
	double L(sqrt(pow(((abs(C2.C.x - S1.C.x))-(S1.d/2)),2)+
			pow(abs(C2.C.y -S1.C.y)-(S1.d/2),2)));
	if (((abs(C2.C.x-S1.C.x) > (S1.d/2)) and (abs(C2.C.y - S1.C.y) - (S1.d/2))) 
		and (L > (C2.r + epsil_zero))){
		return false;
	}
	else if ((abs(C2.C.x - S1.C.x) < ((S1.d/2)+C2.r+epsil_zero)) 
			and (abs(C2.C.y - S1.C.y) < ((S1.d/2)+C2.r+epsil_zero))){
		return true;		
	}
	return false;
}
