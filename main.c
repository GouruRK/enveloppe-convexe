#include "main.h"

/*
gcc -c ./utils/list/list.c -Wall -std=c17
gcc -c ./utils/math/math.c list.o -Wall -std=c17
gcc main.c list.o math.o -Wall -std=c17 -o main -lMLV
*/

#define RAYON 5

void drawPoint(Point* p) {
    MLV_draw_filled_circle(p->x, p->y, RAYON, MLV_COLOR_BLUE);
}

void drawPoints(Polygon poly) {
    Vertex* head = NULL;
    while (head != poly) {
        if (!head) {
            head = poly;
        }
        drawPoint(poly->p);
        poly = poly->next;
    }
}

void drawPoly(Polygon poly) {
    Vertex* head = poly;
    Vertex* prev = head;
    poly = poly->next;
    while (head != poly) {
        MLV_draw_line(prev->p->x, prev->p->y, poly->p->x, poly->p->y, MLV_COLOR_BLACK);
        prev = poly;
        poly = poly->next;
    }
}

void addPoint(Polygon* poly, int x, int y) {
    Vertex* v = createVertex();
    Point* p = createPoint();
    fillPoint(p, x, y);
    fillVertex(v, p);
    addVertexHead(poly, v);
}

int main(void) {
    int points = 0;
    int nbPoints = 10;
    Polygon poly = createPolygon();
    MLV_create_window("Enveloppe Convexe", "", 500, 500);
    while (points != nbPoints) {
        int x, y;
        MLV_wait_mouse(&x, &y);
        addPoint(&poly, x, y);
        MLV_clear_window(MLV_COLOR_WHITE);
        drawPoints(poly);
        points ++;
        if (points >= 3) {
            Polygon res = createPolygon();
            quickHull(&poly, &res);
            drawPoly(res);
        }
        MLV_update_window();
    }
    return 0;
}