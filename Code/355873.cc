#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Structure

struct Co
{
	int x;
	int y;
};

struct Vide
{
	Co indice;
	int distance;
};

struct Chemin
{
	int cell;
	string depls;	
};

// Constante globale

const string TOO_SMALL("Error: the number of lines/columns must be greater than 2");
const string BAD_LOCATION("Error: the cell is not in the inner space of the grid");
const string OVERLAP_AB("Error: self overlap of start and end cells is not allowed");
const string OVERLAP_FULL("Error: this cell is already full");
const string OVERLAP_AB_FULL("Error: overlap of start or end cells is not allowed");
const string NO_SOLUTION("No path from start to end cells");
const int INFINIE(1e6);

//Type def

typedef vector<vector<int>> Laby;
typedef vector<Vide> LVid; 
typedef vector<Chemin> Lchem;
typedef vector<int> Vi;

//Fonction

void entree(int& nbC, int& nbL, int& nbP, Co& A, Co& B);
void affect_obs(Laby& la,Co a, Co b, int nbP, int nbL, int nbC);
void print_error(string message, bool with_cell = false, unsigned i=0, unsigned j=0);
void verification_tableau(int nbL, int nbC);
void verification_position (int nbL, int nbC, int& ligne, int& colonne);
void verification_overlap_AB (int px, int ay,int bx, int by);
void verification_overlap_AB_FULL (int px, int py,int& ligne, int& colonne);
Laby creation_tableau(int& nbL,int& nbC);
void affectation_obstacle(Laby& laby, int px, int py, int ax, int ay, int bx, int by);
void affichage_tableau(Laby& labyr, size_t ax, size_t ay, size_t bx, size_t by);
void verification_overlap_full (Laby& labyr, int px, int py);
LVid creation_lvide(Laby& labyr, int nbL, int nbC, int nbP);
Laby creation_floyd(LVid& lvide, int nbL, int nbC, int nbP);
int voisin(Co a, LVid& lvide, Co b);
Laby calcul_floyd(Laby& floyd, LVid& lvide, int nbL, int nbC);
int min(int a, int b);
int idc(LVid& lvide, int ax, int ay);
void veri_no_sol(Laby& dist, LVid& lvide, int ax, int ay, int bx, int by);
Lchem bestchem(Laby& laby, Co a ,Co b, LVid& lvide, Laby& floyd, int nbC, int nbL);
Lchem co_cell(int x, vector<int>& tdist, Lchem& path, LVid& lvide, 
				Laby& laby, string depl, int s, int nbC, int nbL);
vector<string> pathmaker(vector<Chemin>& path);
bool comparer_chemin(string L1, string L2);
vector<string> fusion(vector<string>& left, size_t N1,vector<string>& right, size_t N2);
vector<string> trifusion(vector<string> path2);
void aff_chem(vector<string>& path2);


int main()
{
	int nbC (0);int nbL (0);int nbP (0);
	Co a = {0,0};Co b = {0,0};
	//Entree du tableau
	entree(nbC, nbL, nbP, a, b);
	//Creation du tableau
	Laby la = creation_tableau(nbL, nbC);
	//Affectation des Obstacles + verifcation
	affect_obs(la,a, b,nbP, nbL, nbC);
	//Affichage du tableau 1
	affichage_tableau(la, a.x, a.y, b.x, b.y);
	//Creation tableau de cellules vides et floyd
	LVid lvide = creation_lvide(la, nbL, nbC, nbP);
	Laby floyd = creation_floyd (lvide, nbL, nbC, nbP);
	cout << endl;
	//calcul de distance
	Laby dist = calcul_floyd(floyd, lvide, nbL, nbC);
	veri_no_sol(dist, lvide, a.x, a.y, b.x, b.y);
	Lchem path = bestchem(la, a, b, lvide, dist, nbC, nbL);
	//affichage tableau resolue
	affichage_tableau(la, a.x, a.y, b.x, b.y);
	cout << endl;
	//Tri
	vector<string> path2 = pathmaker(path);
	path2 = trifusion(path2);
	//affichage des paths
	aff_chem(path2);

}

void entree(int& nbC, int& nbL, int& nbP, Co& a, Co& b)
{
	cin >> nbL >> nbC;
	verification_tableau(nbL,nbC);
	cin >> a.x >> a.y;
	verification_position(nbL,nbC,a.x, a.y);
	cin >> b.x >> b.y;
	verification_position(nbL,nbC,b.x, b.y);
	verification_overlap_AB(a.x, a.y, b.x, b.y);
	cin >> nbP;
}
	//Affectation des Obstacles + verifcation
