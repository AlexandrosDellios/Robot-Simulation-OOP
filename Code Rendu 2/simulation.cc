/* Projet Propre en ordre 2023
 * simulation.cc
 * Leo Sierra 341942
 * Alexandros Dellios 355873
 * Leo : 80%
 * Alexandros : 20%
*/

#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <random>

#include "simulation.h"
#include "robot.h"
#include "particule.h"
#include "constante.h"
#include "shape.h"
#include "message.h"

using namespace std;
static default_random_engine e;
static Spatial sp(0,0,0,0,0,0,0,0,0,0);
static Simulation sim({}, sp, {}, {},"");//Instance globale simulation accessible par tout le module simulation

void simulation::lecture(char* nom_fichier)
{
	//Variables temporaires de construction
	vector<Particule> particules{};
	vector<Reparateur> reparateurs{};
	vector<Neutraliseur> neutraliseurs{};
	int x,y,nbUpdate, nbNr, nbNs, nbNd, nbNp(0), nbRr, nbRs, nbP;
	string line;
	Spatial sp_vide(0,0,0,0,0,0,0,0,0,0);
	static Simulation sim_vide({}, sp, {}, {},"");
	sim = sim_vide; //Reset la simulation en cas de detection d'erreur
	
	ifstream fichier(nom_fichier);
	if(!fichier.fail())
	{
		do{getline(fichier >> ws,line);}while(line[0]=='#'); // lecture nombre particule
		istringstream data(line);
		data >> nbP;
		
		for(int i(0); i < nbP; i++)	//lecture données particules
		{
			do{getline(fichier >> ws,line);} while(line[0]=='#');
			if(lecture_particule(particules, line))return;
		}
		
		
		do{getline(fichier >> ws,line);} while(line[0]=='#'); //lecture robot spatial
		data.str(line); data.clear();	//changement de string de data et reset des flags error
		
		data >> x; data >> y; data >> nbUpdate; data >> nbNr; data >> nbNs;
		data >> nbNd; data >> nbRr; data >> nbRs;
		
		Spatial temp(x,y,r_spatial ,nbUpdate, nbNr, nbNs, nbNd, 0, nbRr, nbRs);
		if(verification_spatial(temp, particules)) return;
		
		for(int i(0); i < nbRs; i++)	//lecture données robots reparateurs
		{
			do{getline(fichier >> ws,line);} while(line[0]=='#');
			if(lecture_robot_reparateur(particules,line,reparateurs
				,neutraliseurs)) return;
		}
		
		for(int i(0); i < nbNs; i++)	//lecture données robots neutraliseurs
		{
			do{getline(fichier >> ws,line);} while(line[0]=='#');
			if(lecture_robot_neutraliseur(temp, particules, line 
				,reparateurs, neutraliseurs)) return;
		}
		
		for(size_t i=0; i < neutraliseurs.size(); i++)
		{
			if(neutraliseurs[i].get_panne()) nbNp++;
		}
		Spatial spatial(x,y,r_spatial ,nbUpdate, nbNr, nbNs, nbNd, nbNp, nbRr
						, nbRs);
		
		e.seed(1);
		Simulation nouvelle_sim(particules, spatial, reparateurs, neutraliseurs,
						nom_fichier);
		sim = nouvelle_sim;
		cout << message::success();
	}
	else
	{
		cerr << "erreur dans l'ouverture du fichier" << endl;
	}
}

void simulation::sauvegarde(string filename)
{
	ofstream file(filename);
	vector<Particule> p = sim.get_particules();
	vector<Reparateur> r = sim.get_reparateurs();
	vector<Neutraliseur> n = sim.get_neutraliseurs();
	Data d = sim.get_spatial().get_donnees();
	S2d s_centre = sim.get_spatial().get_cercle().C;
	if (!file.is_open()) return;
	string name = filename.substr(filename.find_last_of("/\\") + 1); //gets end name of file without path
	file << "# " << name << "\n#\n# nombre de particules puis les "
	<< "données d'une particule par ligne\n" << p.size() << "\n";
	for(size_t i=0; i < p.size(); i++) 
	{
		file << "   " << p[i].get_carre().C.x  << " " 
			 << p[i].get_carre().C.y << " " << p[i].get_carre().d << "\n";
	}
	file << "\n# données du robot spatial\n" << s_centre.x << " " << s_centre.y 
		 << " "  << d.nbUpdate << " " << d.nbNr << " " << d.nbNs << " " 
		 << d.nbNd << " " << d.nbRr << " " << d.nbRs << "\n\n" 
		 << "# données des nbRs robots réparateurs en service (un par ligne)\n";
	for(size_t i=0; i < r.size(); i++) 
	{
		file << "   " << r[i].get_cercle().C.x  << " " 
		<< r[i].get_cercle().C.y << " "  << "\n";
	}
	file << "\n# données des nbNs robots " 
		 << "neutraliseurs en service (un par ligne) \n";
	for(size_t i=0; i < n.size(); i++) 
	{
		file << "   " << n[i].get_cercle().C.x  << " " 
			 << n[i].get_cercle().C.y << " " << n[i].get_alpha() << " " 
			 << n[i].get_c_n() << " ";
		if(n[i].get_panne())file << "true";
		else file << "false";
		file << " " << n[i].get_k_update() << "\n";
	}
	file.close();
	cout << "sauvegarde reussie" << endl;
}

void simulation::mise_a_jour()
{
	boom();
	sim.get_spatial().add_update();
}

Data simulation::update_data(int& p)
{
	p = sim.get_particules().size();
	return sim.get_spatial().get_donnees();
}

void simulation::draw_all_Robots(){
	draw_Robot(sim.get_reparateurs(),(sim.get_reparateurs()).size());
	draw_Robot(sim.get_neutraliseurs(),(sim.get_neutraliseurs()).size());
	draw_Robot(sim.get_spatial());
	draw_particule(sim.get_particules());
}

void simulation::boom(){
	vector<Particule> updated_particules;
	vector<Particule> temp;
	vector<Particule> copy_particules = sim.get_particules();
	double p = desintegration_rate;
	for (size_t i(0); i < copy_particules.size(); ++i)
	{
		bernoulli_distribution b(p/copy_particules.size());
		if(b(e))
		{
			temp = desintegration(copy_particules[i]);
			for (auto i: temp)
			{
				updated_particules.push_back(i);
			}
		}
		else updated_particules.push_back(copy_particules[i]);
	}
	sim.set_particules(updated_particules);
}

void Simulation::set_particules(vector<Particule> p){particules = p;};
