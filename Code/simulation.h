/* Projet Propre en ordre 2023
 * Leo Sierra 341942
 * Alexandros Dellios 355873
*/

#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>

#include "robot.h"
#include "particule.h"

class Simulation
{
private :
	vector<Particule> particules;
	Spatial spatial;
	vector<Reparateur> reparateurs;
	vector<Neutraliseur> neutraliseurs;
	
public :
	Simulation(vector<Particule> p, Spatial s, vector<Reparateur> r
										, vector<Neutraliseur> n) :
		particules(p), spatial(s), reparateurs(r), neutraliseurs(n){}
	
	vector<Particule>& get_particules(){return particules;};
	Spatial& get_spatial(){return spatial;};
	vector<Reparateur>& get_reparateurs(){return reparateurs;};
	vector<Neutraliseur>& get_neutraliseurs(){return neutraliseurs;};
};


void lecture(char* nom_fichier);

void sauvegarde();

#endif
