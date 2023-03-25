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

using namespace std;

void lecture(char* nom_fichier)
{
	vector<Particule> particules;
	
	int nbP, nbNs, nbRs;
	string line("#");
	ifstream fichier(nom_fichier);
	if(!fichier.fail())
	{
		while(line[0]=='#') getline(fichier >> ws,line);
		istringstream data(line);
		data >> nbP;
		
		for(int i(0); i < nbP; i++)
		{
			getline(fichier >> ws,line);
			while(line[0]=='#') getline(fichier >> ws,line);
			istringstream data(line);
			particules.push_back(lecture_particule(particules, line));
		}

			
		cout << "fin de la lecture" << endl;
	}
	else cout << "erreur lecture" << endl;

}


