#include <iostream>
#include <cairomm/context.h>
#include "gui.h"
#include "simulation.h"
#include "graphic_gui.h"
#include "constante.h"

////////////////////////////////////////////

// default Model Framing and window parameters
static Frame default_frame = {-150., 150., -100., 100., 1.5, 300, 200}; 

constexpr int area_side(200);

static void draw_frame(const Cairo::RefPtr<Cairo::Context>& cr, Frame frame);
static void orthographic_projection(const Cairo::RefPtr<Cairo::Context>& cr, 
									Frame frame);

MyArea::MyArea(): empty(false)
{
	set_content_width(area_side);
	set_content_height(area_side);
	
	set_draw_func(sigc::mem_fun(*this, &MyArea::on_draw));
}

MyArea::~MyArea()
{
}

void MyArea::clear()
{
	empty = true; 
	queue_draw();
}

void MyArea::draw()
{
	empty = false;
	queue_draw();
}

// defining the Model space frame to visualize in the window canvas
void MyArea::setFrame(Frame f)
{
	if((f.xMin <= f.xMax) and (f.yMin <= f.yMax) and (f.height > 0))
	{
		f.asp = f.width/f.height;
		frame = f;
	}
	else
		std::cout << "incorrect Model framing or window parameters" << std::endl;
} 

void MyArea::adjustFrame(int width, int height)
{
	frame.width  = width;
	frame.height = height;

	// Preventing distorsion by adjusting the frame (cadrage)
	// to have the same proportion as the graphical area
	
    // use the reference framing as a guide for preventing distortion
    double new_aspect_ratio((double)width/height);
    if( new_aspect_ratio > default_frame.asp)
    { // keep yMax and yMin. Adjust xMax and xMin
	    frame.yMax = default_frame.yMax ;
	    frame.yMin = default_frame.yMin ;	
	  
	    double delta(default_frame.xMax - default_frame.xMin);
	    double mid((default_frame.xMax + default_frame.xMin)/2);
        // the new frame is centered on the mid-point along X
	    frame.xMax = mid + 0.5*(new_aspect_ratio/default_frame.asp)*delta ;
	    frame.xMin = mid - 0.5*(new_aspect_ratio/default_frame.asp)*delta ;		  	  
    }
    else
    { // keep xMax and xMin. Adjust yMax and yMin
	    frame.xMax = default_frame.xMax ;
	    frame.xMin = default_frame.xMin ;
	  	  
 	    double delta(default_frame.yMax - default_frame.yMin);
	    double mid((default_frame.yMax + default_frame.yMin)/2);
        // the new frame is centered on the mid-point along Y
	    frame.yMax = mid + 0.5*(default_frame.asp/new_aspect_ratio)*delta ;
	    frame.yMin = mid - 0.5*(default_frame.asp/new_aspect_ratio)*delta ;		  	  
    }
}




void MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height)
{
	graphic_set_context(cr);
	if(not empty)   // drawing in the Model space
	{
		// adjust the frame (cadrage) to prevent distortion 
		adjustFrame(width, height);
		draw_frame(cr, frame);
		orthographic_projection(cr, frame); // set the transformation MODELE to GTKmm
	
		//set width and color
		cr->set_line_width(1);
		cr->set_source_rgb(0.2, 0.2, 0.2);
	
		//Now we can draw directly in the Model space
		cr->move_to(-dmax,dmax);
		cr->line_to(-dmax,-dmax);
		cr->line_to(dmax,-dmax);
		cr->line_to(dmax,dmax);
		cr->line_to(-dmax,dmax);
		cr->stroke();
		
		simulation::draw_all_Robots();
	}
	else
	{
		std::cout << "Empty !" << std::endl;
	}
}
static void draw_frame(const Cairo::RefPtr<Cairo::Context>& cr, Frame frame)
{
	//display a rectangular frame around the drawing area
	cr->set_line_width(10.0);
	// draw greenish lines
	cr->set_source_rgb(0., 0.7, 0.2);
	cr->rectangle(0,0, frame.width, frame.height);
	cr->stroke();
}
static void orthographic_projection(const Cairo::RefPtr<Cairo::Context>& cr, 
								    Frame frame)
{
	// déplace l'origine au centre de la fenêtre
	cr->translate(frame.width/2, frame.height/2);
  
	// normalise la largeur et hauteur aux valeurs fournies par le cadrage
	// ET inverse la direction de l'axe Y
	cr->scale(frame.width/(frame.xMax - frame.xMin), 
             -frame.height/(frame.yMax - frame.yMin));
  
	// décalage au centre du cadrage
	cr->translate(-(frame.xMin + frame.xMax)/2, -(frame.yMin + frame.yMax)/2);
}

/////////////////////////////////////////////////////////////////////////////

