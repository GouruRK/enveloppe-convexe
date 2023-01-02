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

ConvexHull createConvex(int maxlen) {
    ConvexHull convex;
    convex.poly = createPolygon();
    convex.curlen = 0;
    convex.maxlen = maxlen;
    return convex;
}


void drawPoints(Polygon poly, MLV_Color color) {
    if (poly) {
        Vertex* head = poly->prev;
        while (head != poly) {
            drawPoint(poly->p, color);
            poly = poly->next;
        }
        drawPoint(poly->p, color);
    }
}

void drawPoly(ConvexHull convex, MLV_Color color, void (*drawFunction)(const int*, const int*, int, MLV_Color)) {
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

// void drawPoly(ConvexHull convex, MLV_Color color) {
//     Vertex* poly = convex.poly;
//     Vertex* head = poly;
//     Vertex* prev = head;
//     poly = poly->next;
//     while (head != poly) {
//         MLV_draw_line(prev->p->x, prev->p->y, poly->p->x, poly->p->y, color);
//         prev = poly;
//         poly = poly->next;
//     }
//     MLV_draw_line(prev->p->x, prev->p->y, poly->p->x, poly->p->y, color);
// }



void initConvex(ConvexHull* convex) {
    int points = 0;
    Point* p0 = createPoint();
    Point* p1 = createPoint();
    while (points < 2) {
        int x, y;
        MLV_update_window();
        MLV_wait_mouse(&x, &y);
        MLV_clear_window(MLV_COLOR_WHITE);
        MLV_update_window();
        if (points == 0) {
            fillPoint(p0, x, y);
            points++;
            drawPoint(p0, MLV_COLOR_BLUE);
        } else if (points == 1) {
            fillPoint(p1, x, y);
            drawPoint(p0, MLV_COLOR_BLUE);
            drawPoint(p1, MLV_COLOR_BLUE);
            points++;
        }
    }
    addPoint(&(convex->poly), p0, addVertexTail);
    addPoint(&(convex->poly), p1, addVertexTail);
    convex->curlen = 2;
    drawPoly(*convex, MLV_COLOR_BLACK, MLV_draw_polygon);
    MLV_update_window();
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

void newPoint(ConvexHull* convex, ConvexHull* insidePoints, Point* p) {
    // On regarde si le point est a l'intérieur de l'enveloppe
    Vertex* head = NULL;
    Vertex* point;
    int direct;
    while (head != convex->poly) {
        if (!head) {
            head = convex->poly;
        }
        direct = isDirect(p, convex->poly->p, convex->poly->next->p);
        convex->poly = convex->poly->next;
        if (direct) {
            continue;
        } else {
            // on insère p entre [Si, Si+1]
            // on insère a (*poly)->next pcq sinon on insère avant Si
            // *poly = (*poly)->next;
            addPoint(&(convex->poly), p, addVertexHead);
            // point devient l'endroit où on a insérer le point
            point = convex->poly;
            convex->curlen++;
            break;
        }
    }
    if (direct) {
        addPoint(&(insidePoints->poly), p, addVertexHead);
        insidePoints->curlen++;
        return;
    }
    // On fixe le début de poly au nouveau point
    convex->poly = point;

    // nettoyage avant
    while (1) {
        direct = isDirect(convex->poly->p, convex->poly->next->p, convex->poly->next->next->p);
        if (!direct) {
            Vertex* v = extractVertexHead(&(convex->poly->next));
            addVertexHead(&(insidePoints->poly), v);
            convex->curlen--;
            insidePoints->curlen++;
        } else {
            break;
        }
    }
    // nettoyage arriere
    while (1) {
        direct = isDirect(convex->poly->p, convex->poly->prev->prev->p, convex->poly->prev->p);
        if (!direct) {
            Vertex* keep = convex->poly;
            convex->poly = convex->poly->prev;
            Vertex* v = extractVertexHead(&(convex->poly));
            addVertexHead(&(insidePoints->poly), v);
            convex->poly = keep;
            convex->curlen--;
            insidePoints->curlen++;
        } else {
            break;
        }
    }
}

int main(void) {
    ConvexHull convex = createConvex(-1);
    ConvexHull insidePoints = createConvex(-1);
    MLV_create_window("Enveloppe Convexe", "", 500, 500);
    MLV_clear_window(MLV_COLOR_WHITE);
    initConvex(&convex);
    while (1) {
        int x, y;
        MLV_wait_mouse(&x, &y);
        Point* p = createPoint();
        fillPoint(p, x, y);
        newPoint(&convex, &insidePoints, p);
        MLV_clear_window(MLV_COLOR_WHITE);
        drawPoly(convex, MLV_COLOR_BLACK, MLV_draw_polygon);
        drawPoints(convex.poly, MLV_COLOR_BLUE);
        drawPoints(insidePoints.poly, MLV_COLOR_ORANGE);
        MLV_update_window();
    }
    return 0;
}