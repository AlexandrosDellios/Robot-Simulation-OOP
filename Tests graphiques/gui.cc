#include "gui.h"
#include <iostream>

Fenetre::Fenetre():
	
	Frame_Buttons("General"),
	Frame_Infos("info : nombre de ..."),
	
	Main_Box(Gtk::Orientation::VERTICAL, 0),
	Buttons_Box(Gtk::Orientation::VERTICAL, 2),
	Infos_Box(Gtk::Orientation::VERTICAL, 2),
	
	Button_Exit("exit"), Button_Open("open"), Button_Save("save"),
	Button_Start("start"), Button_Step("step")
{
	set_title("Keyboard Events");
	set_resizable(true);
	set_child(Main_Box);
	
	Buttons_Box.set_size_request(150, -1);
	
	Main_Box.append(Frame_Buttons);
	
	Frame_Buttons.set_label_align(Gtk::Align::START);
	Frame_Buttons.set_child(Buttons_Box);
	
	Frame_Infos.set_label_align(Gtk::Align::START);
	Frame_Infos.set_child(Infos_Box);
	
	Buttons_Box.append(Button_Exit);
	Buttons_Box.append(Button_Open);
	Buttons_Box.append(Button_Save);
	Buttons_Box.append(Button_Start);
	Buttons_Box.append(Button_Step);
	
	//Handling mouse clicks on buttons
	Button_Exit.signal_clicked().connect(
		sigc::mem_fun(*this, &Fenetre::on_button_clicked_exit));
	Button_Open.signal_clicked().connect(
		sigc::mem_fun(*this, &Fenetre::on_button_clicked_open));
	Button_Save.signal_clicked().connect(
		sigc::mem_fun(*this, &Fenetre::on_button_clicked_save));
	Button_Start.signal_clicked().connect(
		sigc::mem_fun(*this, &Fenetre::on_button_clicked_start));
	Button_Step.signal_clicked().connect(
		sigc::mem_fun(*this, &Fenetre::on_button_clicked_step));

    // Handling Keyboard Events.
    auto controller = Gtk::EventControllerKey::create();
    controller->signal_key_pressed().connect(
                  sigc::mem_fun(*this, &Fenetre::on_window_key_pressed), false);
    add_controller(controller);
}

bool Fenetre::on_window_key_pressed(guint keyval, guint, Gdk::ModifierType state)
{
	switch(gdk_keyval_to_unicode(keyval))
	{
		case 's':
			on_button_clicked_start();
			return true;
		case '1':
			on_button_clicked_step();
	}
    //the event has not been handled
    return false;
}

void Fenetre::on_button_clicked_exit()
{
	hide();
}

void Fenetre::on_button_clicked_open()
{
	std::cout << "open" << std::endl;
}

void Fenetre::on_button_clicked_save()
{
	std::cout << "save" << std::endl;
}

void Fenetre::on_button_clicked_start()
{
	if(Button_Start.get_label() == "start")
	{
		Button_Start.set_label("stop");
		Button_Step.set_sensitive(false);
	}
	else 
	{
		Button_Start.set_label("start");
		Button_Step.set_sensitive(true);
	}
}

void Fenetre::on_button_clicked_step()
{
	if(Button_Step.get_sensitive()) std::cout << "step" << std::endl;
}
