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
	vector<Particule> p = p_sim->get_particules();
	vector<Reparateur> r = p_sim->get_reparateurs();
	vector<Neutraliseur> n = p_sim->get_neutraliseurs();
	donnees_spatial d = p_sim->get_spatial().get_donnees();
	if (file.is_open())
	{
		file << "# " << p_sim->get_filename() 
		<< "\n#\n# nombre de particules puis les "
		<< "données d'une particule par ligne\n" << p.size() << "\n";
		for(size_t i=0; i < p.size(); i++) 
		{
			file << "   " << p[i].get_carre().C.x  << " " 
			<< p[i].get_carre().C.y << " " << p[i].get_carre().d << "\n";
		}
		file << "\n# données du robot spatial\n" 
			 << p_sim->get_spatial().get_cercle().C.x << " "
			 << p_sim->get_spatial().get_cercle().C.y << " " 
			 << d.nbUpdate << " " << d.nbNr << " " << d.nbNs << " " << d.nbNd
			 << " " << d.nbRr << " " << d.nbRs << "\n\n" << "# données des nbRs"
			 << " robots réparateurs en service (un par ligne)\n";
		for(size_t i=0; i < r.size(); i++) 
		{
			file << "   " << r[i].get_cercle().C.x  << " " 
			<< r[i].get_cercle().C.y << " "  << "\n";
		}
		file << "\n# données des nbNs"
			 << "robots neutraliseurs en service (un par ligne)\n";
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

void simulation::draw_all_Robots(){
	draw_Robot(p_sim->get_reparateurs(),(p_sim->get_reparateurs()).size());
	draw_Robot(p_sim->get_neutraliseurs(),(p_sim->get_neutraliseurs()).size());
	draw_Robot(p_sim->get_spatial());
	draw_particule(p_sim->get_particules(), (p_sim->get_particules()).size());
}

