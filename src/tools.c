#include <stdbool.h>

#include "../include/tools.h"
#include "../include/struct.h"

bool equals_points(Point a, Point b) {
    return (a.x == b.x) && (a.y == b.y);
}

bool point_in_section(Point point, Section section) {
    return (section.min.x < point.x && point.x < section.max.x)
           && (section.min.y < point.y && point.y < section.max.y); 
}