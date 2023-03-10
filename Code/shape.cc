#include <iostream>
#include "shape.h"

using namespace std;

struct S2d {double x=0. ; double y=0. ;}; //structure coordonnées

struct carre {S2d point; double longueur;};
struct circle {S2d centre; double rayon;};
