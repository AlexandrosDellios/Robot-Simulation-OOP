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
	else shape::s2d_add_scaled_vector(cercle.C, pos_to_goal, vtran_max/norm*delta_t);
}

void Neutraliseur::move_to(S2d goal, int type, Neutraliseur& neut)
{
	if (alignement == false)
	{
		switch(type)
		{
			case 0:
				move_type0(goal, cercle.C, alpha);
			break;
			case 1:
				move_type1(goal,cercle.C, alpha, neut);
			break;
			case 2:
				move_type2(goal,cercle.C, alpha);
			break;
			default:
			break;
		}
	}
}

void move_type0(S2d& goal, S2d& centre, double& alpha)
{
	S2d updated_pos_to_goal = {goal.x - centre.x, goal.y - centre.y};
	double goal_a(atan2(updated_pos_to_goal.y, updated_pos_to_goal.x));
	if (goal_a != alpha)
	{
		double delta_a(goal_a - alpha);
		converti_angle(delta_a);
		if(abs(delta_a) <= vrot_max) alpha = goal_a;
		
		else if (delta_a > 0)
		{
			alpha += delta_a*vrot_max;
		}
		else if (delta_a < 0)
		{
			alpha += delta_a*vrot_max;
		}
	}
	if (goal_a == alpha)
	{
		S2d init_pos_to_goal = {goal.x -  centre.x, goal.y - centre.y};
		S2d travel_dir = {cos(alpha),sin(alpha)};
		double proj_goal = shape::s2d_prod_scal(init_pos_to_goal, travel_dir);
		
		if(abs(proj_goal) > vtran_max*delta_t)
		{
			proj_goal = ((proj_goal > 0) ? 1: -1)*vtran_max*delta_t;
		}
		shape::s2d_add_scaled_vector(centre, travel_dir,proj_goal);	
	}
}

void move_type1(S2d& goal, S2d& centre, double& alpha, Neutraliseur& neut)
{
	S2d goal_ext;
	if (centre.x >= goal.x+neut.get_d_target()/2)
	{
		goal_ext.x = goal.x+((neut.get_d_target()/2)*risk_factor)+1;
		goal_ext.y = goal.y;
	}
	if (centre.x <= goal.x-neut.get_d_target()/2)
	{
		goal_ext.x = goal.x-((neut.get_d_target()/2)*risk_factor)-1;
		goal_ext.y = goal.y;
	}
	if ((centre.x <= goal.x+neut.get_d_target()/2) 
	and (centre.x >= goal.x-neut.get_d_target()/2) 
	and (centre.y >= goal.y+neut.get_d_target()/2))
	{
		goal_ext.x = goal.x;
		goal_ext.y = goal.y+((neut.get_d_target()/2)*risk_factor)+1;
	}
	if ((centre.x <= goal.x+neut.get_d_target()/2) 
	and (centre.x >= goal.x-neut.get_d_target()/2) 
	and (centre.y <= goal.y-neut.get_d_target()/2))
	{
		goal_ext.x = goal.x;
		goal_ext.y = goal.y-((neut.get_d_target()/2)*risk_factor)-1;
	}
	move_type0(goal_ext, centre, alpha); //goal_ext determine
	if ((centre.x == goal_ext.x) and (centre.y == goal_ext.y))
	{
		neut.aligner_ortho(goal, neut.get_d_target());
	}
	move_type0(goal, centre, alpha);
}

void move_type2(S2d& goal, S2d& centre, double& alpha)
{
	S2d init_pos_to_goal = {goal.x -  centre.x, goal.y - centre.y};
	S2d travel_dir = {cos(alpha),sin(alpha)};
	double proj_goal = shape::s2d_prod_scal(init_pos_to_goal, travel_dir);
	
	if(abs(proj_goal) > vtran_max)
	{
		proj_goal = ((proj_goal > 0) ? 1: -1)*vtran_max;
	}
	shape::s2d_add_scaled_vector(centre, travel_dir,proj_goal);
	
	S2d updated_pos_to_goal = {goal.x - centre.x, goal.y - centre.y};
	double goal_a(atan2(updated_pos_to_goal.y, updated_pos_to_goal.x));
	double delta_a(goal_a - alpha);
	
	if(abs(delta_a) <= vrot_max) alpha = goal_a;
	else alpha += ((delta_a > 0) ? 1. : -1)*vrot_max;
}

