#include <MLV/MLV_all.h>
#include <math.h>
#include <time.h>

#include "../utils.h"

#define RADIUS 5
#define PI 3.14159265

/*
clang -c graphic.c -Wall -std=c17 -lMLV
clang -c ../list/list.c -Wall -std=c17
clang -c ../math/math.c list.o -Wall -std=c17
clang enveloppe.c graphic.o -Wall -std=c17 -o env -lMLV
*/

void drawPoint(Point* p, MLV_Color color) {
    MLV_draw_filled_circle(p->x, p->y, RADIUS, color);
}

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

int r_sign() {
    if ((rand() % 2) == 0) {
        return -1;
    } else {
        return 1;
    }
}

void draw_circle_random_rising(int radius_max, int nb_points, int window_widht, int window_height) {
    double nb_random, radius = radius_max / (float)nb_points;
    srand(time(NULL));
    for (int i = 0; i < nb_points; i++) {
        nb_random = rand();
        MLV_draw_filled_circle(window_widht / 2 + radius * i * cos(nb_random), window_height / 2 + radius * i * sin(nb_random), 2, MLV_COLOR_GREEN);
        MLV_actualise_window();
    }
}

void draw_circle_random(int radius_max, int nb_points, int window_widht, int window_height) {
    double nb_random;
    int radius;
    srand(time(NULL));
    for (int i = 0; i < nb_points; i++) {
        nb_random = rand();
        radius = rand() % radius_max;
        MLV_draw_filled_circle(window_widht / 2 + radius * cos(nb_random), window_height / 2 + radius * sin(nb_random), 2, MLV_COLOR_GREEN);
        MLV_actualise_window();
    }
}

void draw_square_random(int radius_max, int nb_points, int window_widht, int window_height) {
    int min_x = (window_widht / 2) - radius_max, min_y = (window_height / 2) - radius_max;
    srand(time(NULL));
    for (int i = 0; i < nb_points; i++) {
        MLV_draw_filled_circle(min_x + rand() % (2 * radius_max), min_y + rand() % (2 * radius_max), 2, MLV_COLOR_GREEN);
        MLV_actualise_window();
    }
}

void draw_square_random_rising(int radius_max, int nb_points, int window_widht, int window_height) {
    float radius = radius_max / (float)nb_points;
    srand(time(NULL));
    for (int i = 0; i < nb_points; i++) {
        int nb = (radius * i) + 1;
        // printf("%d\n", nb);
        // printf("%d\n", rand() % nb);
        MLV_draw_filled_circle(window_widht / 2 + r_sign() * (rand() % nb), window_height / 2 + r_sign() * (rand() % nb), 2, MLV_COLOR_GREEN);
        MLV_actualise_window();
    }
}

void init_Convex_click(ConvexHull* convex) {
    convex->poly = createPolygon();
    int points = 0, x, y;
    Point *p0 = createPoint(), *p1 = createPoint();
    while (points < 2) {
        MLV_wait_mouse(&x, &y);
        if (points == 0) {
            fillPoint(p0, x, y);
            drawPoint(p0, MLV_COLOR_BLUE);
        } else {
            fillPoint(p1, x, y);
            drawPoint(p1, MLV_COLOR_BLUE);
        }
        MLV_update_window();
        points++;
    }
    addPoint(&(convex->poly), p0, addVertexTail);
    addPoint(&(convex->poly), p1, addVertexTail);
    drawPoly(convex->poly, MLV_COLOR_BLACK);
    MLV_update_window();
}

void Convex_click(ConvexHull* convex) {
    init_Convex_click(convex);
    Polygon insidePoints = createPolygon();
    while (1) {
        int x, y;
        MLV_wait_mouse(&x, &y);
        Point* p = createPoint();
        fillPoint(p, x, y);
        newPoint((*convex).poly, &insidePoints, p);
        MLV_clear_window(MLV_COLOR_WHITE);
        MLV_update_window();
        drawPoints((*convex).poly, MLV_COLOR_BLUE);
        drawPoints(insidePoints, MLV_COLOR_ORANGE);
    }
}
int main(void) {
    ConvexHull convex;
    MLV_create_window("Setting convex hull", "Setting", 1000, 1000);
    MLV_clear_window(MLV_COLOR_WHITE);
    MLV_update_window();
    Convex_click(&convex);
    // draw_circle_random_rising(100, 400, 300, 600);
    // draw_circle_random(100, 400, 300, 600);
    // draw_square_random(100, 200, 300, 600);
    // draw_square_random_rising(350, 1000, 1000, 1000);
    MLV_wait_seconds(2);
    MLV_free_window();
    return 0;
}
