#ifndef PARTICULE_H
#define PARTICULE_H

#include "shape.h"

class Particule{
private:
	Carre square;
public:
	Particule(double x, double y, double d) : square({{x,y},d}){}
};



#endif
