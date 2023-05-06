/* Projet Propre en ordre 2023
 * robot.h
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

struct Data
{
	int nbUpdate;
	int nbNr , nbNs, nbNd, nbNp;
	int nbRr , nbRs;
};

class Robot
{
protected:
	Robot(double x, double y, double r) : cercle({{x,y},r}){}
	Cercle cercle ;	
public :
	Cercle get_cercle();
	void move_to(S2d goal) {cercle.C = goal;}
};

class Reparateur : public Robot
{
public:
	Reparateur(double x, double y, double r) : Robot(x,y,r){}
	void move_to(S2d goal);
	
};

class Neutraliseur : public Robot
{
private:
	double alpha;
	int c_n;
	bool panne;
	int k_update;
public:
	Neutraliseur(double x, double y, double r, double a, int c,bool p, int k): 
		Robot(x,y,r), alpha(a), c_n(c), panne(p),k_update(k){};
	double get_alpha();
	int get_c_n();
	bool get_panne();
	int get_k_update();
	void move_to(S2d goal);
};

class Spatial : public Robot
{
private:
	Data donnees;
	
public:
	Spatial(double x, double y, double rayon, int nbU ,int Nr, int Ns, int Nd,
	 int Np, int Rr, int Rs) : 
		Robot(x,y,rayon), donnees({nbU,Nr,Ns,Nd,Np,Rr,Rs}){}
	
	void add_update();
	Data get_donnees();
	Data set_donnees();
};

bool lecture_robot_reparateur(vector<Particule>& particules , string line
	, vector<Reparateur>& reparateurs, vector<Neutraliseur>& neutraliseurs);
	
bool lecture_robot_neutraliseur(Spatial& spatial, vector<Particule>& particules 
						, string line , vector<Reparateur>& reparateurs
						, vector<Neutraliseur>& neutraliseurs);
						
bool verification_robots(vector<Particule>& particules, Cercle c, bool type
		, vector<Reparateur>& reparateurs, vector<Neutraliseur>& neutraliseurs);
		//le type de robot représente neutraliseur : 1 et réparateur : 0

bool verification_spatial(Spatial &spatial, vector<Particule> &particules);
void draw_Robot(vector<Neutraliseur>& robot,int nb);
void draw_Robot(vector<Reparateur>& robot, int nb);
void draw_Robot(Spatial& robot);

#endif
