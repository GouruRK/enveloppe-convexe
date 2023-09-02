#include "../include/tools.h"
#include "../include/struct.h"

int equals_points(Point a, Point b) {
    return (a.x == b.x) && (a.y == b.y);
}

int point_in_section(Point point, Section section) {
    return (section.min.x < point.x && point.x < section.max.x)
           && (section.min.y < point.y && point.y < section.max.y); 
}