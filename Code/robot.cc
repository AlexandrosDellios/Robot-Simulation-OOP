/* Projet Propre en ordre 2023
 * robot.cc
 * Leo Sierra 341942
 * Alexandros Dellios 355873
 * Alexandros : 85%
 * Leo : 15%
*/

#include <sstream>
#include <iostream>
#include <cmath>

#include "robot.h"
#include "particule.h"
#include "message.h"
#include "shape.h"
#include "constante.h"

using namespace std;

bool lecture_robot_reparateur(vector<Particule>& particules , string line
	, vector<Reparateur>& reparateurs, vector<Neutraliseur>& neutraliseurs)
{
	double x,y;
	istringstream data(line);
	data >> x; data >> y;
	Reparateur robot(x,y,r_reparateur);
	Cercle cercle = robot.get_cercle();
	if(verification_robots(particules, cercle,0, reparateurs, neutraliseurs))
	{return 1;}
	reparateurs.push_back(robot);
	return 0;
}

bool lecture_robot_neutraliseur(Spatial& spatial, vector<Particule>& particules 
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
	if(verification_robots(particules, cercle,1, reparateurs, neutraliseurs))
	{return 1;}
	if(k_update_panne > spatial.get_donnees().nbUpdate)
	{
		cout << message ::invalid_k_update(x, y, k_update_panne
											, spatial.get_donnees().nbUpdate);
		return 1;
	}
	neutraliseurs.push_back(robot);
	return 0;
}

bool verification_spatial(Spatial &spatial, vector<Particule> &particules)
{
	Cercle c = spatial.get_cercle();
	if((c.C.x+(c.r/2)>dmax) or (c.C.y+(c.r/2)>dmax) or (c.C.x-(c.r/2)<-dmax) 
		or (c.C.y-(c.r/2)<-dmax))
	{
		cout << message::spatial_robot_ouside(c.C.x, c.C.y);
		return 1;
	}
	for (size_t i(0); i<particules.size(); ++i)
	{
		Carre c2 = particules[i].get_carre();
		if (shape::colli_carre_cercle(c2,c,true))
		{
			cout << message::particle_robot_superposition(c2.C.x, c2.C.y,c2.d
															, c.C.x, c.C.y,c.r);
			return 1;
		}	
	}
	return 0;
}

bool verification_robots(vector<Particule>& particules, Cercle c, bool type
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
			return 1;
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
			return 1;
		}	
	}
	for (size_t i(0); i<particules.size(); ++i)
	{
		Carre c2 = particules[i].get_carre();
		if (shape::colli_carre_cercle(c2,c,true))
		{
			cout << message::particle_robot_superposition(c2.C.x, c2.C.y,c2.d
															, c.C.x, c.C.y,c.r);
			return 1;
		}	
	}
	return 0;
}

void draw_Robot(vector<Reparateur>& robot, int nb)
{
	for (int i(0); i < nb; ++i)
	{
		Cercle c = robot[i].get_cercle();
		shape::draw_robotRep(c.r,c.C.x, c.C.y);
	}
}

void draw_Robot(vector<Neutraliseur>& robot, int nb)
{
	for (int i(0); i < nb; ++i)
	{
		Cercle c = robot[i].get_cercle();
		double alpha = robot[i].get_alpha();
		bool panne = robot[i].get_panne();
		shape::draw_robotNeut(c.r,c.C.x, c.C.y, alpha, panne);
	}
}

void draw_Robot(Spatial& robot)
{
	Cercle c = robot.get_cercle();
	shape::draw_robotSpa(c.r,c.C.x,c.C.y);
}

void Reparateur::move_to(S2d goal)
{
	S2d pos_to_goal = {goal.x - cercle.C.x, goal.y - cercle.C.y};
	double norm(shape::s2d_norm(pos_to_goal));
	if (norm <= vtran_max) cercle.C = goal;
	else shape::s2d_add_scaled_vector(cercle.C, pos_to_goal, vtran_max/norm);
}

void Neutraliseur::move_to(S2d goal)
{
	S2d init_pos_to_goal = {goal.x -  cercle.C.x, goal.y - cercle.C.y};
	S2d travel_dir = {cos(alpha),sin(alpha)};
	double proj_goal = shape::s2d_prod_scal(init_pos_to_goal, travel_dir);
	
	if(abs(proj_goal) > vtran_max)
	{
		proj_goal = ((proj_goal > 0) ? 1: -1)*vtran_max;
	}
	shape::s2d_add_scaled_vector(cercle.C, travel_dir,proj_goal);
	
	S2d updated_pos_to_goal = {goal.x - cercle.C.x, goal.y - cercle.C.y};
	double goal_a(atan2(updated_pos_to_goal.y, updated_pos_to_goal.x));
	double delta_a(goal_a - alpha);
	
	if(abs(delta_a) <= vrot_max) alpha = goal_a;
	else alpha += ((delta_a > 0) ? 1. : -1)*vrot_max;
}


//"getters"
Cercle Robot::get_cercle(){return cercle;};
void Spatial::add_update(){donnees.nbUpdate++;};
Data Spatial::get_donnees(){return donnees;};
double Neutraliseur::get_alpha(){return alpha;};
int Neutraliseur::get_c_n(){return c_n;};
bool Neutraliseur::get_panne(){return panne;};
int Neutraliseur::get_k_update(){return k_update;};
