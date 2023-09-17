#ifndef __INIT_TOOLS__
#define __INIT_TOOLS__

#include <stdbool.h>

#include "struct.h"

/**
 * @brief Generates a random float between '0' and '1'.
 * 
 * @return generated float
 */
double uniform(void);

/**
 * @brief Generates a random inclusive int bounded by `min` and `max`.
 * 
 * @param min minimum bound
 * @param max maximum bound
 * @return generated int
 */
int random_int(int min, int max);

/**
 * @brief Checks if two points are equals based on their coordinates.
 *
 * @param a first point
 * @param b second point
 * @return 'true' if their coordinates are equal
 *         else 'false'
 */
bool equals_points(Point a, Point b);

/**
 * @brief Checks if a point in contained in a section.
 * 
 * @param point point to check
 * @param section section to check
 * @return 'true' if the point in contained in the section
 *         else 'false'
 */
bool point_in_section(Point point, Section section);

int true_modulo(int a, int b);

#endif
