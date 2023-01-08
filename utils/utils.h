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

// define math
#define RADIUS 5
#define PI 3.14159265

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
int min(int x, int y);

// Fichier : ./graphic/draw.c
int isInside(int x, int y, int minX, int maxX, int minY, int maxY);
ConvexHull createConvex(int maxlen);
ConvexHull* createConvexPointer(int maxlen);
ListPoint createListPoint(int maxlen);
ListPoint* createListPointPointer(int maxlen);
void drawPoint(Point* p, int radius, MLV_Color color);
void drawPoints(Polygon poly, int radius, MLV_Color color);
void drawPoly(ConvexHull convex, MLV_Color color, void (*drawFunction)(const int*, const int*, int, MLV_Color));
void drawTriangle(Point* A, Point* B, Point* C);
void drawAll(Window* window, ConvexHull* convex, ConvexHull* insidePoints, int radius, void (*drawFunction)(const int*, const int*, int, MLV_Color));
void initWindow(Window* window, int width, int height, int panelHeight);
void printInfo(Window* window, ConvexHull* convex, ConvexHull* insidePoints);

// Fichier ./graphic/enveloppe.c
void freeAll(ConvexHull* convex, ListPoint* insidePoints, Point* p);
void newPoint(ConvexHull* convex, ListPoint* insidePoints, Point* p);
int r_sign(void);
void drawCircleRandomRising(Window* window, ConvexHull* convex, int radius_max, int nb_points, int wait, float coef);
void drawCircleRandom(Window* window, ConvexHull* convex, int radius_max, int nb_points, int wait, float coef);
void drawSquareRandom(Window* window, ConvexHull* convex, int radius_max, int nb_points, int wait, float coef);
void drawSquareRandomRising(Window* window, ConvexHull* convex, int radius_max, int nb_points, int wait, float coef);
void initConvexClick(Window* window, ConvexHull* convex);
void drawConvexClick(Window* window, ConvexHull* convex);

// Fichier : ./graphic/graphic.c
void exit_function(void* data);
int isClicking(MLV_Mouse_button button, MLV_Button_state expected);
Button createButton(int x, int y, char* text);
int buttonOnClick(Button but, int x, int y);
int button_onclick_tab(Button tab[], int size, int x, int y);
void drawButton(Button but, MLV_Color color_text, MLV_Color color_border);
void button_draw_tab(Button tab[], int size, MLV_Color color[]);
void switch_(Button tab[], int size, int index);
int indexActiveButton(Button tab[], int size);
void windowParamPreclose(int w_width, int w_height, int array[]);
void initWindowParam(int* window_width, int* window_height, int array[]);

// Fichier : ./graphic/inception.c
void freeAllList(InceptionConvex* convexs);
void newPointRec(InceptionConvex* convexs, int depth, Point* p);
void printInfoRec(Window* window, InceptionConvex convexs);
void drawInceptionClick(void);

// Fichier : ./args/errs.c
void errAlloc(void);

#endif