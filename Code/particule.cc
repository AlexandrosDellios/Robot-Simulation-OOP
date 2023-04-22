/* Projet Propre en ordre 2023
 * Leo Sierra 341942
 * Alexandros Dellios 355873
*/

#include <sstream>
#include <vector>
#include <string>
#include <iostream>

#include "particule.h"
#include "message.h"
#include "shape.h"
#include "constante.h"

using namespace std;

Particule lecture_particule(vector<Particule>& particules, string line)
{
	double x,y,d;
	istringstream data(line);
	data >> x; data >> y; data >> d;
	Particule p(x,y,d);
	verification_particule(particules, p);
	return p;
	
}

void verification_particule(vector<Particule>& particules, Particule p)
{
	Carre c = p.get_carre();
	if(c.d <= d_particule_min)
	{
		cout << message::particle_too_small(c.C.x,c.C.y,c.d);
		exit(EXIT_FAILURE);
	}
	for (size_t i(0); i<particules.size(); ++i)
	{
		Carre c2 = particules[i].get_carre();
		if (shape::colli_carre(c,c2,true))
		{
			cout << message::particle_superposition(c.C.x,c.C.y,c2.C.x,c2.C.y);
			exit(EXIT_FAILURE);
		}	
	}
	if((c.C.x+(c.d/2)>dmax) or (c.C.y+(c.d/2)>dmax) or (c.C.x-(c.d/2)<-dmax) 
							or (c.C.y-(c.d/2)<-dmax)) 
	{
		cout << message::particle_outside(c.C.x, c.C.y, c.d);
		exit(EXIT_FAILURE);
	}
}

Carre Particule::get_carre(){return carre;};

void draw_particule(vector<Particule>& particule,int nbP){
	for (int i(0); i < nbP; ++i){
		Carre c = particule[i].get_carre();
		shape::draw_parti(c.d,c.C.x,c.C.y);
	}
}



