#include "main.h"

/*
gcc -c ./utils/list/list.c -Wall -std=c17
gcc -c ./utils/math/math.c list.o -Wall -std=c17
gcc main.c list.o math.o -Wall -std=c17 -o main -lMLV
*/

#define RADIUS 5

void drawPoint(Point* p, MLV_Color color) {
    MLV_draw_filled_circle(p->x, p->y, RADIUS, color);
}

void drawPoints(Polygon poly, MLV_Color color) {
    Vertex* head = NULL;
    while (head != poly) {
        if (!head) {
            head = poly;
        }
        drawPoint(poly->p, color);
        poly = poly->next;
    }
}

void drawPoly(Polygon poly, MLV_Color color) {
    Vertex* head = poly;
    Vertex* prev = head;
    poly = poly->next;
    while (head != poly) {
        MLV_draw_line(prev->p->x, prev->p->y, poly->p->x, poly->p->y, color);
        prev = poly;
        poly = poly->next;
    }
    MLV_draw_line(prev->p->x, prev->p->y, poly->p->x, poly->p->y, color);
}

void initConvex(ConvexHull* convex) {
    convex->poly = createPolygon();
    int points = 0;
    Point* p0 = createPoint();
    Point* p1 = createPoint();
    Point* p2 = createPoint();
    while (points < 2) {
        int x, y;
        MLV_update_window();
        MLV_wait_mouse(&x, &y);
        MLV_clear_window(MLV_COLOR_WHITE);
        MLV_update_window();
        if (points == 0) {
            fillPoint(p0, x, y);
            drawPoint(p0, MLV_COLOR_BLUE);
        } else if (points == 1) {
            fillPoint(p1, x, y),
            drawPoint(p0, MLV_COLOR_BLUE);
            drawPoint(p1, MLV_COLOR_BLUE);
        } else if (points == 2) {
            fillPoint(p2, x, y),
            drawPoint(p0, MLV_COLOR_BLUE);
            drawPoint(p1, MLV_COLOR_BLUE);
            drawPoint(p2, MLV_COLOR_BLUE);
        }
        points++;
        MLV_update_window();
    }
    addPoint(&(convex->poly), p0, addVertexTail);
    addPoint(&(convex->poly), p1, addVertexTail);
    // if (isDirect(p0, p1, p2)) {
    //     addPoint(&(convex->poly), p0, addVertexTail);
    //     addPoint(&(convex->poly), p1, addVertexTail);
    //     addPoint(&(convex->poly), p2, addVertexTail);
    // } else {
    //     addPoint(&(convex->poly), p0, addVertexTail);
    //     addPoint(&(convex->poly), p2, addVertexTail);
    //     addPoint(&(convex->poly), p1, addVertexTail);
    // }
    drawPoly(convex->poly, MLV_COLOR_BLACK);
    MLV_update_window();
}

void drawTriangle(Point* A, Point* B, Point* C) {
    MLV_Color color = isDirect(A, B, C) ? MLV_COLOR_GREEN: MLV_COLOR_RED;
    MLV_draw_line(A->x, A->y, B->x, B->y, color);
    MLV_draw_line(A->x, A->y, C->x, C->y, color);
    MLV_draw_line(B->x, B->y, C->x, C->y, color);
    MLV_draw_text(A->x, A->y, "A", MLV_COLOR_PURPLE);
    MLV_draw_text(B->x, B->y, "B", MLV_COLOR_PURPLE);
    MLV_draw_text(C->x, C->y, "C", MLV_COLOR_PURPLE);
    MLV_update_window();
}

// TRIANGLE DIRECT -> PAS DEDANS
// TRIANGLE INDIRECT -> DEDANS

void newPoint(Polygon* poly, Polygon* insidePoints, Point* p) {
    // On regarde si le point est a l'intérieur de l'enveloppe
    Vertex* head = NULL;
    Vertex* point;
    int direct;
    while (head != *poly) {
        if (!head) {
            head = *poly;
        }
        direct = isDirect(p, (*poly)->p, (*poly)->next->p);
        *poly = (*poly)->next;
        if (direct) {
            continue;
        } else {
            // on insère p entre [Si, Si+1]
            // on insère a (*poly)->next pcq sinon on insère avant Si
            // *poly = (*poly)->next;
            addPoint(poly, p, addVertexHead);
            // point devient l'endroit où on a insérer le point
            point = *poly;
            break;
        }
    }
    if (direct) {
        addPoint(insidePoints, p, addVertexHead);
        return;
    }
    // On fixe le début de poly au nouveau point
    *poly = point;

    // nettoyage avant
    while (1) {
        direct = isDirect((*poly)->p, (*poly)->next->p, (*poly)->next->next->p);
        if (!direct) {
            Vertex* v = extractVertexHead(&(*poly)->next);
            addVertexHead(insidePoints, v);
        } else {
            break;
        }
    }
    // nettoyage arriere
    while (1) {
        direct = isDirect((*poly)->p, (*poly)->prev->prev->p, (*poly)->prev->p);
        if (!direct) {
            Vertex* keep = *poly;
            *poly = (*poly)->prev;
            Vertex* v = extractVertexHead(poly);
            addVertexHead(insidePoints, v);
            *poly = keep;
        } else {
            break;
        }
    }
}

int main(void) {
    ConvexHull convex;
    Polygon insidePoints = createPolygon();
    MLV_create_window("Enveloppe Convexe", "", 500, 500);
    MLV_clear_window(MLV_COLOR_WHITE);
    initConvex(&convex);
    while (1) {
        int x, y;
        MLV_wait_mouse(&x, &y);
        Point* p = createPoint();
        fillPoint(p, x, y);
        newPoint(&(convex.poly), &insidePoints, p);
        MLV_clear_window(MLV_COLOR_WHITE);
        drawPoly(convex.poly, MLV_COLOR_BLACK);
        drawPoints(convex.poly, MLV_COLOR_BLUE);
        drawPoints(insidePoints, MLV_COLOR_ORANGE);
        MLV_update_window();
    }
    return 0;
}