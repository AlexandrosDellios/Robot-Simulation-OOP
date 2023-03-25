#ifndef ROBOT_H
#define ROBOT_H

#include "shape.h"
#include "constante.h"

class Robot{
private:	
	Circle cercle ;	
protected:
	Robot(double x, double y, double r) : cercle({{x,y},r}){}
};


class Spatial : public Robot{
private:
	int nbUpdate;
	int nbNr , nbNs, nbNd;
	int nbRr , nbRs;
	int nbN;
	int nbR;
public:
	Spatial(double x, double y, double r_spatial,int nbU ,int Nr, 
	int Ns, int Nd, int Rr, int Rs, int N, int R) : 
	Robot(x,y,r_spatial), nbUpdate(nbU), nbNr(Nr), nbNs(Ns), nbNd(Nd), 
	nbRr(Rr), nbRs(Rs), nbN(N), nbR(R){}

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
	int c_n,k_update;
	bool panne;
public:
	Neutraliseur(double x, double y, double r, double a, int c, int k) : Robot(x,y,r), alpha(a), c_n(c), k_update(k){};
};



#endif
