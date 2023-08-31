#ifndef __INIT_MATH__
#define __INIT_MATH__

/**
 * @brief Return the cross product of three points.
 * 
 * @param A first point
 * @param B second point
 * @param C third point
 * @return int result
 */
int cross_product(Point A, Point B, Point C);

/**
 * @brief Determine if a triangle ABC is direct, which means 
 *        that the cross product between the three points is >= 0.
 * 
 * @param A first point
 * @param B second point
 * @param C third point
 * @return int '1' if the triangle is direct
 *             else '0'
 */
int is_direct(Point A, Point B, Point C);

#endif
