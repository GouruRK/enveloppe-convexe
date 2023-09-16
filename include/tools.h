#ifndef __INIT_TOOLS__
#define __INIT_TOOLS__

#include <stdbool.h>

#include "struct.h"

/**
 * @brief Generate a random float between '0' and '1'.
 * 
 * @return float generated float
 */
double uniform(void);

/**
 * @brief Generate a random inclusive int bounded by `min` and `max`.
 * 
 * @param min minimum bound
 * @param max maximum bound
 * @return int generated int
 */
int random_int(int min, int max);

/**
 * @brief Check if two points are equals based on their coordinates.
 *
 * @param a first point
 * @param b second point
 * @return int 'true' if their coordinates are equal
 *             else 'false'
 */
bool equals_points(Point a, Point b);

/**
 * @brief Check if a point in contained in a section.
 * 
 * @param point point to check
 * @param section section to check
 * @return bool 'true' if the point in contained in the section
 *              else 'false'
 */
bool point_in_section(Point point, Section section);

int true_modulo(int a, int b);

#endif
