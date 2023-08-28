#ifndef __INIT_CONVEXHULL__
#define __INIT_CONVEXHULL__

#include "struct.h"

void create_convexhull(int* stop);
int init_convexhull(Convex* convex, int* stop);
void new_point(Convex* convex, Array* inside_points, Point* point);

#endif