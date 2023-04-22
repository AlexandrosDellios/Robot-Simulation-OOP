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
	string filename;
	
public :
	Simulation(vector<Particule> p, Spatial s, vector<Reparateur> r
									, vector<Neutraliseur> n, string f) :
		particules(p), spatial(s), reparateurs(r),neutraliseurs(n),filename(f){}
	
	vector<Particule>& get_particules(){return particules;};
	Spatial& get_spatial(){return spatial;};
	vector<Reparateur>& get_reparateurs(){return reparateurs;};
	vector<Neutraliseur>& get_neutraliseurs(){return neutraliseurs;};
	string get_filename(){return filename;};
};

struct Data
{
	unsigned int p, nbRs, nbRr, nbNs, nbNp, nbNd, nbNr;
};

namespace simulation
{
	void lecture(char* nom_fichier);
	void sauvegarde();
	void mise_a_jour();
	Data get_data();
}

#endif
