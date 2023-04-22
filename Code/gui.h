#ifndef GUI_H
#define GUI_H

#include <gtkmm.h>

class Fenetre : public Gtk::Window
{
public:
	Fenetre();

protected:

	//Button Signal handlers:
	void on_button_clicked_exit();
	void on_button_clicked_open();
	void on_button_clicked_save();
	void on_button_clicked_start();
	void on_button_clicked_step();
	void on_file_dialog_response(int response_id,
								Gtk::FileChooserDialog* dialog);
	
	//keyboard event
    bool on_window_key_pressed(guint keyval, guint keycode, 
								Gdk::ModifierType state);
	
	//Frames
	Gtk::Frame Frame_Buttons, Frame_Infos;
	
	//Boxes
	Gtk::Box Main_Box, Infos_Box, Label_Box, Data_Box, UI_Box, Buttons_Box, 
		Simulation_Box;
	
	//Buttons
	Gtk::Button Button_Exit, Button_Open, Button_Save, Button_Start,
		Button_Step;
		
	//Labels
	Gtk::Label  data_maj, data_particules, data_nbNr, data_nbNs, data_nbNd, 
		data_nbRr, data_nbRs, data_nbNp, data_label;
	
	bool keyb_driven_state; 
	
	void create_boxes();
	
	// button signal handlers
	void on_button_add_timer();
	void on_button_delete_timer();
	void on_button_quit();
	
	// This is the standard prototype of the Timer callback function
	bool on_timeout();
	
	// to handle a single timer
	bool timer_added; 
	// to store a single timer disconnect request
	bool disconnect; 
	
	const int timeout_value; 
};

#endif

