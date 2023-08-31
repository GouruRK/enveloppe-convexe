#include <stdlib.h>

#include "../include/list.h"
#include "../include/struct.h"
#include "../include/tools.h"

void add_vertex_tail(Polygon* poly, Vertex* vrtx) {
    if (!(*poly)) {
        *poly = vrtx;
        return;
    }
    (*poly)->prev->next = vrtx;
    vrtx->next = *poly;
    vrtx->prev = (*poly)->prev;
    (*poly)->prev = vrtx;
}

void add_vertex_head(Polygon* poly, Vertex* vrtx) {
    add_vertex_tail(poly, vrtx);
    *poly = vrtx;
}

int add_point(Polygon* poly, Point point, void (*add_function)(Polygon*, Vertex*)) {
    Vertex* vrtx = create_vertex();
    if (!vrtx) {
        return 0;
    }
    fill_vertex(vrtx, point);
    add_function(poly, vrtx);
    return 1;
}

Vertex* extract_vertex_tail(Polygon* poly) {
    if (!(*poly)) {
        return NULL;
    }
    Vertex* vrtx = (*poly)->prev;
    if (vrtx == *poly) {
        *poly = NULL;
    } else {
        vrtx->prev->next = *poly;
        vrtx->next = vrtx;
        (*poly)->prev = vrtx->prev;
        vrtx->prev = vrtx;
    }
    return vrtx;
}

Vertex* extract_vertex_head(Polygon* poly) {
    *poly = (*poly)->next;
    return extract_vertex_tail(poly);
}

Vertex* extract_point(Polygon* poly, Point point) {
    if (!(*poly)) {
        return NULL;
    }
    Vertex* head = *poly;
    if (equals_points(head->point, point)) {
        return extract_vertex_head(poly);
    }
    *poly = (*poly)->next;
    while (head != *poly) {
        if (equals_points((*poly)->point, point)) {
            return extract_vertex_head(poly);
        }
    }
    return NULL;
}