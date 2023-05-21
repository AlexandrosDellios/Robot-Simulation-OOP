/* Projet Propre en ordre 2023
 * graphic.cc
 * Leo Sierra 341942
 * Alexandros Dellios 355873
 * Alexandros : 100%
*/
#include <cmath>
#include "graphic_gui.h"

static const Cairo::RefPtr<Cairo::Context>* ptcr(nullptr); 

void graphic_set_context(const Cairo::RefPtr<Cairo::Context>& cr)
{
	ptcr = &cr;
}

void graphic_draw_square(double cote, double xc, double yc, RGB color, 
							bool fill,RGB colorb) 
{
	if(cote <= 0.) return;
	(*ptcr)->rectangle(xc-(cote/2),yc-(cote/2),cote,cote);
	if (fill==true){
		(*ptcr)->set_source_rgb(colorb.r,colorb.g,colorb.b);
		(*ptcr)->fill_preserve();
	}
	(*ptcr)->set_line_width(0.3);
	(*ptcr)->set_source_rgb(color.r,color.g,color.b);
	(*ptcr)->stroke();
}

void graphic_draw_circle(double rayon, double xc, double yc, RGB color, 
						bool fill,RGB colorb, int type,double alpha=0)
{
	if(rayon <= 0.) return;
	(*ptcr)->arc(xc,yc,rayon,0.0, 2*M_PI);
	if (fill==true)
	{
		(*ptcr)->set_source_rgb(colorb.r,colorb.g,colorb.b);
		(*ptcr)->fill_preserve();
	}
	(*ptcr)->set_line_width(0.8);
	(*ptcr)->set_source_rgb(color.r,color.g,color.b);
	(*ptcr)->stroke();
	switch (type) //type de robot 1 : neutraliseur, 2 : spatial, 3 : reparateur
	{
		case 1:
			(*ptcr)->set_line_width(1.0);
			(*ptcr)->set_source_rgb(GREEN.r,GREEN.g,GREEN.b);
			(*ptcr)->move_to(xc,yc);
			(*ptcr)->line_to(xc+rayon*cos(alpha),yc+rayon*sin(alpha));
			(*ptcr)->stroke();
		case 2: //appel commun au neutraliseur et spatial (dessin du centre)
			(*ptcr)->arc(xc,yc,0.25,0.0, 2*M_PI);
			(*ptcr)->set_line_width(0.5);
			(*ptcr)->set_source_rgb(color.r,color.g,color.b);
			(*ptcr)->stroke();
		break;
		default:
		break;
	}
}





