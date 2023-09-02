#ifndef __INIT_TOOLS__
#define __INIT_TOOLS__

#include "struct.h"

/**
 * @brief Check if two points are equals based on their coordinates.
 * 
 * @param a first point
 * @param b second point
 * @return int '1' if their coordinates are equal
 *             else '0'
 */
int equals_points(Point a, Point b);

int point_in_section(Point point, Section section);

#endif
