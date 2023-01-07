#include "../utils.h"

ConvexHull createConvex(int maxlen) {
    ConvexHull convex;
    convex.poly = createPolygon();
    convex.curlen = 0;
    convex.maxlen = maxlen;
    return convex;
}

void drawPoint(Point* p, int radius, MLV_Color color) {
    MLV_draw_filled_circle(p->x, p->y, radius, color);
}

void drawPoints(Polygon poly, int radius, MLV_Color color) {
    if (poly) {
        Vertex* head = poly->prev;
        while (head != poly) {
            drawPoint(poly->p, radius, color);
            poly = poly->next;
        }
        drawPoint(poly->p, radius, color);
    }
}

void drawPoly(ConvexHull convex, MLV_Color color,
              void (*drawFunction)(const int*, const int*, int, MLV_Color)) {
    if (!convex.curlen) {
        return;
    }
    int* vx = malloc(sizeof(int) * convex.curlen);
    int* vy = malloc(sizeof(int) * convex.curlen);
    if (!vx || !vy) {
        exit(1);
    }
    for (int i = 0; i < convex.curlen; i++) {
        vx[i] = convex.poly->p->x;
        vy[i] = convex.poly->p->y;
        convex.poly = convex.poly->next;
    }
    drawFunction(vx, vy, convex.curlen, color);
    free(vx);
    free(vy);
}

void drawTriangle(Point* A, Point* B, Point* C) {
    MLV_Color color = isDirect(A, B, C) ? MLV_COLOR_GREEN : MLV_COLOR_RED;
    MLV_draw_line(A->x, A->y, B->x, B->y, color);
    MLV_draw_line(A->x, A->y, C->x, C->y, color);
    MLV_draw_line(B->x, B->y, C->x, C->y, color);
    MLV_draw_text(A->x, A->y, "A", MLV_COLOR_PURPLE);
    MLV_draw_text(B->x, B->y, "B", MLV_COLOR_PURPLE);
    MLV_draw_text(C->x, C->y, "C", MLV_COLOR_PURPLE);
    MLV_update_window();
}

void drawAll(ConvexHull* convex, ConvexHull* insidePoints, int radius,
              void (*drawFunction)(const int*, const int*, int, MLV_Color)) {
    MLV_clear_window(MLV_COLOR_WHITE);
    drawPoly(*convex, COLOR_LINE, drawFunction);
    drawPoints((*convex).poly, radius, COLOR_OUTSIDE);
    drawPoints((*insidePoints).poly, radius, COLOR_INSIDE);
    MLV_update_window();
}