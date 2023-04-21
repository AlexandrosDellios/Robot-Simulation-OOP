/* Projet Propre en ordre 2023
 * Leo Sierra 341942
 * Alexandros Dellios 355873
*/

#ifndef ROBOT_H
#define ROBOT_H

#include <vector>
#include <string>

#include "shape.h"
#include "particule.h"

using namespace std;

class Robot
{
private:	
	Cercle cercle ;	
protected:
	Robot(double x, double y, double r) : cercle({{x,y},r}){}
public :
	Cercle get_cercle();
};

class Reparateur : public Robot
{
private:
	S2d but;
public:
	Reparateur(double x, double y, double r) : Robot(x,y,r){}
};

class Neutraliseur : public Robot
{
private:
	double alpha;
	int c_n;
	bool panne;
	int k_update;
public:
	Neutraliseur(double x, double y, double r, double a, int c,bool p, int k) : 
		Robot(x,y,r), alpha(a), c_n(c), panne(p),k_update(k){};
};

class Spatial : public Robot
{
private:
	int nbUpdate;
	int nbNr , nbNs, nbNd;
	int nbRr , nbRs;
	int nbN;
	int nbR;
	
public:
	Spatial(double x, double y, int nbU ,int Nr, int Ns, int Nd, int Rr, 
			int Rs, double r_spatial,int N, int R) : 
		Robot(x,y,r_spatial), nbUpdate(nbU), nbNr(Nr), nbNs(Ns), nbNd(Nd), 
		nbRr(Rr), nbRs(Rs), nbN(N), nbR(R){}
		
	int getupdatemax();
};

void lecture_robot_reparateur(vector<Particule>& particules , string line
	, vector<Reparateur>& reparateurs, vector<Neutraliseur>& neutraliseurs);
	
void lecture_robot_neutraliseur(Spatial& spatial, vector<Particule>& particules 
						, string line , vector<Reparateur>& reparateurs
						, vector<Neutraliseur>& neutraliseurs);
						
void verification_robots(vector<Particule>& particules, Cercle c, bool type
		, vector<Reparateur>& reparateurs, vector<Neutraliseur>& neutraliseurs);
		//le type de robot représente neutraliseur : 1 et réparateur : 0

void verification_spatial(Spatial &spatial, vector<Particule> &particules);

#endif
