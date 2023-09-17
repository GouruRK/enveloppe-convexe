#ifndef __INIT_MATH__
#define __INIT_MATH__

#include <stdbool.h>

/**
 * @brief Returns the cross product of three points.
 * 
 * @param A first point
 * @param B second point
 * @param C third point
 * @return result
 */
int cross_product(Point A, Point B, Point C);

/**
 * @brief Determines if a triangle ABC is direct, which means 
 *        that the cross product between the three points is >= 0.
 * 
 * @param A first point
 * @param B second point
 * @param C third point
 * @return 'true' if the triangle is direct
 *         else 'false'
 */
bool is_direct(Point A, Point B, Point C);

#endif
