/* Projet Propre en ordre 2023
 * Leo Sierra 341942
 * Alexandros Dellios 355873
*/

#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include <random>

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
	default_random_engine e;
	
public :
	Simulation(vector<Particule> p, Spatial s, vector<Reparateur> r
				, vector<Neutraliseur> n, string f, default_random_engine e) :
		particules(p), spatial(s), reparateurs(r),neutraliseurs(n),filename(f)
		,e(e){}
	
	vector<Particule>& get_particules(){return particules;};
	Spatial& get_spatial(){return spatial;};
	vector<Reparateur>& get_reparateurs(){return reparateurs;};
	vector<Neutraliseur>& get_neutraliseurs(){return neutraliseurs;};
	string get_filename(){return filename;};
	default_random_engine get_e();
	void set_particules(vector<Particule> p);
};

namespace simulation
{
	void lecture(char* nom_fichier);
	void sauvegarde();
	void mise_a_jour();
	Data update_data(int nbupdates, int& p);
	void draw_all_Robots();
	void boom();
}

#endif
