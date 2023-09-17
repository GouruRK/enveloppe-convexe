/**
 * @file convexhull.h
 * @author Laborde Quentin & Kies Remy
 * @brief Contains function declarations to graphically create convex hulls and self-contained convex hulls
 * @date 05-09-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __INIT_CONVEXHULL__
#define __INIT_CONVEXHULL__

#include <stdbool.h>

#include "struct.h"

/**
 * @brief Creates graphically a simple convex hull.
 *        Point selection is determined by the `get_point` function.
 * 
 * @param stop set to 'true' whenever the user close the window 
 * @param set generation settings
 * @param get_point function that give the next point to be added
 *                  It can be either :
 *                   - 'point_on_click'
 *                   - 'rising_circle'
 *                   - 'rising_square'
 * @param win window parameters
 */
void create_convexhull(bool* stop, Settings set, Point (*get_point)(bool*, Settings, Window*), Window* win);

/**
 * @brief Initiates graphically a simple convex hull by collecting 
 *        with clicks the first two points.
 * 
 * @param convex point collection of the convex hull object
 * @param stop set to 'true' whenvever the suer close the window 
 * @param set generation settings
 * @param get_point function that give the next point to be added
 *                  It can be either :
 *                   - 'point_on_click'
 *                   - 'rising_circle'
 *                   - 'rising_square'
 * @param win window parameters
 * @return '0' to stop the processus    
 *         '1' to continue
 */
int init_convexhull(Convex* convex, bool* stop, Settings set, Point (*get_point)(bool*, Settings, Window*), Window* win);

/**
 * @brief Creates graphically a self-contained convex hull.
 *        Point selection is click-based.
 * 
 * @param stop set to 'true' whenever the user close the window
 * @param set generation settings
 * @param get_point function that give the next point to be added
 *                  It can be either :
 *                   - 'point_on_click'
 *                   - 'rising_circle'
 *                   - 'rising_square'
 * @param win window parameters
 */
void create_inception_convexhull(bool* stop, Settings set, Point (*get_point)(bool*, Settings, Window*), Window* win);

/**
 * @brief Determines if a point is on the convex hull outline or inside the hull.
 *        Based on that, add the point to `convex` or `inside_points` and do the
 *        necessary changes.
 * 
 * @param convex contains the outlines points of the hull
 * @param inside_points contains the points inside the hull
 * @param point point to add
 * @return '1' to continue the process if no errors
 *         else '0', due to allocation error 
 */
int new_point(Convex* convex, Array* inside_points, Point point);

/**
 * @brief Determines in which hull to add a point in a self-contained convex hull.
 * 
 * @param incepconv collection of convex hull objects
 * @param depth current convex hull
 * @param point point to add
 * @return '1' to continue the process if no errors
 *         else '0', due to allocation error 
 */
int new_point_rec(InceptionConvex* convexs, int depth, Point p);

#endif
