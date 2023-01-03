#include <MLV/MLV_all.h>
#include <math.h>
#include <time.h>

#include "../utils.h"

#define RADIUS 5
#define PI 3.14159265

/*
clang -c ../list/list.c -Wall -std=c17
clang -c ../math/math.c list.o -Wall -std=c17
clang -c draw.c -Wall -std=c17
clang -c graphic.c -Wall -std=c17 -lMLV
clang enveloppe.c graphic.o math.o list.o draw.o -Wall -std=c17 -o env -lMLV -lm
*/

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

int r_sign() {
    return !(rand() % 2) ? -1: 1; 
}

void draw_circle_random_rising(ConvexHull* convex, int radius_max,
                               int nb_points, int window_widht,
                               int window_height) {
    ConvexHull insidePoints = createConvex(nb_points);
    double nb_random, radius = radius_max / (float)nb_points;
    Point *p0 = createPoint(), *p1 = createPoint();
    float x, y;
    for (int i = 0; i < nb_points; i++) {
        nb_random = rand();
        x = window_widht / 2 + radius * i * cos(nb_random);
        y = window_height / 2 + radius * i * sin(nb_random);
        if (i == 2) {
            if (p0->x == p1->x && p0->y == p1->y) {
                p1->x++;
            }
            addPoint(&(convex->poly), p0, addVertexTail);
            addPoint(&(convex->poly), p1, addVertexTail);
            convex->curlen = 2;
        }
        if (i < 2) {
            if (i == 0) {
                fillPoint(p0, (int)x, (int)y);
                drawPoint(p0, RADIUS, COLOR_OUTSIDE);
            } else {
                fillPoint(p1, (int)x, (int)y);
                drawPoint(p1, RADIUS, COLOR_OUTSIDE);
            }
        } else {
            MLV_clear_window(MLV_COLOR_WHITE);
            Point* p = createPoint();
            fillPoint(p, (int)x, (int)y);
            newPoint(convex, &insidePoints, p);
            drawAll(convex, &insidePoints, RADIUS, MLV_draw_polygon);
        }
        MLV_update_window();
    }
}

void draw_circle_random(int radius_max, int nb_points,
                        int window_widht, int window_height) {
    double nb_random;
    int radius;
    
    for (int i = 0; i < nb_points; i++) {
        nb_random = rand();
        radius = rand() % radius_max;
        MLV_draw_filled_circle(window_widht / 2 + radius * cos(nb_random),
                               window_height / 2 + radius * sin(nb_random),
                               RADIUS,
                               MLV_COLOR_GREEN);
        MLV_actualise_window();
    }
}

void draw_square_random(int radius_max, int nb_points,
                        int window_widht, int window_height) {
    int min_x = (window_widht / 2) - radius_max, min_y = (window_height / 2) - radius_max;
    for (int i = 0; i < nb_points; i++) {
        MLV_draw_filled_circle(min_x + rand() % (2 * radius_max),
                               min_y + rand() % (2 * radius_max),
                               RADIUS,
                               MLV_COLOR_GREEN);
        MLV_actualise_window();
    }
}

void draw_square_random_rising(int radius_max, int nb_points,
                               int window_widht, int window_height) {
    float radius = radius_max / (float)nb_points;
    for (int i = 0; i < nb_points; i++) {
        int nb = (radius * i) + 1;
        MLV_draw_filled_circle(window_widht / 2 + r_sign() * (rand() % nb),
                               window_height / 2 + r_sign() * (rand() % nb),
                               RADIUS,
                               MLV_COLOR_GREEN);
        MLV_actualise_window();
    }
}

void init_Convex_click(ConvexHull* convex) {
    int points = 0, x, y;
    Point *p0 = createPoint(), *p1 = createPoint();
    while (points < 2) {
        MLV_wait_mouse(&x, &y);
        if (points == 0) {
            fillPoint(p0, x, y);
            drawPoint(p0, RADIUS, COLOR_OUTSIDE);
        } else {
            fillPoint(p1, x, y);
            drawPoint(p1, RADIUS, COLOR_OUTSIDE);
            MLV_draw_line(p0->x, p0->y, p1->x, p1->y, COLOR_LINE);
        }
        MLV_update_window();
        points++;
    }
    if (p0->x == p1->x && p0->y == p1->y) {
        p1->x++;
    }
    addPoint(&(convex->poly), p0, addVertexTail);
    addPoint(&(convex->poly), p1, addVertexTail);
    convex->curlen = 2;
    MLV_update_window();
}

void draw_convex_click(ConvexHull* convex) {
    ConvexHull insidePoints = createConvex(-1);
    MLV_clear_window(MLV_COLOR_WHITE);
    MLV_update_window();
    init_Convex_click(convex);
    while (1) {
        int x, y;
        MLV_wait_mouse(&x, &y);
        Point* p = createPoint();
        fillPoint(p, x, y);
        newPoint(convex, &insidePoints, p);
        MLV_clear_window(MLV_COLOR_WHITE);
        drawAll(convex, &insidePoints, RADIUS, MLV_draw_polygon);
        MLV_update_window();
    }
}

int main(void) {
    srand(time(NULL));
    ConvexHull convex = createConvex(-1);
    MLV_create_window("Setting convex hull", "Setting", 1000, 1000);
    MLV_clear_window(MLV_COLOR_WHITE);
    // MLV_update_window();
    // draw_convex_click(&convex);
    draw_circle_random_rising(&convex, 400, 400, 1000, 1000);
    // draw_circle_random(100, 400, 300, 600);
    // draw_square_random(100, 200, 300, 600);
    // draw_square_random_rising(350, 1000, 1000, 1000);
    MLV_wait_seconds(2);
    MLV_free_window();
    return 0;
}
