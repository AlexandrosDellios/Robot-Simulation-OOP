/* Projet Propre en ordre 2023
 * Leo Sierra 341942
 * Alexandros Dellios 355873
*/

#include <iostream>

#include "simulation.h"

using namespace std;

// lit le fichier dont le nom est transmis sur la ligne de commande
int main(int argc, char * argv[])
{
	if(argc != 2)
	{
		cout << "pas de fichier passé pour la lecture" << endl;
		return 0;
	}
	lecture(argv[1]);

	return 0;
}


