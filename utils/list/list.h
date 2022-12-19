#include "main.h"

typedef struct pnt {
    int x;
    int y;
} Point;

typedef struct _vrtx_ { 
    Point* s; 
    struct _vrtx_ *prev;
    struct _vrtx_ *next;
} Vertex, *Polygon

typedef struct {
    Polygon pol;
    int curlen;
    int maxlen;
} ConvexHull;