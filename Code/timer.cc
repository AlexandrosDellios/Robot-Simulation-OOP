#include <string>
#include "basictimer.h"

BasicTimer::BasicTimer() :
	m_box(Gtk::Orientation::VERTICAL, 10),
	top_box(Gtk::Orientation::HORIZONTAL, 10),
	bottom_box(Gtk::Orientation::HORIZONTAL, 10),
	start_timer("_Start", true),
	stop_timer("_Stop", true),
	quit_button("_Quit", true),
	text_label("Simulation step : "),
	data_label("0"),
	timer_added(false),// to handle a single timer
	disconnect(false), // to handle a single timer
	timeout_value(500) // 500 ms = 0.5 seconds
{
	m_box.set_margin(10);
	set_child(m_box);
	
	m_box.append(top_box);
	m_box.append(bottom_box);
	
	top_box.append(start_timer);
	top_box.append(stop_timer);
	top_box.append(quit_button);
	
	start_timer.set_expand();
	stop_timer.set_expand();
	quit_button.set_expand();

	bottom_box.append(text_label);
	bottom_box.append(data_label);

	text_label.set_expand();
	data_label.set_expand();
	
	// Connect the three buttons:
	quit_button.signal_clicked().connect(sigc::mem_fun(*this,
			  &BasicTimer::on_button_quit));
	start_timer.signal_clicked().connect(sigc::mem_fun(*this,
			  &BasicTimer::on_button_add_timer));
	stop_timer.signal_clicked().connect(sigc::mem_fun(*this,
			  &BasicTimer::on_button_delete_timer));
}

void BasicTimer::on_button_quit()
{
  hide();
}

void BasicTimer::on_button_add_timer()
{
	if(not timer_added)
	{	  
		// Creation of a new object prevents long lines and shows us a little
		// how slots work.  We have 0 parameters and bool as a return value
		// after calling sigc::bind.
		sigc::slot<bool()> my_slot = sigc::bind(sigc::mem_fun(*this,
		                                        &BasicTimer::on_timeout));
		
		// This is where we connect the slot to the Glib::signal_timeout()
		auto conn = Glib::signal_timeout().connect(my_slot,timeout_value);
			
		timer_added = true;
		
		std::cout << "Timer added" << std::endl;
	}
	else
	{
	    std::cout << "The timer already exists : nothing more is created" 
	              << std::endl;
	}
}

void BasicTimer::on_button_delete_timer()
{
	if(not timer_added)
	{
		std::cout << "Sorry, there is no active timer at the moment." << std::endl;
	}
	else
	{
		std::cout << "manually disconnecting the timer " << std::endl;
		disconnect  = true;   
		timer_added = false;
	}
}

bool BasicTimer::on_timeout()
{
	static unsigned int val(1);
	
	if(disconnect)
	{
		disconnect = false; // reset for next time a Timer is created
		
		return false; // End of Timer 
	}
	
	data_label.set_text(std::to_string(val));  // display he simulation clock
	
	std::cout << "This is simulation update number : " << val << std::endl;

	++val;
	return true; 
}
