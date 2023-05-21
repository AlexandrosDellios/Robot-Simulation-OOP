/* Projet Propre en ordre 2023
 * particule.h
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
	void set_carre_d(double a);
};

bool lecture_particule(vector<Particule>& particules, string line);

bool verification_particule(vector<Particule>& particules, Particule p);
void draw_particule(vector<Particule>& particules);
vector<Particule> desintegration_particule(Particule particule);
vector<Particule> tri_particules(vector<Particule> p);


#endif