void affect_obs(Laby& la,Co a, Co b, int nbP, int nbL, int nbC)
{
	Co p = {0,0};
	for (int i(0); i < nbP; ++i)
	{
		cin >> p.x >> p.y;
		verification_position(nbL, nbC, p.x, p.y);
		verification_overlap_AB_FULL(p.x, p.y, a.x, a.y);
		verification_overlap_AB_FULL(p.x, p.y, b.x, b.y);
		verification_overlap_full(la, p.x, p.y);
		affectation_obstacle(la, p.x, p.y, a.x, a.y, b.x, b.y);
	}
}	
	//fonction de message d'erreur
void print_error(string message, bool with_cell, unsigned i, unsigned j)
{
    cout << message ;
    
    if(with_cell) 
    {
        cout << " : ligne = " << i << " colonne = " << j ;
    }
    cout << endl;	
    exit(0);
}

	//verification de la taille du tableau
void verification_tableau(int nbL, int nbC)
{
	if ((nbC < 3) or (nbL< 3))
	{
		print_error(TOO_SMALL);
	}
}

	//verification de la position des cellules	
void verification_position (int nbL, int nbC, int& ligne, int& colonne)
{
	if ((ligne >= nbL-1) or (colonne >= nbC-1))
	{
		print_error(BAD_LOCATION, true, ligne, colonne);
	}
	if ((ligne < 1) or (colonne <1))
	{
		print_error(BAD_LOCATION, true, ligne, colonne);
	}
}
	
	//verification de l'overlap du start and end
void verification_overlap_AB (int ax, int ay,int bx, int by)
{
	if ((ax == bx) and (ay == by))
	{
		print_error(OVERLAP_AB);
	}
}
	//verification de overlap des obstacles avec start ou end
void verification_overlap_AB_FULL (int px, int py,int& ligne, int& colonne)
{
	if ((px == ligne) and (py == colonne))
	{
		print_error(OVERLAP_AB_FULL, true, ligne, colonne);
	}
}
	//verification de overlap de case deja remplie
void verification_overlap_full (Laby& labyr, int px, int py)
{
	if (labyr[px][py] == -1)
	{
		print_error(OVERLAP_FULL, true, px, py);
	}
}

	//etablir les Bordures + creer le tableau
Laby creation_tableau(int& nbC, int& nbL)
{
	Laby labyrinthe(nbC, vector<int>(nbL));
	//Bordure 1er ligne
	for (auto& i : labyrinthe[0])
	{
		i = -1;
	}
	//Bordure derniere ligne
	for (auto& i : labyrinthe[nbC-1])
	{
		i = -1;
	}
	//Bordure 1 colonne
	for (auto& i : labyrinthe)
	{
		i[0] = -1;
	}
	//Bordure derniere colonne
	for (auto& i : labyrinthe)
	{
		i[nbL-1] = -1;
	}
	return labyrinthe;	
}

	//Affectation des cellules speciales au tableau
void affectation_obstacle(Laby& labyr, int px, int py, int ax, int ay, int bx, int by)
{
	labyr[px][py] = -1;
} 

	//Affichage tu tableau initiale completé
void affichage_tableau(Laby& labyr, size_t ax, size_t ay, size_t bx, size_t by)
{
	for (size_t i(0); i < labyr.size(); ++i)
	{
		for(size_t j(0); j<labyr[i].size(); ++j)
		{
			if (j==ay and i==ax)
			{
				cout << 'A';
			}
			else if (j==by and i==bx)
			{
				cout << 'B';
			}
			else if (labyr[i][j] == -1)
			{
				cout << '#';
			}
			else if (labyr[i][j] == -3)
			{
				cout << '.';
			}
			else 
			{
				cout << ' ';
			}
		}
		cout << endl;
	}
}

	//Creation de lvide
	
LVid creation_lvide(Laby& labyr, int nbL, int nbC, int nbP)
{
	vector<Vide> lvide;
	for (int i(0); i<nbL; ++i)
	{
		for (int j(0); j<nbC; ++j)
		{
			if (labyr[i][j]!=-1)
			{
				lvide.push_back({{i,j}, -1});
			}
		}
	}
	return lvide;
}

	// verifie si deux cellules sont voisines ou pas
	
