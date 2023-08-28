#ifndef __INIT_GRAPHIC__
#define __INIT_GRAPHIC__

#include <MLV/MLV_all.h>

#include "struct.h"

#define RADIUS 5 

#define INSIDE_POINT_COLOR MLV_COLOR_RED
#define ONLINE_POINT_COLOR MLV_COLOR_BLUE
#define LINE_COLOR MLV_COLOR_BLACK

void exit_function(void* data);
int check_mouse_position(MLV_Mouse_button button, MLV_Button_state expected);
void draw_inside_point(Point* point);
void draw_online_point(Point* point);
void draw_point(Point* point, MLV_Color color);
void draw_line(Point* a, Point* b);
void draw_array(Array points);
void draw_outline(Convex convex);

#endif
