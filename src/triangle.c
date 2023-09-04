#include <stdbool.h>

#include "../include/struct.h"

int cross_product(Point A, Point B, Point C) {
    return (B.x - A.x)*(C.y - A.y) - (C.x - A.x)*(B.y - A.y);
}

bool is_direct(Point A, Point B, Point C) {
    return cross_product(A, B, C) >= 0;
}
