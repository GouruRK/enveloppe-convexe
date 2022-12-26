typedef struct pnt { 
    int x;
    int y;
} Point;

typedef struct _vrtx_ { 
    Point* p;
    struct _vrtx_ *prev;
    struct _vrtx_ *next;
} Vertex, *Polygon;

typedef struct {
    Polygon poly;
    int curlen;
    int maxlen;
} ConvexHull;