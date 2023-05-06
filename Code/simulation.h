/* Projet Propre en ordre 2023
 * simulation.h
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
	
public :
	Simulation(vector<Particule> p, Spatial s, vector<Reparateur> r
				, vector<Neutraliseur> n, string f) :
		particules(p), spatial(s), reparateurs(r),neutraliseurs(n),filename(f){}
	
	vector<Particule>& get_particules(){return particules;};
	Spatial& get_spatial(){return spatial;};
	vector<Reparateur>& get_reparateurs(){return reparateurs;};
	vector<Neutraliseur>& get_neutraliseurs(){return neutraliseurs;};
	string get_filename(){return filename;};
	default_random_engine get_e();
	void set_particules(vector<Particule> p);
	void update_neutraliseur(Neutraliseur n, int i);
	void update_reparateur(Reparateur r, int i);
	
};

namespace simulation
{
	void lecture(char* nom_fichier);
	void sauvegarde(string filename);
	bool mise_a_jour();
	Data update_data(int& p);
	void draw_all_Robots();
	void desintegration();
}

#endif
