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
	vector<Particule> parti;
	Spatial spatial;
	vector<Reparateur> rep;
	vector<Neutraliseur> neut;
	string filename;
	
public :
	Simulation(vector<Particule> p, Spatial s, vector<Reparateur> r
				, vector<Neutraliseur> n, string f) :
		parti(p), spatial(s), rep(r),neut(n),filename(f){}
	
	vector<Particule>& get_particules(){return parti;};
	Spatial& get_spatial(){return spatial;};
	vector<Reparateur>& get_reparateurs(){return rep;};
	vector<Neutraliseur>& get_neutraliseurs(){return neut;};
	string get_filename(){return filename;};
	default_random_engine get_e();
	
	void desintegration();
	bool detect_colli(Robot robot);
	bool colli_neut(Robot robot);
	bool colli_rep(Robot robot);
	bool colli_parti(Robot robot);
	
	void choix_buts_neutraliseurs();
	void choix_buts_reparateurs();
	void move_neutraliseurs();
	void move_reparateurs();
	
	void ajouter_robots();
	void bobo_robot(Particule danger);
	void destroy_robot();
	
};

namespace simulation
{
	void lecture(char* nom_fichier);
	void sauvegarde(string filename);
	bool mise_a_jour();
	Data update_data(int& p);
	void draw_all_Robots();
}

#endif
