/* Projet Propre en ordre 2023
 * projet.cc
 * Leo Sierra 341942
 * Alexandros Dellios 355873
*/

#include <iostream>
#include <gtkmm/application.h>

#include "simulation.h"
#include "gui.h"

using namespace std;

// lit le fichier dont le nom est transmis sur la ligne de commande
int main(int argc, char * argv[])
{
	
	if(argc != 2)
	{
		cout << "pas de fichier passé pour la lecture" << endl;
	}
	else simulation::lecture(argv[1]);
	
	auto app = Gtk::Application::create();

	return app->make_window_and_run<Fenetre>(1, argv);

}


