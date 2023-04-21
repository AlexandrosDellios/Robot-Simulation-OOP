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
	void on_file_dialog_response(int response_id,Gtk::FileChooserDialog* dialog);
	
	//keyboard event
    bool on_window_key_pressed(guint keyval, guint keycode, Gdk::ModifierType state);
	
	//Frames
	Gtk::Frame Frame_Buttons;
	Gtk::Frame Frame_Infos;
	Gtk::Frame Frame_Simulation;
	
	//Boxes
	Gtk::Box Main_Box;
	Gtk::Box Infos_Box;
	Gtk::Box UI_Box;
	Gtk::Box Buttons_Box;
	Gtk::Box Simulation_Box;
	
	//Buttons
	Gtk::Button Button_Exit;
	Gtk::Button Button_Open;
	Gtk::Button Button_Save;
	Gtk::Button Button_Start;
	Gtk::Button Button_Step;
	
	bool keyb_driven_state; 
};

#endif

