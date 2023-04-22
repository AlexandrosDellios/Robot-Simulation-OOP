/* Projet Propre en ordre 2023
 * Leo Sierra 341942
 * Alexandros Dellios 355873
*/

#ifndef PARTICULE_H
#define PARTICULE_H

#include <string>
#include <vector>
#include "shape.h"

using namespace std;

class Particule
{
private:
	Carre carre;
public:
	Particule(double x, double y, double d) : carre({{x,y},d}){}
	Carre get_carre();
};

Particule lecture_particule(vector<Particule>& particules, string line);

void verification_particule(vector<Particule>& particules, Particule p);
void draw_particule(vector<Particule>& particules,int nbP);


#endif
