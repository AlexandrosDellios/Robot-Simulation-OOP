#include <iostream>
#include "gui.h"
#include "simulation.h"

Fenetre::Fenetre():
	
	Frame_Buttons("General"),
	Frame_Infos("info : nombre de ..."),
	Frame_Simulation("Propre en Ordre"),
	
	Main_Box(Gtk::Orientation::HORIZONTAL, 0),
	Buttons_Box(Gtk::Orientation::VERTICAL, 1),
	Infos_Box(Gtk::Orientation::VERTICAL, 1),
	UI_Box(Gtk::Orientation::VERTICAL, 2),
	Simulation_Box(Gtk::Orientation::VERTICAL, 2),
	
	Button_Exit("exit"), Button_Open("open"), Button_Save("save"),
	Button_Start("start"), Button_Step("step")
{
	set_title("Keyboard Events");
	set_resizable(true);
	set_child(Main_Box);
	
	Buttons_Box.set_size_request(150, -1);
	
	Main_Box.append(UI_Box);
	UI_Box.append(Frame_Buttons);
	UI_Box.append(Frame_Infos);
	Main_Box.append(Simulation_Box);
	Simulation_Box.append(Frame_Simulation);
	
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
    auto dialog = new Gtk::FileChooserDialog("Please choose a file",
											Gtk::FileChooser::Action::OPEN);
	dialog->set_transient_for(*this);
	dialog->set_modal(true);
	dialog->signal_response().connect(sigc::bind(
	sigc::mem_fun(*this, &Fenetre::on_file_dialog_response),dialog));

	//Add response buttons to the dialog:
	dialog->add_button("_Cancel", Gtk::ResponseType::CANCEL);
	dialog->add_button("_Open", Gtk::ResponseType::OK);

	//Add filters, so that only certain file types can be selected:
	auto filter_text = Gtk::FileFilter::create();
	filter_text->set_name("Text files");
	filter_text->add_suffix("txt");
	dialog->add_filter(filter_text);
	

	auto filter_any = Gtk::FileFilter::create();
	filter_any->set_name("Any files");
	filter_any->add_pattern("*");
	dialog->add_filter(filter_any);

	//Show the dialog and wait for a user response:
	dialog->show();
}

void Fenetre::on_file_dialog_response(int response_id,
												Gtk::FileChooserDialog* dialog)
{
	//Handle the response:
	switch (response_id)
	{
		case Gtk::ResponseType::OK:
		{
			std::cout << "Open clicked." << std::endl;

			//Notice that this is a std::string, not a Glib::ustring.
			auto filename = dialog->get_file()->get_basename();
			std::cout << "File selected: " << filename << std::endl;
			lecture(&(filename[0]));
			break;
		}
		case Gtk::ResponseType::CANCEL:
		{
			std::cout << "Cancel clicked." << std::endl;
			break;
		}
		default:
		{
			std::cout << "Unexpected button clicked." << std::endl;
			break;
		}
	}
	delete dialog;
} 


void Fenetre::on_button_clicked_save()
{
	sauvegarde();
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