int voisin(Co a, LVid& lvide, Co b)
{
	if ((a.x == b.x) and (a.y == b.y))
	{
		return 0;
	}
	else if ((((a.x == b.x -1) or (a.x == b.x +1)) and (a.y == b.y)))
	{
		return 1; 
	}
	else if ((((a.y == b.y -1) or (a.y == b.y +1)) and (a.x == b.x)))
	{
		return 1;
	}
	else 
	{
		return INFINIE; 
	}
}

	//Initialisation du tableau de floyd
	
Laby creation_floyd(LVid& lvide, int nbL, int nbC, int nbP)
{
	int nbV ((nbL-2)*(nbC-2) - nbP);
	Laby floyd (nbV, vector<int> (nbV));
	
	for (int i(0); i<nbV; ++i)
	{
		for (int j(0); j<nbV; ++j)
		{
			floyd[i][j] = voisin(lvide[i].indice, lvide, lvide[j].indice); 
		}	
	}
	return floyd;
}

	// distance minimum 
	
int min(int a, int b)
{
	if (b < a)
	{
		return b;
	}
	else
	{
		return a;
	}
}
	// Calcul de Floyd
	
Laby calcul_floyd(Laby& floyd, LVid& lvide, int nbL, int nbC)
{	
	for (size_t k(0); k<floyd.size(); ++k)
	{
		for(size_t i(0); i<floyd.size(); ++i)
		{
			for(size_t j(0); j<floyd.size(); ++j)
			{
				floyd[i][j] = min(floyd[i][j], floyd[i][k]+floyd[k][j]);
			}
		}
	}
	return floyd;
}

	//fonction qui trouve l'indice de A et B dans le tableau de floyd
	
int idc(LVid& lvide,int ax,int ay)
{
	int pos(0);
	for (size_t h(0); h < lvide.size(); ++h)
	{
		if ((lvide[h].indice.x == ax) and (lvide[h].indice.y == ay))
		{
			pos = h;
		}
	}
	return pos;	
}
	//verification de solutions
	
void veri_no_sol(Laby& dist, LVid& lvide, int ax, int ay, int bx, int by )
{
	int a = idc(lvide, ax, ay);
	int b = idc(lvide, bx, by);
	if (dist[a][b] == INFINIE)
	{
		print_error(NO_SOLUTION);
	}
}

	//compare les cellules voisines
	
Lchem co_cell(int x, Vi& tdist, Lchem& path, LVid& lvide, 
				Laby& laby, string depl, int s, int nbC, int nbL)
{
	int distance(INFINIE); int new_cell(0); int ad_cell(0);
	char new_depl ('L');
	Co d = {lvide[x].indice.x, lvide[x].indice.y};
	//voison le plus opti
	int dx (idc(lvide, d.x+1,d.y));
	if ((laby[d.x+1][d.y] != -1) and (d.x+1 < nbL)){
		if (tdist[dx] < distance){
			distance = tdist[dx];
			new_cell = dx;
			new_depl = 'D';
		}		
	}
	int lx (idc(lvide, d.x,d.y-1));
	if ((laby[d.x][d.y-1] != -1) and (d.y-1 > 0)){
		if (tdist[lx] < distance){
			distance = tdist[lx];
			new_cell = lx;
			new_depl = 'L';
		}	
	}
	int rx (idc(lvide, d.x,d.y+1));
	if ((laby[d.x][d.y+1] != -1) and (d.y+1 < nbC)){
		if (tdist[rx] < distance){
			distance = tdist[rx];
			new_cell = rx;
			new_depl = 'R';	
		}
	}
	int ux (idc(lvide, d.x-1,d.y));
	if ((laby[d.x-1][d.y] != -1) and (d.x-1 > 0)){
		if (tdist[ux] < distance){
			distance = tdist[ux];
			new_cell = ux;
			new_depl = 'U';
		}	
	}
	// pour chemin egaux
	if ((tdist[dx] == distance) and (d.x+1 < nbL) and (laby[d.x+1][d.y] != -1)){
		if ( new_depl != 'D'){
			ad_cell = dx;
			path.push_back({ad_cell, depl+ 'D'});
			laby[d.x+1][d.y] = -3;
		}
	}
	if ((tdist[lx] == distance) and (d.y-1 > 0) and (laby[d.x][d.y-1] != -1)){
		if ( new_depl != 'L'){
			ad_cell = lx;
			path.push_back({ad_cell, depl+ 'L'});
			laby[d.x][d.y-1] = -3;
		}
	}
	if ((tdist[rx] == distance) and (d.y+1<nbC) and (laby[d.x][d.y+1] != -1)){
		if ( new_depl != 'R'){
			ad_cell = rx;
			path.push_back({ad_cell, depl+ 'R'});
			laby[d.x][d.y+1] = -3;
		}
	}
	if ((tdist[ux] == distance) and (d.x-1 > 0) and (laby[d.x-1][d.y] != -1)){
		if ( new_depl != 'U'){
			ad_cell = ux;
			path.push_back({ad_cell, depl+ 'U'});
			laby[d.x-1][d.y] = -3;
		}
	}	
	depl = depl + new_depl;
	path[s].cell = new_cell;
	path[s].depls = depl;
	laby[lvide[new_cell].indice.x][lvide[new_cell].indice.y] = -3;
	return path;
}

	//Recherche du plus court chemin
	
