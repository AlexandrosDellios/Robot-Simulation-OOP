#ifndef TIMER_H
#define TIMER_H

#include <gtkmm.h>
#include <iostream>
#include <map>

class BasicTimer : public Gtk::Window
{
public:
    BasicTimer();

protected:
	// button signal handlers
	void on_button_add_timer();
	void on_button_delete_timer();
	void on_button_quit();
	
	// This is the standard prototype of the Timer callback function
	bool on_timeout();
	
	// Member data:
	Gtk::Box m_box, top_box,   bottom_box;
	Gtk::Button 	start_timer, stop_timer, quit_button;
	Gtk::Label  	text_label, data_label;
	
	// to handle a single timer
	bool timer_added; 
	// to store a single timer disconnect request
	bool disconnect; 
	
	const int timeout_value; 
};

#endif // GTKMM_BASIC_TIMER_H
