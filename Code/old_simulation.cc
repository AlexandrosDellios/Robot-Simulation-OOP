#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

#include "simulation.h"
#include "robot.h"
#include "particule.h"
#include "shape.h"

using namespace std;


class Simulation{
	
public:
	
private:
	int nbP, nbNr, nbNs, nbNd, nbRr, nbRs, nbUpdate;
};


void lecture(char* nom_fichier)
{
	int parametre = 0, nbP, nbR, nbN;
	int nombre;
	string line;
	ifstream fichier(nom_fichier);
	if(!fichier.fail())
	{
		// l’appel de getline filtre aussi les séparateurs
		while(getline(fichier >> ws,line))
		{
			// ligne de commentaire à ignorer, on passe à la suivante
			if(line[0]=='#') continue;
			cout << "line : " << line << endl;
			istringstream data(line);
			data >> nombre;
			cout << "nombre " << nombre << endl;
			
			switch (parametre){
				case 0:
					cout << "nbP = " << nombre << endl;
					nbP = nombre;
					parametre ++;
				break;
				
				case 1:
					if(nbP --)
					{
						for(int j=0; j<3; j++)
						{
							cout << nombre << ' ';
							data >> nombre;
						}
						cout << endl;
					}
					if(nbP == 0) parametre ++;
				break;
				
				case 2:
					cout << "x = " << nombre;
					data >> nombre;
					cout << ", y = " << nombre;
					data >> nombre;
					cout << ", nbUpdate = " << nombre;
					data >> nombre;
					cout << ", nbNr = " << nombre;
					data >> nombre;
					cout << ", nbNs = " << nombre;
					nbN = nombre;
					data >> nombre;
					cout << ", nbNd = " << nombre;
					data >> nombre;
					cout << ", nbRr = " << nombre;
					data >> nombre;
					nbR = nombre;
					cout << ", nbRs = " << nombre << endl;
					
					parametre ++;
				break;
				
				case 3:
					if(nbR --)
					{
						for(int j=0; j<2; j++)
						{
							cout << nombre << ' ';
							data >> nombre;
						}
						cout << endl;
					}
					else parametre ++;
				break;
				
				case 4:
					if(nbN --)
					{
						for(int j=0; j<6; j++)
						{
							cout << nombre << ' ';
							data >> nombre;
						}
						cout << endl;
					}
					else parametre ++;
				break;		
			}
			

		}
		cout << "fin de la lecture" << endl;
	}
	else cout << "erreur lecture" << endl;

}


