#include <stdbool.h>
#include <stdlib.h>

#include "../include/tools.h"

#include "../include/struct.h"

bool equals_points(Point a, Point b) {
    return (a.x == b.x) && (a.y == b.y);
}

bool point_in_section(Point point, Section section) {
    return (section.min.x < point.x && point.x < section.max.x)
           && (section.min.y < point.y && point.y < section.max.y); 
}

int random_int(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}

double uniform(void) {
    return rand() / (double)RAND_MAX;
}

int true_modulo(int a, int b) {
    return ((a % b) + b) % b;
}