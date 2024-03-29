/**
 * @file graphic.h
 * @author Laborde Quentin & Kies Remy
 * @brief Contains function declarations to draw anything on the current window
 * @date 05-09-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __INIT_GRAPHIC__
#define __INIT_GRAPHIC__

#include <stdbool.h>
#include <MLV/MLV_all.h>

#include "struct.h"

#define RADIUS 4
#define PI 3.14159265359

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
 * @brief Checks a mouse's position.
 * 
 * @param button button to check
 * @param expected expected position
 * @return 'true' if the given button is at the given position
 *         else 'false'
 */
bool check_mouse_position(MLV_Mouse_button button, MLV_Button_state expected);

/**
 * @brief Checks a key's position.
 * 
 * @param key key to check
 * @param expected expected position
 * @return 'true' if the given key is at the given position
 *         else 'false'
 */
bool check_key_position(MLV_Keyboard_button key, MLV_Button_state expected);

/**
 * @brief Draws a point that is inside a convex hull.
 * 
 * @param point point to draw
 */
void draw_inside_point(Point point);

/**
 * @brief Draws a point that is on the convex hull's outline.
 * 
 * @param point point to draw
 */
void draw_outline_point(Point point);

/**
 * @brief Draws a point of the given color
 * 
 * @param point point to draw
 * @param color color to draw the point
 */
void draw_point(Point point, MLV_Color color);

/**
 * @brief Draws a line between two points.
 * 
 * @param a first point
 * @param b second point
 */
void draw_line(Point a, Point b);

/**
 * @brief Draws a surface between three points of the given colors.
 * 
 * @param a first point
 * @param b second point
 * @param c third point
 * @param color color to draw the surface
 */
void draw_surface(Point a, Point b, Point c, MLV_Color color);

/**
 * @brief Draws a collection of points that are inside a convex hull.
 * 
 * @param points points to draw
 */
void draw_inside_points(Array points);

/**
 * @brief Draws a collection of points that are on a convex hull's outline.
 *        Connect a line between each point
 * 
 * @param points points to draw
 * @param show_points indicate to show or not the points. 
 *                    If not, then only draw a line between each vertexes.
 */
void draw_outline_points(Array points, bool show_points);

/**
 * @brief Draws a surface in the convex hull.
 * 
 * @param convex convex hull to draw the surface
 * @param color color of the surface
 * @param show_points indicate to show or not the points
 */
void draw_filled_convex(Convex convex, MLV_Color color, bool show_points);

/**
 * @brief Draws self-contained convex hulls.
 * 
 * @param incepconv collection of convex hulls
 * @param show_points indicate to show or not the points
 */
void draw_inception_convex(InceptionConvex incepconv, bool show_points);

/**
 * @brief Waits for the user to click on the window. 
 *        When he does, return a point that contains the mouse's coordinates.
 *        If the user close the window, return a point with negatives coordinates.
 * 
 * @param stop set to '1' whenever the user close the window 
 * @param set generation settings. Note that this is the only generation function
 *            that deosnt take into account generation settings
 * @param win window settings
 * @return point that contains the mouse's coordinates when the user click on the window
 */
Point point_on_click(bool* stop, Settings set, Window* win);

/**
 * @brief Randomly generates points that form a circle with a rising radius.
 *        Each time this function is called, it will return further and further point from the origin.
 *        When the user close the window, it return a point with negatives coordinates.
 *        When all points have been generated, return a point with negatives coordinates.
 * 
 * @param stop set to '1' whenever the user close the window 
 * @param param generations settings
 * @param win window settings
 * @return new point
 */
Point rising_circle(bool* stop, Settings set, Window* win);

/**
 * @brief Randomly generates points that form a square with a rising radius.
 *        Each time this function is called, it will return further and further point from the origin.
 *        When the user close the window, it return a point with negatives coordinates.
 *        When all points have been generated, return a point with negatives coordinates.
 * 
 * @param stop set to '1' whenever the user close the window 
 * @param set generation settings
 * @param win window settings
 * @return new point
 */
Point rising_square(bool* stop, Settings set, Window* win);

/**
 * @brief Draws on screen the number of outline points.
 * 
 * @param value number of points
 * @param win window settings
 */
void draw_outline_points_information(int value, Window* win);

/**
 * @brief Draws on screen the number of inside points.
 * 
 * @param value number of points
 * @param win window settings
 */
void draw_inside_points_information(int value, Window* win);

/**
 * @brief Draws on screen the number of points.
 * 
 * @param value number of points
 * @param win window settings
 */
void draw_total_points_information(int value, Window* win);

/**
 * @brief Draws on screen the number of hulls.
 * 
 * @param value number of hulls
 * @param win window settings
 */
void draw_hulls_information(int value, Window* win);

/**
 * @brief Draws on screen given information concerning the number of outline and inside points.
 * 
 * @param outline number of outline points
 * @param inside number of inside points
 * @param win window settings
 */
void draw_raw_convex_information(int outline, int inside, Window* win);

/**
 * @brief Draws on screen information about a convex hull.
 * 
 * @param convex collection of outline points
 * @param points collection of inside points
 * @param win window settings
 */
void draw_convex_information(Convex convex, Array points , Window* win);

/**
 * @brief Draws on screen given information concerning self-contained convex hulls.
 * 
 * @param hulls number of hulls
 * @param points number of points
 * @param win window settings
 */
void draw_raw_inception_convex_information(int hulls, int points, Window* win);

/**
 * @brief Draws on screen information concerning self-contained convex hulls.
 * 
 * @param incepconv collection of hulls
 * @param win window settings
 */
void draw_inception_convex_information(InceptionConvex incepconv, Window* win);

#endif
