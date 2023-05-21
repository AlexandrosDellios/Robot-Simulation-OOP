/* Projet Propre en ordre 2023
 * particule.cc
 * Leo Sierra 341942
 * Alexandros Dellios 355873
 * Alexandros : 50%
 * Leo : 50%
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

bool lecture_particule(vector<Particule>& particules, string line)
{
	double x,y,d;
	istringstream data(line);
	data >> x; data >> y; data >> d;
	Particule p(x,y,d);
	if(verification_particule(particules, p))return 1;
	particules.push_back(p);
	return 0;
	
}

bool verification_particule(vector<Particule>& particules, Particule p)
{
	Carre c = p.get_carre();
	if(c.d < d_particule_min)
	{
		cout << message::particle_too_small(c.C.x,c.C.y,c.d);
		return 1;
	}
	for (size_t i(0); i < particules.size(); ++i)
	{
		Carre c2 = particules[i].get_carre();
		if (shape::colli_carre(c,c2,true))
		{
			cout << message::particle_superposition(c.C.x,c.C.y,c2.C.x,c2.C.y);
			return 1;
		}	
	}
	if((c.C.x+(c.d/2)>dmax) or (c.C.y+(c.d/2)>dmax) or (c.C.x-(c.d/2)<-dmax) 
							or (c.C.y-(c.d/2)<-dmax)) 
	{
		cout << message::particle_outside(c.C.x, c.C.y, c.d);
		return 1;
	}
	return 0;
}

Carre Particule::get_carre(){return carre;};

void draw_particule(vector<Particule>& particules)
{
	for (size_t i(0); i < particules.size(); ++i)
	{
		Carre c = particules[i].get_carre();
		shape::draw_parti(c.d,c.C.x,c.C.y);
	}
}

vector<Particule> desintegration_particule(Particule particule)
{
	vector<Particule> temp;
	Carre c = particule.get_carre();
	if(((c.d)/2)-2*shape::epsil_zero >= d_particule_min + shape::epsil_zero)
	{
		Particule c1 (c.C.x-((c.d)/4), c.C.y+((c.d)/4)
						, ((c.d)/2)-2*shape::epsil_zero);
		Particule c2 (c.C.x+((c.d)/4), c.C.y+((c.d)/4)
						, ((c.d)/2)-2*shape::epsil_zero);
		Particule c3 (c.C.x-((c.d)/4), c.C.y-((c.d)/4)
						, ((c.d)/2)-2*shape::epsil_zero);
		Particule c4 (c.C.x+((c.d)/4), c.C.y-((c.d)/4)
						, ((c.d)/2)-2*shape::epsil_zero);
		temp.push_back(c1);
		temp.push_back(c2);
		temp.push_back(c3);
		temp.push_back(c4);
	}
	return temp;
}

vector<Particule> tri_particules(vector<Particule> p)
{
	size_t max;
	for (size_t i = 0; i < p.size(); i++)
	{
		max = i;
		for (size_t j = max; j < p.size(); j++)
		{
			if (p[j].get_carre().d > p[max].get_carre().d)
			{
				max = j;
			}
		}
		if (max != i)
		{
			swap(p[i], p[max]);
		}
	}
	return p;
}

void Particule::set_carre_d(double a){carre.d = a;};

