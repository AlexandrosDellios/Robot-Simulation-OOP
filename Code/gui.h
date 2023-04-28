/* Projet Propre en ordre 2023
 * Leo Sierra 341942
 * Alexandros Dellios 355873
*/
#ifndef GUI_H
#define GUI_H

#include <gtkmm.h>

struct Frame // Model Framing and window parameters
{
	double xMin; // frame parameters
	double xMax;
	double yMin;
	double yMax;
	double asp;  // frame aspect ratio
	int height;  // window height
	int width;   // window width
};

class MyArea : public Gtk::DrawingArea
{
public:
	MyArea();
	virtual ~MyArea();
	
	void draw();
    void setFrame(Frame x); 
    void adjustFrame(int width, int height);

protected:
	void on_draw(const Cairo::RefPtr<Cairo::Context>& cr,int width, int height);

private:
    Frame frame;
	bool empty;
};

class Fenetre : public Gtk::Window
{
public:
	Fenetre();
protected:
	MyArea m_area;
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
	Gtk::Box Main_Box, UI_Box, Buttons_Box, Infos_Box, Label_Box, Data_Box;
	//Labels
	Gtk::Label  data_maj, data_particules, data_nbNr, data_nbNs, data_nbNd, 
		data_nbRr, data_nbRs, data_nbNp, data_label;
	//Buttons
	Gtk::Button Button_Exit, Button_Open, Button_Save, Button_Start,
		Button_Step;	
	bool keyb_driven_state; 
	// button signal handlers
	void on_button_add_timer();
	void on_button_delete_timer();
	void on_button_quit();
	//Timer handling
	bool on_timeout();
	bool timer_added; 
	bool disconnect; 
	const int timeout_value;
	
	void create_boxes();
	void update_infos();
};
#endif

