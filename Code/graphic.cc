#include <cmath>
#include "graphic_gui.h"


static const Cairo::RefPtr<Cairo::Context>* ptcr(nullptr); 

void graphic_set_context(const Cairo::RefPtr<Cairo::Context>& cr)
{
	ptcr = &cr;
}

void graphic_draw_square(const double cote, double xc, double yc, RGB color, 
bool fill,RGB colorb) 
{

	(*ptcr)->rectangle(xc-(cote/2),yc-(cote/2),cote,cote);
	if (fill==true){
		(*ptcr)->set_source_rgb(colorb.r,colorb.g,colorb.b);
		(*ptcr)->fill_preserve();
	}
	(*ptcr)->set_line_width(5.0);
	(*ptcr)->set_source_rgb(color.r,color.g,color.b);
	(*ptcr)->stroke();
}

void graphic_draw_circle(const double rayon, double xc, double yc, RGB color, 
bool fill,RGB colorb,bool robotNeut)
{
	(*ptcr)->arc(xc,yc,rayon,0.0, 2*M_PI);
	if (fill==true){
		(*ptcr)->set_source_rgb(colorb.r,colorb.g,colorb.b);
		(*ptcr)->fill_preserve();
	}
	(*ptcr)->set_line_width(5.0);
	(*ptcr)->set_source_rgb(color.r,color.g,color.b);
	(*ptcr)->stroke();
}

