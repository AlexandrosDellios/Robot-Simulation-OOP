#include "robot.h"
#include "particule.h"
#include "message.h"
#include "shape.h"
#include "constante.h"

#include <sstream>
#include <iostream>

void lecture_robot_reparateur(Spatial &spatial, vector<Particule>& particules, string line)
{
	int x,y;
	cout << line << endl;
	istringstream data(line);
	data >> x; data >> y;
	Reparateur robot(x,y,r_reparateur);
	Circle cercle = robot.get_cercle();
	verification_robots(spatial,particules, cercle);
	spatial.reparateurs.push_back(robot);
}

void lecture_robot_neutraliseur(Spatial &spatial, vector<Particule>& particules, string line)
{
	int x,y,c_n,k_update_panne;
	bool panne;
	double a;
	cout << line << endl;
	istringstream data(line);
	data >> x; data >> y;  data >> a; data >> c_n; data >> panne;  data>> k_update_panne;
	Neutraliseur robot(x,y,r_neutraliseur,a,c_n,panne, k_update_panne);
	Circle cercle = robot.get_cercle();
	verification_robots(spatial,particules, cercle);
	spatial.neutraliseurs.push_back(robot);
}

void verification_robots(Spatial &spatial, vector<Particule>& particules, Circle cercle)
{
	
	
	
}

Circle Robot::get_cercle(){return cercle;};


