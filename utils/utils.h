#ifndef INIT

#define INIT

#include <MLV/MLV_all.h>
#include <stdio.h>
#include <stdlib.h>

#include "struct.h"

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

// Fichier : math.c
int isRight(Point* A, Point* B, Point* p);
int dist(Point* A, Point* B);
int crossProduct(Point* p, Point* q, Point* r);
void rightPoints(ConvexHull* convex, Point* A, Point* B, ConvexHull* res);
Point* furtherestPoint(ConvexHull* convex, Point* A, Point* B);
void quickHull(ConvexHull* convex, ConvexHull* res);
void quickHullAux(ConvexHull* convex, ConvexHull* res, Point* p, Point* q);

// Fichier : graphic.c
void exit_function(void* data);
Button button_create(int x, int y, char* text);
int button_onclick(Button but, int x, int y);
int button_onclick_tab(Button tab[], int size, int x, int y);
void button_draw_Wborder(Button but, MLV_Color color_text, MLV_Color color_border);
void button_draw_WOborder(Button but, MLV_Color color_text);
void button_draw_tab(Button tab[], int val[], int size, MLV_Color color[]);
void switch_(int val[], int size, int index);
void window_param_preclose(void);
void init_window_param(void);

#endif