#include <stdlib.h>

#include "../include/struct.h"

Point* create_point(void) {
    return (Point*)malloc(sizeof(Point));
}

Point* create_filled_point(int x, int y) {
    Point* point = create_point();
    fill_point(point, x, y);
    return point;
}

void fill_point(Point* point, int x, int y) {
    if (point) {
        point->x = x;
        point->y = y;
    }
}

Vertex* create_vertex(void) {
    Vertex* vrtx = (Vertex*)malloc(sizeof(Vertex));
    if (vrtx) {
        vrtx->next = vrtx;
        vrtx->prev = vrtx;
    }
    return vrtx;
}

void fill_vertex(Vertex* vrtx, Point* point) {
    if (vrtx) {
        vrtx->point = point;
    }
}

Vertex* create_filled_vertex(Point* point) {
    Vertex* vrtx = create_vertex();
    fill_vertex(vrtx, point);
    return vrtx;
}

void free_point(Point* point) {
    if (point) {
        free(point);
    }
}

void free_vertex(Vertex* vrtx) {
    if (vrtx) {
        free(vrtx);
    }
}

void deep_free_vertex(Vertex* vrtx) {
    if (vrtx) {
        free_point(vrtx->point);
        free(vrtx);
    }
}

Polygon create_polygon(void) {
    return NULL;
}
