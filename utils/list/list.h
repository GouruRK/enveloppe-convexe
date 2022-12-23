#include "main.h"

typedef struct pnt {
    int x;
    int y;
} Point;

typedef struct _vrtx_ {
    Point *s;
    struct _vrtx_ *prev;
    struct _vrtx_ *next;
} Vertex, *Polygon

          typedef struct {
    Polygon pol;
    int curlen;
    int maxlen;
} ConvexHull;

static const char red[] = "\x1b[31m";
static const char green[] = "\x1b[32m";
static const char cyan[] = "\x1b[36m";
static const char reset[] = "\x1b[0m";