#ifndef __INIT_STRUCT__
#define __INIT_STRUCT__

typedef struct {
    int x;
    int y;
} Point;

typedef struct _vrtx {
    Point* point;
    struct _vrtx* next;
    struct _vrtx* prev;
} Vertex, *Polygon;

typedef struct {
    Polygon poly;
    int curlen;
    int maxlen;
} Convex;

typedef struct {
    Convex** tab_convex;
    int size;
} InceptionConvex;


Point* create_point(void);
Point* create_filled_point(int x, int y);
void fill_point(Point* point, int x, int y);

Vertex* create_vertex(void);
Vertex* create_filled_vertex(Point* point);
void fill_vertex(Vertex* vrtx, Point* point);

void free_point(Point* point);
void free_vertex(Vertex* vrtx);
void deep_free_vertex(Vertex* vrtx);

Polygon create_polygon(void);


#endif