Lchem bestchem(Laby& laby, Co a, Co b, LVid& lvide, Laby& floyd, int nbC, int nbL)
{
	int i_start = idc(lvide, a.x, a.y);
	int i_end = idc(lvide, b.x, b.y);
	int i_cell(i_start);
	string depl("");
	vector<Chemin> path (1,{i_cell, depl});
	size_t nb_chemin (1);
	do{
		nb_chemin = path.size();
		for (size_t i(0); i<nb_chemin ; ++i)
		{
			path = co_cell(path[i].cell, floyd[i_end], path, lvide, laby, 
							path[i].depls, i, nbC-1, nbL-1);
		}
	}while((path[0].cell != i_end));
	return path;
}

	// converti le vecteur de struct chemin en vecteur de chemin

vector<string> pathmaker(vector<Chemin>& path)
{
	vector<string> path2 (path.size());
	for (size_t i(0); i<path.size(); ++i)
	{
		path2[i] = path[i].depls;
	}
	return path2;
}


	//Comparer deux chemins alphabetiquement
	
bool comparer_chemin(string l1, string l2)
{	
	for(size_t i(0); i<l1.size(); ++i)
	{
		if ((l1[i] - 0 ) > (l2[i] - 0))
		{
			return true;
		}
		else if ((l1[i] - 0 ) < (l2[i] - 0))
		{
			return false;
		}
	}
	return false;
}
	//couper la liste en deux
	
vector<string> couper(vector<string>& path2, size_t n, size_t end)
{
	vector<string> lcouper;
	for (size_t i(n); i<=end; ++i)
	{
		lcouper.push_back(path2[i]);
	}	
	return lcouper;
}

	//fusion liste
	
vector<string> fusion(vector<string>& left, size_t n1,vector<string>& right, size_t n2)
{
	size_t n = n1 + n2;
	vector<string> finale(n);
	size_t i(0),j(0),k(0);
	while (i<n1 and j<n2)
	{
		if (comparer_chemin(left[i],right[j]) == false)
		{
			finale[k] = left[i];
			i += 1;
		}
		else 
		{
			finale[k] = right[j];
			j += 1;
		}
		k+=1;
	}
	for (size_t pos(i); pos<n1; ++pos)
	{
		finale[k] = left[pos];
		k += 1;
	}
	for (size_t pos2(j); pos2<n2; ++pos2)
	{
		finale[k] = right[pos2];
		k += 1;
	}
	return finale;
}

	//Tri fusion
	
vector<string> trifusion(vector<string> path2)
{
	vector<string> left; vector<string> right;
	vector<string> new_path2 = path2;
	if (path2.size() == 1)
	{
		return new_path2;
	}
	if (path2.size() == 2)
	{
		if (comparer_chemin(path2[0],path2[1]))
		{
			string temp(path2[0]);
			new_path2[0] = path2[1];
			new_path2[1] = temp;
		}
		return new_path2;
	}
	left = trifusion(couper(path2,0,path2.size()/2));
	right = trifusion(couper(path2,path2.size()/2+1, path2.size()-1));
	
	return fusion(left,left.size(), right, right.size());
}
	
	//Affichage des chemins
	
void aff_chem(vector<string>& path2)
{
	for (auto p : path2)
	{
		cout << p << endl;
	}
}





