/* Projet Propre en ordre 2023
 * Leo Sierra 341942
 * Alexandros Dellios 355873
*/

#include <sstream>
#include <iostream>

#include "robot.h"
#include "particule.h"
#include "message.h"
#include "shape.h"
#include "constante.h"

void lecture_robot_reparateur(vector<Particule>& particules , string line
	, vector<Reparateur>& reparateurs, vector<Neutraliseur>& neutraliseurs)
{
	double x,y;
	istringstream data(line);
	data >> x; data >> y;
	Reparateur robot(x,y,r_reparateur);
	Cercle cercle = robot.get_cercle();
	verification_robots(particules, cercle,0, reparateurs, neutraliseurs);
	reparateurs.push_back(robot);
}

void lecture_robot_neutraliseur(Spatial& spatial, vector<Particule>& particules 
							, string line , vector<Reparateur>& reparateurs
							, vector<Neutraliseur>& neutraliseurs)
{
	double x,y,a;
	int c_n,k_update_panne;
	bool panne;
	istringstream data(line);
	data >> x; data >> y;  data >> a; data >> c_n; 
	data >> boolalpha >> panne; data>> k_update_panne;
	Neutraliseur robot(x,y,r_neutraliseur,a,c_n,panne, k_update_panne);
	Cercle cercle = robot.get_cercle();
	verification_robots(particules, cercle,1, reparateurs, neutraliseurs);
	if(k_update_panne > spatial.getupdatemax())
	{
		cout << message ::invalid_k_update(x, y, k_update_panne
											, spatial.getupdatemax());
		exit(EXIT_FAILURE);
	}
	neutraliseurs.push_back(robot);
}

void verification_spatial(Spatial &spatial, vector<Particule> &particules)
{
	Cercle c = spatial.get_cercle();
	if((c.C.x+(c.r/2)>dmax) or (c.C.y+(c.r/2)>dmax) or (c.C.x-(c.r/2)<-dmax) 
		or (c.C.y-(c.r/2)<-dmax))
	{
		cout << message::spatial_robot_ouside(c.C.x, c.C.y);
		exit(EXIT_FAILURE);
	}
	for (size_t i(0); i<particules.size(); ++i)
	{
		Carre c2 = particules[i].get_carre();
		if (shape::colli_carre_cercle(c2,c,true))
		{
			cout << message::particle_robot_superposition(c2.C.x, c2.C.y,c2.d
															, c.C.x, c.C.y,c.r);
			exit(EXIT_FAILURE);
		}	
	}
}

void verification_robots(vector<Particule>& particules, Cercle c, bool type
		, vector<Reparateur>& reparateurs, vector<Neutraliseur>& neutraliseurs)
{
	for (size_t i(0); i<neutraliseurs.size(); ++i)
	{
		Cercle c2 = neutraliseurs[i].get_cercle();
		if (shape::colli_cercle(c,c2,true))
		{
			if(type) cout << message::neutralizers_superposition(c.C.x, c.C.y
															, c2.C.x, c2.C.y);
			else cout << message::repairer_neutralizer_superposition(c.C.x
													, c.C.y, c2.C.x, c2.C.y);
			exit(EXIT_FAILURE);
		}	
	}
	for (size_t i(0); i<reparateurs.size(); ++i)
	{
		Cercle c2 = reparateurs[i].get_cercle();
		if (shape::colli_cercle(c,c2,true))
		{
			if(type) cout << message::repairer_neutralizer_superposition(c2.C.x
													, c2.C.y, c.C.x, c.C.y);
			else cout << message::repairers_superposition(c.C.x, c.C.y, c2.C.x
																	, c2.C.y);
			exit(EXIT_FAILURE);
		}	
	}
	for (size_t i(0); i<particules.size(); ++i)
	{
		Carre c2 = particules[i].get_carre();
		if (shape::colli_carre_cercle(c2,c,true))
		{
			cout << message::particle_robot_superposition(c2.C.x, c2.C.y,c2.d
															, c.C.x, c.C.y,c.r);
			exit(EXIT_FAILURE);
		}	
	}
}

Cercle Robot::get_cercle(){return cercle;};
int Spatial::getupdatemax(){return nbUpdate;};

double Neutraliseur::alpha_get(){
	return alpha;
}

bool Neutraliseur::panne_get(){
	return panne;
}

void draw_Robot(vector<Reparateur>& robot, int nb){
	for (int i(0); i < nb; ++i){
		Cercle c = robot[i].get_cercle();
		shape::draw_robotRep(c.r,c.C.x, c.C.y);
	}
}

void draw_Robot(vector<Neutraliseur>& robot, int nb){
	for (int i(0); i < nb; ++i){
		Cercle c = robot[i].get_cercle();
		double alpha = robot[i].alpha_get();
		bool panne = robot[i].panne_get();
		shape::draw_robotNeut(c.r,c.C.x, c.C.y, alpha, panne);
	}
}
void draw_Robot(Spatial& robot){
	Cercle c = robot.get_cercle();
	shape::draw_robotSpa(c.r,c.C.x,c.C.y);
}

