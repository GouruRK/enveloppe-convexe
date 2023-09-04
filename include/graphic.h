#ifndef __INIT_GRAPHIC__
#define __INIT_GRAPHIC__

#include <stdbool.h>
#include <MLV/MLV_all.h>

#include "struct.h"

#define RADIUS 5 

#define INSIDE_POINT_COLOR MLV_COLOR_RED
#define ONLINE_POINT_COLOR MLV_COLOR_BLUE
#define LINE_COLOR MLV_COLOR_BLACK
#define TEXT_COLOR MLV_COLOR_BLACK

#define TAB_COLOR_SIZE 6

#define TAB_COLOR (MLV_Color[TAB_COLOR_SIZE]) { \
    MLV_rgba(0, 0, 255, 100),                   \
    MLV_rgba(0, 255, 0, 100),                   \
    MLV_rgba(255, 0, 0, 100),                   \
    MLV_rgba(255, 0, 255, 100),                 \
    MLV_rgba(0, 255, 255, 100),                 \
    MLV_rgba(255, 255, 0, 100)                  \
}

/**
 * @brief Function executed whenever the user close the window.
 *        Set `data` to '1' in this case.
 * 
 * @param data set to '1' if the user close the window
 */
void exit_function(void* data);

/**
 * @brief Check mouse's buttons position.
 * 
 * @param button button to check
 * @param expected expected position
 * @return int '1' if the given button is at the given position
 *             else '0'
 */
bool check_mouse_position(MLV_Mouse_button button, MLV_Button_state expected);

bool check_key_position(MLV_Keyboard_button key, MLV_Button_state expected);

/**
 * @brief Draw a point that is inside a convex hull.
 * 
 * @param point point to draw
 */
void draw_inside_point(Point point);

/**
 * @brief Draw a point that is on the convex hull's outline.
 * 
 * @param point point to draw
 */
void draw_outline_point(Point point);

/**
 * @brief Draw a point of the given color
 * 
 * @param point point to draw
 * @param color color to draw the point
 */
void draw_point(Point point, MLV_Color color);

/**
 * @brief Draw a line between two points.
 * 
 * @param a first point
 * @param b second point
 */
void draw_line(Point a, Point b);

/**
 * @brief Draw a surface between three points of the given colors.
 * 
 * @param a first point
 * @param b second point
 * @param c third point
 * @param color color to draw the surface
 */
void draw_surface(Point a, Point b, Point c, MLV_Color color);

/**
 * @brief Draw a collection of points that are inside a convex hull.
 * 
 * @param points points to draw
 */
void draw_inside_points(Array points);

/**
 * @brief Draw a collection of points that are on a convex hull's outline.
 * 
 * @param points points to draw
 */
void draw_outline_points(Array points, bool show_points);

/**
 * @brief Draw a surface in the convex hull.
 * 
 * @param convex convex hull to draw the surface
 * @param color color of the surface
 */
void draw_filled_convex(Convex convex, MLV_Color color, bool show_points);

/**
 * @brief Draw self-contained convex hulls.
 * 
 * @param incepconv collection of convex hulls
 */
void draw_inception_convex(InceptionConvex incepconv, bool show_points);

Point point_on_click(int* stop, int nb_points, Window* win);

Point rising_sphere(int* stop, int nb_points, Window* win);

Point rising_square(int* stop, int nb_points, Window* win);

void draw_outline_points_information(int value, Window* win);

void draw_inside_points_information(int value, Window* win);

void draw_total_points_information(int value, Window* win);

void draw_hulls_information(int value, Window* win);

void draw_raw_convex_information(int outline, int inside, Window* win);

void draw_convex_information(Convex convex, Array points , Window* win);

void draw_raw_inception_convex_information(int hulls, int points, Window* win);

void draw_inception_convex_information(InceptionConvex incepconv, Window* win);

#endif
