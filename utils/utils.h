#ifndef INIT

#define INIT

#include "struct.h"

#include <stdlib.h>
#include <stdio.h>

// Fichier: list.c
int isPointEqual(const Point* A, const Point* B);
void printPoint(const Point* p);
int minX(const Point* A, const Point* B);
int maxX(const Point* A, const Point* B);
Point* createPoint(void);
void fillPoint(Point* p, int x, int y);
Vertex* createVertex(void);
void fillVertex(Vertex* vertex, Point* p);
Polygon createPolygon(void);
ConvexHull createConvex(int maxlen);
void addVertexTail(ConvexHull* convex, Vertex* vertex);
void addVertexHead(ConvexHull* convex, Vertex* vertex);
void addPoint(ConvexHull* convex, Point* p, void (*addFunction)(ConvexHull*, Vertex*));
void addPointCoordinates(ConvexHull* convex, int x, int y, void (*addFunction)(ConvexHull*, Vertex*));
Vertex* extractVertexTail(ConvexHull* convex);
Vertex* extractVertexHead(ConvexHull* convex);
Vertex* extractPoint(ConvexHull* convex, Point* p);
Vertex* searchVertexByFunction(ConvexHull* convex, int (*compare)(const Point*, const Point*));
void concatConvex(ConvexHull* convex1, ConvexHull* convex2);
void printPoly(Polygon poly, void (*printPointFunction)(const Point*));
void freePolygon(Polygon* poly);
void freeConvex(ConvexHull* convex);

// Fichier math.c
int isRight(Point* A, Point* B, Point* p);
int dist(Point* A, Point* B);
int crossProduct(Point* p, Point* q, Point* r);
void rightPoints(ConvexHull* convex, Point* A, Point* B, ConvexHull* res);
Point* furtherestPoint(ConvexHull* convex, Point* A, Point* B);
void quickHull(ConvexHull* convex, ConvexHull* res);
void quickHullAux(ConvexHull* convex, ConvexHull* res, Point* p, Point* q);

#endif