#include <stdlib.h>

#include "../include/struct.h"

Point create_point(int x, int y) {
    Point point;
    fill_point(&point, x, y);
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

void fill_vertex(Vertex* vrtx, Point point) {
    if (vrtx) {
        vrtx->point = point;
    }
}

Vertex* create_filled_vertex(Point point) {
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

InceptionConvex create_inception_convex(int nb_hulls) {
    InceptionConvex incepconv;
    incepconv.curlen = 0;
    incepconv.total_points = 0;
    incepconv.tab_convex = (Convex*)malloc(sizeof(Convex) * nb_hulls);
    
    if (!(incepconv.tab_convex)) {
        incepconv.maxlen = 0;
    } else {
        incepconv.maxlen = nb_hulls;
        for (int i = 0; i < incepconv.maxlen; i++) {
            incepconv.tab_convex[i] = create_convex();
        }
    }
    return incepconv;
}

Section create_section(int xmin, int ymin, int xmax, int ymax) {
    Section section;
    section.min = create_point(xmin, ymin);
    section.max = create_point(xmax, ymax);
    section.height = ymax - ymin;
    section.width = xmax - xmin;
    return section;
}

Window create_window(Section information, Section clickable, int width, int height) {
    Window win;
    win.information = information;
    win.clickable = clickable;
    win.width = width;
    win.height = height;
    return win;
}

Window create_window_data(int width, int height) {
    Section information = create_section(0, height - INFORMATION_HEIGHT, width, height);
    Section clickable = create_section(0, 0, width, height - INFORMATION_HEIGHT);
    return create_window(information, clickable, width, height);
}

void free_vertex(Vertex* vrtx) {
    if (vrtx) {
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

