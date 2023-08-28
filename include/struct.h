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
} Convex, Array;

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

Polygon create_polygon(void);
Convex create_convex(int maxlen);
Array create_array(int maxlen);

void free_point(Point* point);
void free_vertex(Vertex* vrtx);
void deep_free_vertex(Vertex* vrtx);
void free_polygon(Polygon* polygon);
void deep_free_polygon(Polygon* polygon);
void free_convex(Convex* convex);
void deep_free_convex(Convex* convex);
void free_array(Array* array);
void deep_free_array(Array* array);

#endif
