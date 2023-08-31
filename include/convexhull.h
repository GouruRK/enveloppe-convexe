#ifndef __INIT_CONVEXHULL__
#define __INIT_CONVEXHULL__

#include "struct.h"

void create_convexhull(int* stop);
int init_convexhull(Convex* convex, int* stop);
void create_inception_convexhull(int* stop);
int new_point(Convex* convex, Array* inside_points, Point point);
int new_point_rec(InceptionConvex* incepconv, int depth, Point point);

#endif