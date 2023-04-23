/* Projet Propre en ordre 2023
 * Leo Sierra 341942
 * Alexandros Dellios 355873
*/

#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <iostream>

#include "simulation.h"
#include "robot.h"
#include "particule.h"
#include "constante.h"
#include "shape.h"
#include "message.h"

using namespace std;
Spatial sp(0, 0, 0,0, 0, 0, 0, 0, 0,0, 0);
Simulation sim({}, sp, {}, {},"");
Simulation* p_sim(&sim);
void simulation::lecture(char* nom_fichier)
{
	vector<Particule> particules;
	vector<Reparateur> reparateurs;
	vector<Neutraliseur> neutraliseurs;
	int x,y,nbUpdate, nbNr, nbNs, nbNd, nbRr, nbRs; //variables tmp spatial
	int nbP;
	string line;
	
	ifstream fichier(nom_fichier);
	if(!fichier.fail())
	{
		do{getline(fichier >> ws,line);}while(line[0]=='#'); // lecture nombre particule
		istringstream data(line);
		data >> nbP;
		
		for(int i(0); i < nbP; i++)	//lecture données particules
		{
			do{getline(fichier >> ws,line);} while(line[0]=='#');
			particules.push_back(lecture_particule(particules, line));
		}
		
		do{getline(fichier >> ws,line);} while(line[0]=='#'); //lecture robot spatial
		data.str(line); data.clear();	//changement de string de data et reset des flags error
		
		data >> x; data >> y; data >> nbUpdate; data >> nbNr; data >> nbNs;
		data >> nbNd; data >> nbRr; data >> nbRs;
		Spatial spatial(x,y ,nbUpdate, nbNr, nbNs, nbNd, nbRr, nbRs,
						r_spatial ,nbNr+nbNs+nbNd, nbRr + nbRs);
		verification_spatial(spatial, particules);
		
		for(int i(0); i < nbP; i++)	//lecture données robots reparateurs
		{
			do{getline(fichier >> ws,line);} while(line[0]=='#');
			lecture_robot_reparateur(particules,line,reparateurs,neutraliseurs);
		}
		
		for(int i(0); i < nbP; i++)	//lecture données robots neutraliseurs
		{
			do{getline(fichier >> ws,line);} while(line[0]=='#');
			lecture_robot_neutraliseur(spatial, particules, line 
										,reparateurs, neutraliseurs);
		}
		
		Simulation sim_copy(particules, spatial, reparateurs, neutraliseurs,
						nom_fichier);
		sim = sim_copy;
		p_sim = &sim;
		cout << message::success();
	}
	else
	{
		cerr << "erreur dans l'ouverture du fichier" << endl;
	}
	
}

void simulation::sauvegarde()
{
	ofstream file(p_sim->get_filename());
	if (file.is_open())
	{
		file << "# " << "" << "\n#\n# nombre de particules puis les "
		<< "données d'une particule par ligne\n" << "nbP" << "\n";
		for(size_t i=0; i < (p_sim->get_particules()).size(); i++) 
		{
			file << "   " << " x" << i << " y" << i << " d" << i << "\n";
		}
		file << "\n# données du robot spatial\n" << "x" << " " << "y" << " "
			 << "nbUpdate" << " " << "nbNr" << " " << "nbNs" << " " << "nbNd"
			 << " " << "nbRr" << " " << "nbRs" << "\n\n" << "# données des nbRs"
			 << "robots réparateurs en service (un par ligne)\n";
		for(size_t i=0; i < 5; i++) 
		{
			file << "   " << "x" << i << " y" << i << "\n";
		}
		file << "\n# données des nbNs"
			 << "robots neutraliseurs en service (un par ligne)\n";
		for(size_t i=0; i < 5; i++) 
		{
			file << "   " << "x" << i << " y" << i << " a" << i << " c_" << i
				 << " panne" << i << " k_update_panne" << i << "\n";
		}
		file.close();
		cout << "Sauvegarde reussie" << endl;
	}
	else cerr << "erreur dans l'ouverture du fichier" << std::endl;
}

void simulation::mise_a_jour();

Data simulation::get_data()
{
	Data data = {3,3,1,3,0,2,1};
	
	return data;
}
default_random_engine Simulation::get_e(){return e;};

void simulation::draw_all_Robots(){
	draw_Robot(p_sim->get_reparateurs(),(p_sim->get_reparateurs()).size());
	draw_Robot(p_sim->get_neutraliseurs(),(p_sim->get_neutraliseurs()).size());
	draw_Robot(p_sim->get_spatial());
	draw_particule(p_sim->get_particules(), (p_sim->get_particules()).size());
}

void simulation::boom(){
	vector<Particule> new_parti;
	vector<Particule> temp_parti;
	double p = desintegration_rate;
	for (size_t i(0); i < p_sim->get_particules().size(); ++i){
		bernoulli_distribution b(p/p_sim->get_particules().size());
		default_random_engine e = p_sim->get_e();
		if (p_sim->get_particules()[i].get_carre().d > d_particule_min + shape::epsil_zero){
			if (b(e)){
				p_sim->get_particules().erase(p_sim->get_particules().begin()+i);
				temp_parti = desintegration(p_sim->get_particules()[i]);
				for (auto i: temp_parti){
					new_parti.push_back(i);
				}
			}
		}
	}
	for (auto i: new_parti){
		p_sim->get_particules().push_back(i);
	}
}