void Neutraliseur::aligner_ortho(S2d goal, double d)
{
	S2d centre(cercle.C);
	alignement = true;
	if ((centre.x < (goal.x-(d/2))) and (centre.y < (goal.y+(d/2))) 
	and (centre.y > (goal.y-(d/2))))
	{
		alpha = 0;
		//rotation(goal,centre,alpha,0);
		if ((alpha > 0-epsil_alignement) and (alpha < 0+epsil_alignement))
		{
			alignement = false;
			//temp.pop_back();
		}
	}	
	if ((centre.x > (goal.x-(d/2))) and (centre.x < (goal.x+(d/2))) and (centre.y > (goal.y+(d/2))))
	{
		alpha = -M_PI/2;
		//rotation(goal,centre,alpha,-M_PI/2);
		if ((alpha > (-M_PI/2)-epsil_alignement) and (alpha < (-M_PI/2)+epsil_alignement))
		{
			alignement = false;
			//temp.pop_back();
		}
	}	

	if ((centre.x > (goal.x+(d/2))) and (centre.y < (goal.y+(d/2))) 
	and (centre.y > (goal.y-(d/2))))
	{
		alpha = M_PI;
		//rotation(goal,centre,alpha, M_PI);
		if ((alpha > M_PI-epsil_alignement) and (alpha < M_PI+epsil_alignement))
		{
			//temp.pop_back();
			alignement = false;
		}
	}	
	if ((centre.x > (goal.x-(d/2))) and (centre.x < (goal.x+(d/2))) and (centre.y < (goal.y-(d/2))))
	{
		alpha = M_PI/2;
		//rotation(goal,centre,alpha,M_PI/2);
		if ((alpha > (M_PI/2)-epsil_alignement) and (alpha < (M_PI/2)+epsil_alignement))
		{
			alignement = false;
			//temp.pop_back();
		}
	}	
}


void rotation(S2d& goal, S2d& centre, double& alpha, double new_a)
{
	double goal_a(new_a);
	double delta_a(goal_a - alpha);
	converti_angle(alpha);
	
	if(abs(delta_a) <= vrot_max*delta_t) alpha = goal_a;
	
	else if (delta_a > 0)
	{
		alpha += delta_a*vrot_max;
	}
	else if (delta_a < 0)
	{
		alpha += delta_a*vrot_max;
	}
}

void converti_angle(double& a)
{
	if(a>M_PI)
	{
		a=-M_PI+(a-M_PI);
	}
	if (a<-M_PI)
	{
		a=M_PI+(M_PI+a);
	}
}

//"getters"
Cercle Robot::get_cercle(){return cercle;};
void Spatial::add_update(){donnees.nbUpdate++;};
Data Spatial::get_donnees(){return donnees;};
double Neutraliseur::get_alpha(){return alpha;};
int Neutraliseur::get_c_n(){return c_n;};
bool Neutraliseur::get_panne(){return panne;};
void Neutraliseur::set_colision(bool etat){colision = etat;};
int Neutraliseur::get_k_update(){return k_update;};
void Neutraliseur::set_type(int a){c_n = a;};
bool Neutraliseur::get_colision(){return colision;};
void Neutraliseur::set_d_target(double d){d_target=d;};
double Neutraliseur::get_d_target(){return d_target;};
void Neutraliseur::set_alignement(bool align){alignement = align;};
double Neutraliseur::get_alignement(){return alignement;};