Fenetre::Fenetre():
	
	Frame_Buttons("General"),
	Frame_Infos("info : nombre de ..."),
	
	Main_Box(Gtk::Orientation::HORIZONTAL, 0),
	UI_Box(Gtk::Orientation::VERTICAL, 0),
	Buttons_Box(Gtk::Orientation::VERTICAL, 1),
	Infos_Box(Gtk::Orientation::HORIZONTAL, 100),
	Label_Box(Gtk::Orientation::VERTICAL, 0),
	Data_Box(Gtk::Orientation::VERTICAL, 0),
	
	data_maj("0"), data_particules("0"), data_nbNr("0"), data_nbNs("0"), 
	data_nbNd("0"), data_nbRr("0"), data_nbRs("0"), data_nbNp("0"),
	data_label("mises à jour:\nparticules:\nrobots réparateurs en service:\n\
robots réparateurs en réserve:\nrobots neutraliseurs en service:\n\
robots neutraliseurs en panne:\nrobots neutraliseurs détruits:\n\
robots neutraliseurs en réserve:"),
	
	Button_Exit("exit"), Button_Open("open"), Button_Save("save"),
	Button_Start("start"), Button_Step("step"),
	
	timer_added(false),// to handle a single timer
	disconnect(false), // to handle a single timer
	timeout_value(500) // 500 ms = 0.5 seconds
{
	set_title("Propre en Ordre");
	set_resizable(true);
	set_child(Main_Box);
	
	create_boxes();
	
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

void Fenetre::create_boxes()
{
	
	Main_Box.append(UI_Box);
	Main_Box.append(m_area);
	UI_Box.append(Frame_Buttons);
	UI_Box.append(Frame_Infos);
	
	Infos_Box.append(Label_Box);
	Infos_Box.append(Data_Box);
	
	// allow the Simulation to expand to the window size
	m_area.set_expand();
	
	
	Frame_Buttons.set_label_align(Gtk::Align::START);
	Frame_Buttons.set_child(Buttons_Box);
	
	Frame_Infos.set_label_align(Gtk::Align::START);
	Frame_Infos.set_child(Infos_Box);
	
	
	Label_Box.append(data_label);
	
	Data_Box.append(data_maj);
	Data_Box.append(data_particules);
	Data_Box.append(data_nbRs);
	Data_Box.append(data_nbRr);
	Data_Box.append(data_nbNs);
	Data_Box.append(data_nbNp);
	Data_Box.append(data_nbNd);
	Data_Box.append(data_nbNr);
	
	Buttons_Box.append(Button_Exit);
	Buttons_Box.append(Button_Open);
	Buttons_Box.append(Button_Save);
	Buttons_Box.append(Button_Start);
	Buttons_Box.append(Button_Step);
	
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
			simulation::lecture(&(filename[0]));
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
	simulation::sauvegarde();
}

void Fenetre::on_button_clicked_start()
{
	if(Button_Start.get_label() == "start")
	{
		Button_Start.set_label("stop");
		Button_Step.set_sensitive(false);
		on_button_add_timer();
	}
	else 
	{
		Button_Start.set_label("start");
		Button_Step.set_sensitive(true);
		on_button_delete_timer();
	}
}

void Fenetre::on_button_clicked_step()
{
	on_timeout();
}

void Fenetre::on_button_add_timer()
{
	if(not timer_added)
	{	  
		// Creation of a new object prevents long lines and shows us a little
		// how slots work.  We have 0 parameters and bool as a return value
		// after calling sigc::bind.
		sigc::slot<bool()> my_slot = sigc::bind(sigc::mem_fun(*this,
		                                        &Fenetre::on_timeout));
		
		// This is where we connect the slot to the Glib::signal_timeout()
		auto conn = Glib::signal_timeout().connect(my_slot,timeout_value);
			
		timer_added = true;
		
	}
}

void Fenetre::on_button_delete_timer()
{
	if(timer_added)
	{
		disconnect  = true;   
		timer_added = false;
	}
}

bool Fenetre::on_timeout()
{
	static unsigned int maj(1);
	
	if(disconnect)
	{
		disconnect = false; // reset for next time a Timer is created
		
		return false; // End of Timer 
	}
	
	//simulation::mise_a_jour();
	Data data = simulation::get_data();
	data_maj.set_text(std::to_string(maj));
	data_particules.set_text(std::to_string(data.p));
	data_nbRs.set_text(std::to_string(data.nbRs));
	data_nbRr.set_text(std::to_string(data.nbRr));
	data_nbNs.set_text(std::to_string(data.nbNs));
	data_nbNp.set_text(std::to_string(data.nbNp));
	data_nbNd.set_text(std::to_string(data.nbNd));
	data_nbNr.set_text(std::to_string(data.nbNr));
	
	++maj;
}
