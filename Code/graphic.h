#ifndef GTKMM_EXAMPLE_GRAPHIC_H
#define GTKMM_EXAMPLE_GRAPHIC_H

struct RGB{double r; double g; double b;};
constexpr RGB WHITE = {1,1,1};
constexpr RGB GREY = {0.5,0.5,0.5};
constexpr RGB RED = {1,0,0};
constexpr RGB LIGHT_BLUE = {0,0.5,1};
constexpr RGB BLACK = {0,0,0};
constexpr RGB PURPLE = {0.3,0,0.5};
constexpr RGB ORANGE = {0.9,0.5,0.1};
constexpr RGB GREEN = {0,0.5,0};

constexpr bool FILLED (true);
constexpr bool UNFILLED (false);


void graphic_draw_square(double cote, double xc, double yc, RGB color, 
							bool fill,RGB colorb);
void graphic_draw_circle(double rayon, double xc, double yc, RGB color, 
							bool fill,RGB colorb,bool robotNeut);

#endif // GTKMM_EXAMPLE_GRAPHIC_H
