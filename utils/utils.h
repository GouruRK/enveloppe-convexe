#ifndef INIT

#define INIT

#include <MLV/MLV_all.h>
#include <stdio.h>
#include <stdlib.h>


#include "struct.h"

// define draw color
#define COLOR_INSIDE MLV_COLOR_ORANGE
#define COLOR_OUTSIDE MLV_COLOR_BLUE
#define COLOR_LINE MLV_COLOR_BLACK

// define console color
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"

// Fichier: ./list/list.c
int isPointEqual(const Point* A, const Point* B);
void printPoint(const Point* p);
int minX(const Point* A, const Point* B);
int maxX(const Point* A, const Point* B);
Point* createPoint(void);
void fillPoint(Point* p, int x, int y);
Vertex* createVertex(void);
void fillVertex(Vertex* vertex, Point* p);
Polygon createPolygon(void);
void addVertexTail(Polygon* poly, Vertex* vertex);
void addVertexHead(Polygon* poly, Vertex* vertex);
int addPoint(Polygon* poly, Point* p, void (*addFunction)(Polygon*, Vertex*));
int addPointCoordinates(Polygon* poly, int x, int y, void (*addFunction)(Polygon*, Vertex*));
Vertex* extractVertexTail(Polygon* poly);
Vertex* extractVertexHead(Polygon* poly);
Vertex* extractPoint(Polygon* poly, Point* p);
Vertex* searchVertexByFunction(Polygon* poly, int (*compare)(const Point*, const Point*));
void concatPolygon(Polygon* poly1, Polygon* poly2);
int length(Polygon poly);
void printPoly(Polygon poly, void (*printPointFunction)(const Point*));
void freePolygon(Polygon* poly);

// Fichier : ./math/math.c
int crossProduct(Point* p, Point* q, Point* r);
int isDirect(Point* A, Point* B, Point* p);
int isInside(Polygon* poly, Point* p);

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



// Fichier : ./graphic/draw.c
ConvexHull createConvex(int maxlen);
void drawPoint(Point* p, int radius, MLV_Color color);
void drawPoints(Polygon poly, int radius, MLV_Color color);
void drawPoly(ConvexHull convex, MLV_Color color, void (*drawFunction)(const int*, const int*, int, MLV_Color));
void drawTriangle(Point* A, Point* B, Point* C);
void drawAll(ConvexHull* convex, ConvexHull* insidePoints, int radius, void (*drawFunction)(const int*, const int*, int, MLV_Color));

// Fichier : ./args/errs.c
void errAlloc(void);

#endif