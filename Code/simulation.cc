#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

#include <vector> // a enlever

#include "simulation.h"
#include "robot.h"
#include "particule.h"
#include "shape.h"

using namespace std;

struct Spatial{
	double x,y;
	int nbUpdate, nbNr, nbNs, nbNd, nbRr, nbRs;
	vector<vector<int>> particules;
};

class Simulation{
	
public:
	
private:
	int nbP, nbNr, nbNs, nbNd, nbRr, nbRs, nbUpdate;
};
	
void lecture_lignes(int n, int type, ifstream& fichier, Spatial &spatial)
{
	if(n > 100) exit(1);
	string line("#");
	int nombre;
	bool panne;
	for(int i=0; i < n; i++)
	{
		while(line[0]=='#') getline(fichier >> ws,line);
		istringstream data(line);
		
		switch (type)
		{
		case 0:
			data >> spatial.particules[i][0];
			data >> spatial.particules[i][1];
			data >> spatial.particules[i][2];
		break;
		case 1:
			cout<<"x"<<i<< endl;
			cout<<"y"<<i<< endl;
		break;
		case 2:
			cout<<"x"<<i<< endl;
			cout<<"y"<<i<< endl;
			cout<<"a"<<i<< endl;
			cout<<"c_"<<i<< endl;
			cout<<"panne"<<i<< endl;
			cout<<"k_update_panne"<<i<< endl;
		break;
		}
	}
}

void lecture(char* nom_fichier)
{
	Spatial spatial;
	
	int n, nbP;
	
	string line("#");
	ifstream fichier(nom_fichier);
	if(!fichier.fail())
	{
		getline(fichier >> ws,line);
		while(line[0]=='#') getline(fichier >> ws,line);
		istringstream data(line);
		data >> nbP;
		spatial.particules = vector<vector<int>> (nbP,vector<int>(3,0));
		lecture_lignes(nbP, 0, fichier, spatial);	
		
		line = "#";
		while(line[0]=='#') {getline(fichier >> ws,line); istringstream data(line);}
		cout << line << endl;
		data >> spatial.x;
		data >> spatial.y;
		data >> spatial.nbUpdate;
		data >> spatial.nbNr;
		data >> spatial.nbNs;
		data >> spatial.nbNd;
		data >> spatial.nbRr;
		data >> spatial.nbNs;
		cout << spatial.nbRs;
		
		lecture_lignes(spatial.nbRs, 1, fichier, spatial);
		lecture_lignes(spatial.nbNs, 2, fichier, spatial);
			
		cout << "fin de la lecture" << endl;
	}
	else cout << "erreur lecture" << endl;

}


