#ifndef INIT

#define INIT

#include "struct.h"

#include <stdlib.h>
#include <stdio.h>

// Fichier: list.c
static inline int isPointEqual(const Point* A, const Point* B);
static inline void printPoint(const Point* p);
static inline int minX(const Point* A, const Point* B);
static inline int maxX(const Point* A, const Point* B);
Point* createPoint(void);
void fillPoint(Point* p, int x, int y);
Vertex* createVertex(void);
void fillVertex(Vertex* vertex, Point* p);
Polygon createPolygon(void);
void addVertexTail(Polygon* poly, Vertex* vertex);
void addVertexHead(Polygon* poly, Vertex* vertex);
Vertex* extractPoint(Polygon* poly, Point* p);
Vertex* searchVertexByFunction(Polygon* poly, int (*compare)(const Point*, const Point*));
Vertex* extractVertexTail(Polygon* poly);
Vertex* extractVertexHead(Polygon* poly);
void concatPolygon(Polygon* poly1, Polygon* poly2);
int length(Polygon poly);
void printPoly(Polygon poly, void (*printPointFunction)(const Point*));
void freePolygon(Polygon* poly);


// Fichier math.c
static inline int isRight(Point* A, Point* B, Point* p);
int dist(Point* A, Point* B);
int crossProduct(Point* p, Point* q, Point* r);
void rightPoints(Polygon* poly, Point* A, Point* B, Polygon* res);
Point* furtherestPoint(Polygon* poly, Point* A, Point* B);

#endif