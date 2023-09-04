#ifndef __INIT_TOOLS__
#define __INIT_TOOLS__

#include <stdbool.h>

#include "struct.h"

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

#endif
