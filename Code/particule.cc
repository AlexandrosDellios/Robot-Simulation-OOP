#include "particule.h"
#include "message.h"
#include "shape.h"
#include "constante.h"

#include <sstream>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

Particule lecture_particule(vector<Particule>& particules, string line)
{
	int x,y,d;
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
	
	
	
}

Carre Particule ::get_carre(){return square;};



