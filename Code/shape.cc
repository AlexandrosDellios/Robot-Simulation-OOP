#include <iostream>
#include "shape.h"
#include <cmath>

using namespace std;


bool colli_cercle(circle C1, circle C2{
	double D (sqrt(pow((C2.C.x - C1.C.x),2)+pow((C2.C.y - C1.C.y),2)));
	if (D < ((r1 + r2) + epsil_zero)){
		return true;
	}
	return false;
}

bool colli_carre(S2d C1, S2d C2, double d1, double d2){
	if (((abs(C2.x - C1.x)) < ((d1/2)+(d2/2)+epsil_zero)) and 
	((abs(C2.y - C1.y)) < ((d1/2)+(d2/2)+epsil_zero))){
		return true;
	}
	return false;
}

bool colli_carre_cercle(S2d C1, double d1, S2d C2, double r2){    // colli_...cle(centre carre, d1, centre cercle, r2)
	double L(sqrt(pow(((abs(C2.x - C1.x))-(d1/2)),2)+
			pow(abs(C2.y -C1.y)-(d1/2),2)));
	if (((abs(C2.x-C1.x) > (d1/2)) and (abs(C2.y - C1.y) - (d1/2))) 
		and (L > (r2 + epsil_zero))){
		return false;
	}
	else if ((abs(C2.x - C1.x) < ((d1/2)+r2+epsil_zero)) 
			and (abs(C2.y - C1.y) < ((d1/2)+r2+epsil_zero))){
		return true;		
	}
	return false;
}
