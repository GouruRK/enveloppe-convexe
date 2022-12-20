#include "list.h"

Point* createPoint(void) {
    return (Point*)malloc(sizeof(Point));
}

void fillPoint(Point* p, int x, int y) {
    p->x = x;
    p->y = y;
}

Vertex* createVertex(void) {
    return (Vertex*)malloc(sizeof(Vertex));
}

void fillVertex(Vertex* vertex, Point* p) {
    vertex->p = p;
    vertex->prev = vertex;
    vertex->next = vertex;
}

Polygon createPolygon(void) {
    return NULL;
}

void addVertexFront(Polygon* poly, Vertex* vertex) {
    // Si poly est vide
    if (!(*poly)) {
        *poly = vertex;
        return;
    }

    vertex->next = *poly;
    (*poly)->prev->next = vertex;
    vertex->prev = (*poly)->prev;
    (*poly)->prev = vertex;
    *poly = vertex;
}

int length(Polygon poly) {
    if (!poly) {
        return 0;
    }
    Vertex* head = poly;
    poly = poly->next;
    int len = 1;
    while (head != poly) {
        len++;
        poly = poly->next;
    }
    return len;
}

int main(void) {
    Polygon poly = createPolygon();
    Vertex* v1 = createVertex();
    Vertex* v2 = createVertex();
    Vertex* v3 = createVertex();
    Point* p1 = createPoint();    
    Point* p2 = createPoint();
    Point* p3 = createPoint();
    fillPoint(p1, 0, 0);
    fillPoint(p2, 1, 1);
    fillPoint(p3, 2, 2);
    fillVertex(v1, p1);
    fillVertex(v2, p2);
    fillVertex(v3, p3);
    printf("%d\n", length(poly));
    addVertexFront(&poly, v1);
    printf("%d\n", length(poly));
    addVertexFront(&poly, v2);
    printf("%d\n", length(poly));
    addVertexFront(&poly, v3);
    printf("%d\n", length(poly));
    return 0;
}