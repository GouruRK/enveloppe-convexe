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

int main(void) {
    MLV_create_window("Setting convex hull", "Setting", 1000, 1000);
    // draw_circle_random_rising(100, 400, 300, 600);
    // draw_circle_random(100, 400, 300, 600);
    // draw_square_random(100, 200, 300, 600);
    draw_square_random_rising(350, 1000, 1000, 1000);
    MLV_wait_seconds(2);
    MLV_free_window();
    return 0;
}
