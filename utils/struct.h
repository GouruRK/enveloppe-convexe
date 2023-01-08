typedef struct pnt {
    int x;
    int y;
} Point;

typedef struct _vrtx_ {
    Point* p;
    struct _vrtx_* prev;
    struct _vrtx_* next;
} Vertex, *Polygon;

typedef struct {
    Polygon poly;
    int curlen;
    int maxlen;
} ConvexHull, ListPoint;

typedef struct button {
    char* text;
    int x;
    int y;
    int height;
    int width;
    int value;
} Button;

typedef struct {
    ConvexHull** tabconvex;
    int size;
} InceptionConvex;

typedef struct win {
    int width;
    int height;
    int clickableWidth;
    int clickableHeight;
    int infoWidth;
    int infoHeight;
} Window;