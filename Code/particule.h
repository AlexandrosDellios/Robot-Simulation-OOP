#ifndef PARTICULE_H
#define PARTICULE_H

#include "shape.h"
#include <string>
#include <vector>
using namespace std;

class Particule{
private:
	Carre square;
public:
	Particule(double x, double y, double d) : square({{x,y},d}){}
	
	Carre get_carre();
	
};

Particule lecture_particule(vector<Particule>& particules, string line);

void verification_particule(vector<Particule>& particules, Particule p);


#endif
