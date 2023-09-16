#ifndef __INIT_CONVEXHULL__
#define __INIT_CONVEXHULL__

#include "struct.h"

/**
 * @brief Create graphically a simple convex hull.
 *        Point selection is click-based.
 * 
 * @param stop set to '1' whenever the user close the window
 */
void create_convexhull(int* stop, Parameters param, Point (*get_point)(int*, Parameters, Window*), Window* win);

/**
 * @brief Initiate graphically a simple convex hull by collecting 
 *        with clicks the first two points.
 * 
 * @param convex point collection of the convex hull object
 * @param stop set to '1' whenvever the suer close the window
 * @return int '1' to continue the process
 *             else '0'
 */
int init_convexhull(Convex* convex, int* stop, Parameters param, Point (*get_point)(int*, Parameters, Window*), Window* win);

/**
 * @brief Create graphically a self-contained convex hull.
 *        Point selection is click-based.
 * 
 * @param stop set to '1' whenever the user close the window
 */
void create_inception_convexhull(int* stop, Parameters param, Point (*get_point)(int*, Parameters, Window*), Window* win);

/**
 * @brief Determine if a point is on the convex hull outline or inside the hull.
 *        Based on that, add the point to `convex` or `inside_points` and do the
 *        necessary changes.
 * 
 * @param convex contains the outlines points of the hull
 * @param inside_points contains the points inside the hull
 * @param point point to add
 * @return int '1' to continue the process if no errors
 *             else '0', due to allocation error 
 */
int new_point(Convex* convex, Array* inside_points, Point point);

/**
 * @brief Determine in which hull to add a point in a self-contained convex hull.
 * 
 * @param incepconv collection of convex hull objects
 * @param depth current convex hull
 * @param point point to add
 * @return int '1' to continue the process if no errors
 *             else '0', due to allocation error 
 */
int new_point_rec(InceptionConvex* convexs, int depth, Point p);

#endif
