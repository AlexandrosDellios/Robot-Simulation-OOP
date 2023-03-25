#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

#include <vector>

#include "simulation.h"
#include "robot.h"
#include "particule.h"
#include "shape.h"
#include "constante.h"

using namespace std;

void lecture(char* nom_fichier)
{
	vector<Particule> particules;
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
			do{getline(fichier >> ws,line);}while(line[0]=='#');
			particules.push_back(lecture_particule(particules, line));
		}
		
		do{getline(fichier >> ws,line);}while(line[0]=='#'); //lecture robot spatial
		data >> x; data >> y; data >> nbUpdate; data >> nbNr; data >> nbNs;
		data >> nbNd; data >> nbRr; data >> nbRs;
		Spatial spatial(x,y,r_spatial ,nbUpdate, nbNr, nbNs, nbNd, nbRr, nbRs,
						nbNr+nbNs+nbNd, nbRr + nbRs);
		
		for(int i(0); i < nbP; i++)	//lecture données robots reparateurs
		{
			do{getline(fichier >> ws,line);}while(line[0]=='#');
			lecture_robot_reparateur(spatial, particules, line);
		}
		
		for(int i(0); i < nbP; i++)	//lecture données robots neutraliseurs
		{
			do{getline(fichier >> ws,line);}while(line[0]=='#');
			lecture_robot_neutraliseur(spatial, particules, line);
		}
		
		cout << "fin de la lecture" << endl;
	}
	else cout << "erreur lecture" << endl;
}


