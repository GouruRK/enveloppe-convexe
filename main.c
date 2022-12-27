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

void drawPoints(ConvexHull* convex) {
    Vertex* head = NULL;
    while (head != convex->poly) {
        if (!head) {
            head = convex->poly;
        }
        drawPoint(convex->poly->p);
        convex->poly = convex->poly->next;
    }
}

void drawConvex(ConvexHull* convex) {
    Vertex* head = convex->poly;
    Vertex* prev = head;
    convex->poly = convex->poly->next;
    while (head != convex->poly) {
        MLV_draw_line(prev->p->x, prev->p->y, convex->poly->p->x, convex->poly->p->y, MLV_COLOR_BLACK);
        prev = convex->poly;
        convex->poly = convex->poly->next;
    }
}

int main(void) {
    int points = 0;
    int nbPoints = 10;
    ConvexHull convex = createConvex(10);
    MLV_create_window("Enveloppe Convexe", "", 500, 500);
    MLV_clear_window(MLV_COLOR_WHITE);
    MLV_update_window();
    int x, y;
    while (points != nbPoints) {
        MLV_wait_mouse(&x, &y);
        addPointCoordinates(&convex, x, y, addVertexHead);
        MLV_clear_window(MLV_COLOR_WHITE);
        drawPoints(&convex);
        points ++;
        if (points >= 3) {
            ConvexHull res = createConvex(-1);
            quickHull(&convex, &res);
            drawConvex(&res);
        }
        MLV_update_window();
    }
    MLV_wait_mouse(&x, &y);
    MLV_free_window();
    return 0;
}