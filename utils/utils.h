#ifndef INIT

#define INIT

#include "struct.h"

#include <stdlib.h>
#include <stdio.h>

// Fichier: list.c

Point* createPoint(void);
void fillPoint(Point* p, int x, int y);
Vertex* createVertex(void);
void fillVertex(Vertex* vertex, Point* p);
Polygon createPolygon(void);
void addVertexTail(Polygon* poly, Vertex* vertex);
void addVertexHead(Polygon* poly, Vertex* vertex);
void concatPolygon(Polygon* poly1, Polygon* poly2);
int length(Polygon poly);
void freePolygon(Polygon* poly);

#endif