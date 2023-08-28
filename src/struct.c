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

Polygon create_polygon(void) {
    return NULL;
}

Convex create_convex(int maxlen) {
    Convex convex;
    convex.curlen = 0;
    convex.maxlen = 0;
    convex.poly = create_polygon();
    return convex;
}

Array create_array(int maxlen) {
    return create_convex(maxlen);
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

void free_polygon(Polygon* polygon) {
    if (!(*polygon)) {
        return;
    }
    Vertex* temp;
    Vertex* head = *polygon;
    *polygon = (*polygon)->next;
    while (head != *polygon) {
        temp = (*polygon)->next;
        free_vertex(*polygon);
        *polygon = temp;
    }
    free_vertex(head);
}

void deep_free_polygon(Polygon* polygon) {
    if (!(*polygon)) {
        return;
    }
    Vertex* temp;
    Vertex* head = *polygon;
    *polygon = (*polygon)->next;
    while (head != *polygon) {
        temp = (*polygon)->next;
        deep_free_vertex(*polygon);
        *polygon = temp;
    }
    deep_free_vertex(head);
}

void free_convex(Convex* convex) {
    free_polygon(&((convex->poly)));
    convex->curlen = 0;
    convex->maxlen = 0;
}

void deep_free_convex(Convex* convex) {
    deep_free_polygon(&((convex->poly)));
    convex->curlen = 0;
    convex->maxlen = 0;
}

void free_array(Array* array) {
    free_convex(array);
}

void deep_free_array(Array* array) {
    deep_free_convex(array);
}
