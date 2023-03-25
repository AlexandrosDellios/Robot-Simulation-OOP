#ifndef ROBOT_H
#define ROBOT_H

#include "shape.h"
#include "constante.h"
#include "particule.h"

#include <vector>
#include <string>

using namespace std;

class Robot{
private:	
	Circle cercle ;	
protected:
	Robot(double x, double y, double r) : cercle({{x,y},r}){}
public :
	Circle get_cercle();
};

class Reparateur : public Robot{
private:
	S2d but;
	double vmax = vtran_max;
public:
	Reparateur(double x, double y, double r) : Robot(x,y,r){}
};

class Neutraliseur : public Robot{
private:
	double alpha;
	int c_n;
	bool panne;
	int k_update;
public:
	Neutraliseur(double x, double y, double r, double a, int c,bool p, int k) : Robot(x,y,r), alpha(a), c_n(c), panne(p),k_update(k){};
};

class Spatial : public Robot{
private:
	int nbUpdate;
	int nbNr , nbNs, nbNd;
	int nbRr , nbRs;
	int nbN;
	int nbR;
public:
	Spatial(double x, double y, int nbU ,int Nr, int Ns, int Nd, int Rr, int Rs, double r_spatial,int N, int R) : 
		Robot(x,y,r_spatial), nbUpdate(nbU), nbNr(Nr), nbNs(Ns), nbNd(Nd), 
		nbRr(Rr), nbRs(Rs), nbN(N), nbR(R){}
	
	int getupdatemax();
	vector<Reparateur> reparateurs;
	vector<Neutraliseur> neutraliseurs;
	
};

void lecture_robot_reparateur(Spatial &spatial,vector<Particule>& particules, string line);
void lecture_robot_neutraliseur(Spatial &spatial,vector<Particule>& particules, string line);

void verification_robots(Spatial &spatial, vector<Particule>& particules, Circle cercle, bool type);
void verification_spatial(Spatial &spatial, vector<Particule> &particules);

#endif
