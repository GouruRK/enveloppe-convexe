#include <MLV/MLV_all.h>
#include <math.h>
#include <time.h>

#include "../utils.h"

#define RADUIS 5
#define PI 3.14159265

/*
clang -c graphic.c -Wall -std=c17 -lMLV
clang -c ../list/list.c -Wall -std=c17
clang -c ../math/math.c list.o -Wall -std=c17
clang enveloppe.c graphic.o -Wall -std=c17 -o env -lMLV
*/

void drawPoint(Point* p, MLV_Color color) {
    MLV_draw_filled_circle(p->x, p->y, RADUIS, color);
}

void coord_from_rand() {
}

int main(void) {
    MLV_create_window("Setting convex hull", "Setting", 400, 400);
    double nb;
    srand(time(NULL));
    for (int i = 1; i < 1000; i++) {
        nb = rand();
        // printf("%f   ", nb);
        // printf("%f %f\n", cos(nb), acos(cos(nb)));
        double rayon = i;
        MLV_draw_filled_circle(200 + rayon * cos(nb), 200 + rayon * sin(nb), 2, MLV_COLOR_RED);
        if (i == 999) {
            printf("%f", rayon + sin(nb));
        }
        MLV_actualise_window();
    }
    MLV_wait_seconds(2);
    MLV_free_window();
    return 0;
}
