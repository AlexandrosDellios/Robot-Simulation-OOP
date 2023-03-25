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
	istringstream data(line);
	data >> x; data >> y;
	cout << x << " " << y << endl;
	Reparateur robot(x,y,r_reparateur);
	Circle cercle = robot.get_cercle();
	verification_robots(spatial,particules, cercle,0);
	spatial.reparateurs.push_back(robot);
}

void lecture_robot_neutraliseur(Spatial &spatial, vector<Particule>& particules, string line)
{
	int x,y,c_n,k_update_panne;
	bool panne;
	double a;
	istringstream data(line);
	data >> x; data >> y;  data >> a; data >> c_n; data >> boolalpha >> panne; data>> k_update_panne;
	cout << x << " " << y << " " << a << " " << c_n << " " << panne << " " << k_update_panne << endl;
	Neutraliseur robot(x,y,r_neutraliseur,a,c_n,panne, k_update_panne);
	Circle cercle = robot.get_cercle();
	verification_robots(spatial,particules, cercle,1);
	if(k_update_panne > spatial.getupdatemax())
	{
		cout << message ::invalid_k_update(x, y, k_update_panne, spatial.getupdatemax());
		exit(EXIT_FAILURE);
	}
	spatial.neutraliseurs.push_back(robot);
}

void verification_spatial(Spatial &spatial)
{
	Circle c = spatial.get_cercle();
	if((c.C.x+(c.r/2)>dmax) or (c.C.y+(c.r/2)>dmax) or (c.C.x-(c.r/2)<-dmax) or (c.C.y-(c.r/2)<-dmax)){
		cout << message::spatial_robot_ouside(c.C.x, c.C.y);
		exit(EXIT_FAILURE);
	}
}

void verification_robots(Spatial &spatial, vector<Particule>& particules, Circle c, bool type)
{
	for (size_t i(0); i<spatial.neutraliseurs.size(); ++i){
		Circle c2 = spatial.neutraliseurs[i].get_cercle();
		if (shape::colli_cercle(c,c2,false)){
			if(type) cout << message::repairer_neutralizer_superposition(c.C.x, c.C.y, c2.C.x, c2.C.x);
			else cout << message::neutralizers_superposition(c.C.x, c.C.y, c2.C.x, c2.C.x);
			exit(EXIT_FAILURE);
		}	
	}
	for (size_t i(0); i<spatial.reparateurs.size(); ++i){
		Circle c2 = spatial.reparateurs[i].get_cercle();
		if (shape::colli_cercle(c,c2,false)){
			if(type) cout << message::repairers_superposition(c.C.x, c.C.y, c2.C.x, c2.C.x);
			else cout << message::repairer_neutralizer_superposition(c.C.x, c.C.y, c2.C.x, c2.C.x);
			exit(EXIT_FAILURE);
		}	
	}
	for (size_t i(0); i<particules.size(); ++i){
		Carre c2 = particules[i].get_carre();
		if (shape::colli_carre_cercle(c2,c,false)){
			cout << message::particle_robot_superposition(c2.C.x, c2.C.y,c2.d, c.C.x, c.C.x,c.r);
			exit(EXIT_FAILURE);
		}	
	}
}

Circle Robot::get_cercle(){return cercle;};
int Spatial::getupdatemax(){return nbUpdate;};


