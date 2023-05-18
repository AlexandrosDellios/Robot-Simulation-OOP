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
			neutraliseurs[i].set_goal(neutraliseurs[i].get_cercle().C);
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

bool simulation::mise_a_jour()
{
	if((sim.get_particules().size()== 0) and (sim.get_neutraliseurs().size()==0)
		and (sim.get_reparateurs().size()==0)) return 1;
	sim.ajouter_robots();
	sim.desintegration();
	sim.choix_buts_neutraliseurs();
	sim.choix_buts_reparateurs();
	sim.move_neutraliseurs();
	sim.move_reparateurs();
	sim.destroy_robot();
	sim.get_spatial().add_update();
	return 0;
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

void Simulation::destroy_robot()
{
	unsigned int updates = spatial.get_donnees().nbUpdate;
	for(size_t i = 0; i < neut.size(); i++)
	{
		if(((updates - neut[i].get_k_update()) >= max_update)
			and (neut[i].get_panne()))
		{
			swap(neut[i],neut[neut.size()-1]);
			neut.pop_back();
			spatial.update_neutraliseurs(1,0,-1);
			i--;
		}
	}
}

void Simulation::ajouter_robots()
{
	S2d centre = spatial.get_cercle().C;
	Data d = spatial.get_donnees();
	if((d.nbUpdate % modulo_update) != 0) return;
	if((parti.size() > size_t(4* d.nbNs)) and (d.nbNr > 0)) 
	{
		Neutraliseur n(centre.x, centre.y,r_neutraliseur, 0,d.nbNs%3,false,0);
		neut.push_back(n);
		if(detect_colli(n)) neut.pop_back();
		else spatial.update_neutraliseurs(0,-1,0);
	}
	if((neut.size() > size_t(3* d.nbRs)) and (d.nbRr > 0)) 
	{
		Reparateur r(centre.x, centre.y,r_reparateur);
		rep.push_back(r);
		if(detect_colli(r)) rep.pop_back();
		else spatial.update_reparateurs(-1);
	}
}

void Simulation::choix_buts_neutraliseurs()
{
	vector<Particule> p = tri_particules(sim.get_particules());
	size_t min;
	for(size_t i=0; i < p.size(); i++)
	{
		if((i+1) > neut.size())break;
		min = i;
		for(size_t j=min; j < neut.size(); j++)
		{
			S2d distance_min = p[i].get_carre().C-neut[min].get_cercle().C;
			double time_min = shape::s2d_norm(distance_min) * vtran_max 
				+ abs(atan2(distance_min.y, distance_min.x) 
					- neut[min].get_alpha()) * vrot_max;
			S2d distance = p[i].get_carre().C-neut[j].get_cercle().C;
			double time = shape::s2d_norm(distance) * vtran_max 
				+ abs(atan2(distance.y, distance.x) 
					- neut[i].get_alpha()) * vrot_max;
			
			if(time  < time_min) min = j;
		}
		neut[min].set_goal(p[i].get_carre().C);
		swap(neut[min],neut[i]);
	}
	for(size_t i = p.size() ; i < neut.size(); i++)
	{
		neut[i].set_goal(spatial.get_cercle().C);
	}
}

void Simulation::choix_buts_reparateurs()
{
	for(size_t i=0; i < rep.size(); i++) rep[i].set_goal(rep[i].get_cercle().C);
	size_t min, k = 0;
	for(size_t i=0; i < neut.size(); i++)
	{
		if((k+1) > rep.size())break;
		if(!neut[i].get_panne()) continue;
		min = k;
		for(size_t j=min; j < rep.size(); j++)
		{
			if(shape::s2d_norm(neut[i].get_cercle().C-rep[j].get_cercle().C) <=
				shape::s2d_norm(neut[i].get_cercle().C-rep[min].get_cercle().C))
					min = j;
		}
		double distance = shape::s2d_norm(neut[i].get_cercle().C
			- rep[min].get_cercle().C);
		double max_distance = (max_update - (spatial.get_donnees().nbUpdate 
			- neut[i].get_k_update()))*vtran_max;
		if(distance > max_distance) continue;
		rep[min].set_goal(neut[i].get_cercle().C);
		swap(rep[min],rep[k]);
		k++;
	}
	Data d = spatial.get_donnees();
	for(size_t i=0; i < rep.size(); i++)
	{
		if((i*3 >= size_t(d.nbNs)) or(!parti.size() and !d.nbNp))
		{
			rep[i].set_goal(spatial.get_cercle().C);
		}
	}
}

void Simulation::move_neutraliseurs()
{
	for(size_t i=0; i < neut.size(); i ++)
	{
		if(neut[i].get_panne()) continue;
		vector<Particule> p = tri_particules(parti);
		bool alignement = false;
		Neutraliseur before = neut[i];
		before.set_collision(false);
		
		Cercle collision_zone = {before.get_cercle().C, 4.5};
		vector<Particule> temp = {};
		for(size_t j=0; j < p.size(); ++j)
		{
			temp.push_back(p[j]);
			if(shape::colli_carre_cercle(p[j].get_carre()
				,collision_zone,false))
			{

				before.set_collision(true);
				if(before.aligner_ortho(p[j].get_carre().C,p[j].get_carre().d))
				{
					temp.pop_back();
				}
				neut[i] = before;
				alignement = true;
			}
		}
		parti = temp;
		if(alignement) continue;
		
		Neutraliseur copie = before;
		copie.move_to(copie.get_goal(), copie.get_c_n());
		neut[i] = copie;
		if(detect_colli(copie)) 
		{
			before.set_collision(true);
			while(!detect_colli(before)) before.move_to(before.get_goal(), 5);
			neut[i] = before;
		}
		
		Cercle centre = {neut[i].get_cercle().C, 0};
		if((shape::colli_cercle(spatial.get_cercle(),centre,false)) 
			and (neut[i].get_goal() == spatial.get_cercle().C))
		{
			swap(neut[i],neut[neut.size()-1]);
			neut.pop_back();
			i--;
			spatial.update_neutraliseurs(0, 1, 0);
		}
	}
	
}

void Simulation::move_reparateurs()
{
	for(size_t i=0; i < rep.size(); i ++)
	{
		Reparateur before = rep[i];
		Reparateur copie = before;
		copie.move_to(copie.get_goal());
		rep[i] = copie;
		if(detect_colli(copie))
		{
			for(size_t j=0; j < neut.size(); j ++)
			if((shape::colli_cercle(neut[j].get_cercle(),rep[i].get_cercle(),false))
					and (neut[j].get_panne()))
			{
				neut[j].set_panne(false);
				spatial.update_neutraliseurs(0,0,-1);
			}
			rep[i] = before;
		}
		
		Cercle centre = {rep[i].get_cercle().C, 0};
		if((shape::colli_cercle(spatial.get_cercle(),centre,false))
			and (rep[i].get_goal() == spatial.get_cercle().C))
		{ 
			swap(rep[i],rep[rep.size()-1]);
			rep.pop_back();
			i--;
			spatial.update_reparateurs(1);
		}
	}
}

void Simulation::desintegration(){
	vector<Particule> updated_particules;
	vector<Particule> temp;
	vector<Particule> copy_particules = parti;
	double p = desintegration_rate;
	for (size_t i(0); i < copy_particules.size(); ++i)
	{
		bernoulli_distribution b(p/copy_particules.size());
		if(b(e))
		{
			temp = desintegration_particule(copy_particules[i]);
			for (auto p: temp)
			{
				updated_particules.push_back(p);
			}
			bobo_robot(copy_particules[i]);
		}
		else updated_particules.push_back(copy_particules[i]);
	}
	parti = updated_particules;
}

void Simulation::bobo_robot(Particule danger)
{
	danger.set_carre_d(danger.get_carre().d*risk_factor);
	for(size_t i=0; i < neut.size(); i++)
	{
		if(shape::colli_carre_cercle(danger.get_carre(),neut[i].get_cercle()
			,false))
		{
			neut[i].set_panne(true);
			spatial.update_neutraliseurs(0,0,1);
			neut[i].set_k_update(spatial.get_donnees().nbUpdate);
		}
	}
}


bool Simulation::detect_colli(Robot robot)
{
	if(colli_neut(robot)) return true;
	if(colli_rep(robot)) return true;
	if(colli_parti(robot)) return true;
	return false;
}

bool Simulation::colli_neut(Robot robot)
{
	bool same (0);
	if(robot.get_cercle().r < 4.) same = true;
	for (size_t i(0); i < neut.size(); ++i)
	{
		if ((neut[i].get_cercle().C.x == robot.get_cercle().C.x) and
		(neut[i].get_cercle().C.y == robot.get_cercle().C.y))
		{
			if (same == 1) return true;
			else same = 1;
		}
		else if(shape::colli_cercle(robot.get_cercle(), neut[i].get_cercle(), false))
		{
			return true;
		}
	}
	return false;
}
bool Simulation::colli_rep(Robot robot)
{
	bool same (0);
	if(robot.get_cercle().r > 2.) same = true;
	for (size_t i(0); i<rep.size(); ++i)
	{
		if ((rep[i].get_cercle().C.x == robot.get_cercle().C.x) 
			and (rep[i].get_cercle().C.y == robot.get_cercle().C.y))
		{
			if (same == 1) return true;
			else same = 1;
		}
		else if(shape::colli_cercle(robot.get_cercle(), rep[i].get_cercle(), false))
		{
			return true;
		}
	}	
	return false;
}
bool Simulation::colli_parti(Robot robot)
{
	for (size_t i(0); i < parti.size(); ++i)
	{
		if(shape::colli_carre_cercle(parti[i].get_carre(),robot.get_cercle(), false))
		{
			return true;
		}
	}
	return false;
}

