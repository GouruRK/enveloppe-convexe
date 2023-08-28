#ifndef __INIT_LIST__
#define __INIT_LIST__

#include "struct.h"

void add_vertex_tail(Polygon* poly, Vertex* vrtx);
void add_vertex_head(Polygon* poly, Vertex* vrtx);
int addPoint(Polygon* poly, Point* point, void (*addFunction)(Polygon*, Vertex*));
Vertex* extract_vertex_tail(Polygon* poly);
Vertex* extract_vertex_head(Polygon* poly);
Vertex* extract_point(Polygon* poly, Point* point);

#endif
