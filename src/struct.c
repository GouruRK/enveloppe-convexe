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
        vrtx->point = NULL;
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

Convex create_convex(void) {
    Convex convex;
    convex.curlen = 0;
    convex.poly = create_polygon();
    return convex;
}

Array create_array(void) {
    return create_convex();
}

InceptionConvex create_inception_convex(void) {
    InceptionConvex incepconv;
    incepconv.tab_convex = (Convex*)malloc(sizeof(Convex) * ALLOCATION_PATERN);
    
    if (!(incepconv.tab_convex)) {
        incepconv.maxlen = 0;
    } else {
        incepconv.maxlen = ALLOCATION_PATERN;
        for (int i = 0; i < incepconv.maxlen; i++) {
            incepconv.tab_convex[i] = create_convex();
        }
    }
    return incepconv;
}

void resize_inception_convex(InceptionConvex* incepconv) {
    if (!incepconv) {
        return;
    }
    Convex* tab_convex = incepconv->tab_convex;
    tab_convex = (Convex*)realloc(tab_convex, (incepconv->maxlen + ALLOCATION_PATERN) * sizeof(Convex));
    if (!tab_convex) {
        free_inception_convex(incepconv);
        return;
    }
    incepconv->tab_convex = tab_convex;
    for (int i = incepconv->maxlen; i < incepconv->maxlen + ALLOCATION_PATERN; i++) {
        incepconv->tab_convex[i] = create_convex();
    }
    incepconv->maxlen += ALLOCATION_PATERN;
}

void free_point(Point* point) {
    if (point) {
        free(point);
    }
}


void free_vertex(Vertex* vrtx) {
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

void free_convex(Convex* convex) {
    free_polygon(&((convex->poly)));
    convex->curlen = 0;
}

void free_array(Array* array) {
    free_convex(array);
}

void free_inception_convex(InceptionConvex* incepconv) {
    if (!incepconv) {
        return;
    }
    for (int i = 0; i < incepconv->maxlen; i++) {
        free_convex(&(incepconv->tab_convex[i]));
    }
    free(incepconv->tab_convex);
    incepconv->maxlen = 0;
}

